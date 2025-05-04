'''
AST Parser
--------------------------------------------------------------------------------------------------
This file contains the code to parse the AST of a given code snippet using tree-sitter.

Authors
--------------------------------------------------------------------------------------------------
  * José Armando Rosas Balderas | A01704132
  * Ramona Najera Fuentes       | A01423596
  * Ian Joab Padron Corona      | A01708940

**Date:** 2025-Apr-28

Libraries
--------------------------------------------------------------------------------------------------
`tree-stitter`: Library for parsing source code into an AST.
`networkx`: Library for creating and manipulating complex networks.
`numpy`: Library for numerical computations in Python.
`matplotlib`: Library for creating static, animated, and interactive visualizations in Python.
`sklearn`: Library for machine learning in Python.
`sys`: Library for system-specific parameters and functions.
`warnings`: Library for issuing warning messages.

Usage
--------------------------------------------------------------------------------------------------
This script is used to parse the AST of a given code snippet using tree-sitter.
```
python AST.py <lang_grammar> <path_grammar> <file>
```
'''

from tree_sitter import Language, Parser
import numpy as np
import matplotlib.pyplot as plt
import sys
import networkx as nx
import warnings

# Ignore all warnings
warnings.filterwarnings("ignore")

class CFGBuilder:
    """
    Class to build a Control Flow Graph (CFG) from a given code snippet using tree-sitter.

    Parameters
    ---
    code: `bytes` The code snippet to be parsed.
    """
    def __init__(self, code: bytes):
        self.graph = nx.DiGraph()
        self.counter = 0
        self.code = code
        self.loop_stack = []  # Holds tuples for break/continue statements
        self.toPrintNodes = []  # Nodes to be appended to the graph


    # Generate a detailed label by traversing the node's children
    def generate_label(self, node):
        if node.child_count == 0:  # Leaf node
            return node.type
        if node.type == "identifier":
            return node.type
        if node.type == "expression_statement":
            return ''.join(self.generate_label(child) for child in node.children)
        if node.type == "local_variable_declaration":
            return ''.join(self.generate_label(child) for child in node.children)
        
        if node.type == "switch_block_statement_group":
            return ''.join(self.generate_label(child) for child in node.children if child.type == "switch_label")
        if node.type == "switch_label":
            return ''.join(self.generate_label(child) for child in node.children)
        else:  # Non-leaf node
            return ''.join(self.generate_label(child) for child in node.children)

    def get_text(self, node):
        """
        Get the text of a node in the AST.
        
        Parameters
        ---
        node: `Tree Sitter Node` The node to get the text from.
        
        Returns
        ---
        text: `str` The text of the node.
        """
        line = self.code[node.start_byte:node.end_byte].decode("utf-8")
        return line 

    def new_node(self, node, label:str):
        """
        Create a new node in the graph with a unique index and label.

        Parameters
        ---
        label: `str` The label for the new node.
        
        Returns
        ---
        idx: `int` The index of the new node.
        """
        idx = self.counter
        if node.type == "expression_statement":
            label = self.generate_label(node)
        elif node.type == "local_variable_declaration":
            label = self.generate_label(node)
        elif node.type == "if_statement":
            label = f"if {self.generate_label(node.child_by_field_name('condition'))}"
        elif node.type == "for_statement":
            label = f"for {self.generate_label(node.child_by_field_name('init'))} {self.generate_label(node.child_by_field_name('condition'))} {self.generate_label(node.child_by_field_name('update'))}"
        elif node.type == "while_statement":
            label = f"while {self.generate_label(node.child_by_field_name('condition'))}"
        elif node.type == "switch_block_statement_group":
            label = f"switch {self.generate_label(node)}"
        elif node.type == "identifier":
            label = f"identifier: {node.type}"
        else:
            label = node.type
            # Append additional text for leaf nodes
            if node.child_count == 0 and node.text:
                label += f": {node.text.decode('utf8')}"
        self.graph.add_node(idx, label=label)
        self.counter += 1
        return idx

    def connect_all(self, from_nodes, to_node):
        """
        Connect all nodes `from_nodes` -> `to_node`.
        
        Parameters
        ---
        from_nodes: `list` The list of nodes to connect from.
        
        to_node: `int` The node to connect to.
        """
        for n in from_nodes:
            self.graph.add_edge(n, to_node)

    def build_from_ast(self, node):
        """
        Build the CFG from the AST node.
        
        Parameters
        ---
        node: `Tree Sitter Node` The root node of the AST.
        """
        return self._visit(node)

    def _visit(self, node):
        """
        Visit a node in the AST and build the CFG.
        
        Parameters
        ---
        node: `Tree Sitter Node` The node to visit.
        
        Returns
        ---
        entry: `int` The entry node of the CFG.
        
        exit: `list` The exit nodes of the CFG.
        """
        if node.type == "block":
            prev_exit = []
            entry = None
            for child in node.children:
                if child.is_named:
                    subgraph = self._visit(child)
                    if entry is None:
                        entry = subgraph["entry"]
                    if prev_exit:
                        self.connect_all(prev_exit, subgraph["entry"])
                    prev_exit = subgraph["exit"]
            return {"entry": entry, "exit": prev_exit}

        elif node.type == "if_statement":
            cond_node = self.new_node(node, f"if {self.get_text(node.child_by_field_name('condition'))}")
            then_branch = self._visit(node.child_by_field_name("consequence"))
            else_node = node.child_by_field_name("alternative")
            if else_node:
                else_branch = self._visit(else_node)
                self.graph.add_edge(cond_node, then_branch["entry"])
                self.graph.add_edge(cond_node, else_branch["entry"])
                exits = then_branch["exit"] + else_branch["exit"]
            else:
                self.graph.add_edge(cond_node, then_branch["entry"])
                exits = then_branch["exit"] + [cond_node]
            return {"entry": cond_node, "exit": exits}

        elif node.type == "while_statement":
            cond_node = self.new_node(node, f"while {self.get_text(node.child_by_field_name('condition'))}")
            
            self.loop_stack.append((cond_node, []))  # Track exits for break
            
            body = self._visit(node.child_by_field_name("body"))
            self.graph.add_edge(cond_node, body["entry"])
            self.connect_all(body["exit"], cond_node)
            
            _, break_exits = self.loop_stack.pop() # Track exits for break
            
            return {"entry": cond_node, "exit": break_exits + [cond_node]}
        
        elif node.type == "do_statement":
            cond_node = self.new_node(node, f"while {self.get_text(node.child_by_field_name('condition'))}")

            body = self._visit(node.child_by_field_name("body"))


            self.loop_stack.append((cond_node, []))

            self.graph.add_edge(cond_node, body["entry"])  # Loop back if condition true
            self.connect_all(body["exit"], cond_node)  # Body to condition

            _, break_exits = self.loop_stack.pop()
            return {"entry": body["entry"], "exit": break_exits + [cond_node]}

        elif node.type == "for_statement":
            init = self.new_node(node, self.get_text(node.child_by_field_name("init")))
            cond = self.new_node(node, f"for {self.get_text(node.child_by_field_name('condition'))}")
            update = self.new_node(node, self.get_text(node.child_by_field_name("update")))

            self.loop_stack.append((cond, []))  # Track exits for break

            body = self._visit(node.child_by_field_name("body"))

            self.graph.add_edge(init, cond)
            self.graph.add_edge(cond, body["entry"])
            self.connect_all(body["exit"], update)
            self.graph.add_edge(update, cond)

            _, break_exits = self.loop_stack.pop() # Track exits for break
            
            return {"entry": init, "exit": break_exits + [cond]}
        
        elif node.type == "switch_expression":
            cond_node = self.new_node(node, f"switch {self.get_text(node.child_by_field_name('condition'))}")
            body = node.child_by_field_name("body")  # should be a block
            case_entries = []
            last_exits = []
            for child in body.children:
                if child.type in {"switch_label", "case", "default", "switch_block_statement_group"}:
                    label = self.new_node(child, self.get_text(child))
                    self.graph.add_edge(cond_node, label)
                    case_entries.append(label)
                    last_label = label
                    last_exits.append(label)
                elif child.is_named:
                    subgraph = self._visit(child)
                    self.connect_all(last_exits, subgraph["entry"])
                    last_exits = subgraph["exit"]

            return {"entry": cond_node, "exit": last_exits}

        elif node.type == "try_statement":
            try_block = self._visit(node.child_by_field_name("block"))
            exits = try_block["exit"]

            # Handle catch clauses
            catch_clauses = [c for c in node.children if c.type == "catch_clause"]
            for catch in catch_clauses:
                catch_block = self._visit(catch.child_by_field_name("block"))
                self.connect_all([try_block["entry"]], catch_block["entry"])
                exits += catch_block["exit"]

            # Handle finally
            finally_block = node.child_by_field_name("finally_clause")
            if finally_block:
                final_graph = self._visit(finally_block.child_by_field_name("block"))
                self.connect_all(exits, final_graph["entry"])
                exits = final_graph["exit"]

            return {"entry": try_block["entry"], "exit": exits}
        
        elif node.type == "break_statement":
            brk = self.new_node("break")
            if self.loop_stack:
                _, break_targets = self.loop_stack[-1]
                break_targets.append(brk)
            return {"entry": brk, "exit": []}

        elif node.type == "continue_statement":
            cont = self.new_node("continue")
            if self.loop_stack:
                loop_cond, _ = self.loop_stack[-1]
                self.graph.add_edge(cont, loop_cond)
            return {"entry": cont, "exit": []}


        elif node.type == "return_statement":
            ret = self.new_node(node, self.get_text(node))
            return {"entry": ret, "exit": []}
        
        elif node.type in ["block_comment", "line_comment"]:
            return {"entry": None, "exit": []}

        else:
            stmt = self.new_node(node, self.get_text(node))
            return {"entry": stmt, "exit": [stmt]}

def set_parserGrammar(parser, lang_grammar, path_grammar):
    """
    Set the language grammar for the parser

    Parameters
    ---
    parser: `Parser`
        The Tree-sitter parser instance

    lang_grammar: `str`
        The programming language grammar ('cpp' or 'java').

    path_grammar: `str`
        The path to the compiled grammar file.
    """
    try:
        parser.set_language(Language(path_grammar, lang_grammar))
    except Exception as e:
        print(f"[ERROR]: Failed to load {lang_grammar} language grammar. {e}")
        sys.exit(1)

def merge_CFGs(cfg_dict):
    """
    Given a dictionary of subCFG's, merge all into a single CFG with a 'root' node.

    Parameters
    ---
    cfg_dict: `dict` 
        A dictionary where keys are method names and values are their corresponding CFGs.

    Returns
    ---
    super_cfg: `Graph` A merged CFG with a 'root' node.
    """
    super_cfg = nx.DiGraph()
    root_id = "root"
    super_cfg.add_node(root_id, label="ROOT")

    for method_name, method_cfg in cfg_dict.items():
        # Rename method nodes to avoid conflicts
        renamed_cfg = nx.relabel_nodes(
            method_cfg, 
            lambda n: f"{method_name}_{n}"
        )

        # Merge method graph into the super CFG
        super_cfg.update(renamed_cfg)

        # Find entry node — assume it's the only node with in-degree 0
        entry_nodes = [n for n in renamed_cfg.nodes if renamed_cfg.in_degree(n) == 0]
        if entry_nodes:
            super_cfg.add_edge(root_id, entry_nodes[0], type="method_entry")

    return super_cfg


def build_CFG(tree, source_code, cfg_builder_class):
    """
    Extracts a CFG for each method in a Java class.

    Parameters
    ---
    tree: `Tree Sitter Tree` 
        The Tree-sitter parsed tree

    source_code: `bytes` 
        The raw source code

    cfg_builder_class: `CFGBuilder` 
        The CFGBuilder class to build the CFG

    Returns
    ---
        `dict` Dictionary of {method_name: networkx.DiGraph}
    """
    root = tree.root_node
    method_cfgs = {}

    # Walk the tree and look for method declarations
    def get_method_name(method_node):
        for child in method_node.children:
            if child.type == "identifier":
                return source_code[child.start_byte:child.end_byte].decode("utf-8")
        return "unknown_method"

    # Recursive DFS to find all method_declaration nodes
    def walk_for_methods(node):
        if node.type == "method_declaration":
            method_name = get_method_name(node)

            # Build the CFG from the method body
            node_body = node.child_by_field_name("body")

            # Initialize the CFGBuilder for both files
            builder = cfg_builder_class(source_code)
            builder.build_from_ast(node_body)
            method_cfgs[method_name] = builder.graph
        for child in node.children:
            walk_for_methods(child)

    walk_for_methods(root)
    return method_cfgs

# Define the constants for the Parser
lang_grammar, path_grammar, file = sys.argv[1], sys.argv[2], sys.argv[3]

# Initialize the parser
parser = Parser()

# Set the grammar for the parser
set_parserGrammar(parser, lang_grammar, path_grammar)

# Read codes from the provided file path
with open(file, 'rb') as f:
    code = f.read()

# Generate the AST for the provided code snippets
tree = parser.parse(code)

# Generate the CFG's for the provided code snippets
CFSubGraphs = build_CFG(tree, code, CFGBuilder)
CFGraph = merge_CFGs(CFSubGraphs)

# Print nodes and edges of the CFG
print("Nodes in CFG:")
for node in CFGraph.nodes(data=True):
    print(node[0], node[1]['label'])
print("\nEdges in CFG:")
for edge in CFGraph.edges(data=True):
    print(edge[0], edge[1])