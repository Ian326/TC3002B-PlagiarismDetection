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
            body_node = node.child_by_field_name("body")
            cond_node = self.new_node(node, f"while {self.get_text(node.child_by_field_name('condition'))}")

            self.loop_stack.append((cond_node, []))

            body = self._visit(body_node)

            self.connect_all(body["exit"], cond_node)  # Body to condition
            self.graph.add_edge(cond_node, body["entry"])  # Loop back if condition true

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

        else:
            stmt = self.new_node(node, self.get_text(node))
            return {"entry": stmt, "exit": [stmt]}

def find_method_declaration(node):
    """
    Recursively search for the first 'method_declaration' node in the AST.

    Parameters:
    ---
    node: `Tree Sitter Node` The current node in the AST.

    Returns:
    ---
    method_node: `Tree Sitter Node` The 'method_declaration' node if found, else None.
    """
    if node.type == "method_declaration":
        return node

    for child in node.children:
        result = find_method_declaration(child)
        if result:
            return result

    return None


# Define the constants for the Parser
lang_grammar, path_grammar, file = sys.argv[1], sys.argv[2], sys.argv[3]

# Initialize the parser
parser = Parser()

if lang_grammar == 'cpp':
  try:
    parser.set_language(Language(path_grammar, 'cpp'))
  except Exception as e:
    print(f"[ERROR]: Failed to load C++ language grammar. {e}")
    sys.exit(1)

elif lang_grammar == 'java':
  try:
    parser.set_language(Language(path_grammar, 'java'))
  except Exception as e:
    print(f"[ERROR]: Failed to load Java language grammar. {e}")
    sys.exit(1)

else:
    print("[ARG0]: Language not supported. Please use 'cpp' or 'java'.")
    sys.exit(1)


# Read codes from the provided file path
with open(file, 'rb') as f:
    code = f.read()

# Generate the AST for the provided code snippets
tree = parser.parse(code)

# Find the method declaration node
node_method = find_method_declaration(tree.root_node)

if node_method is None:
    print("[ERROR]: No method_declaration found in the AST.")
    sys.exit(1)

# Build the CFG from the method body
node_body = node_method.child_by_field_name("body")

# Initialize the CFGBuilder
cfg_builder = CFGBuilder(code)
cfg = cfg_builder.build_from_ast(node_body)
cfgGraph = cfg_builder.graph

# Print nodes and edges of the CFG
print("Nodes in CFG:")
for node in cfgGraph.nodes(data=True):
    print(node[0], node[1]['label'])
print("\nEdges in CFG:")
for edge in cfgGraph.edges(data=True):
    print(edge[0], edge[1])