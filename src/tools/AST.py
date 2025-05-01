'''
==================================================================================================
AST Parser
==================================================================================================
This file contains the code to parse the AST of a given code snippet using tree-sitter.
==================================================================================================
Authors: 
  José Armando Rosas Balderas | A01704132
  Ramona Najera Fuentes       | A01423596
  Ian Joab Padron Corona      | A01708940
Date: 2025-Apr-28
==================================================================================================
Libraries

tree-stitter: Library for parsing source code into an AST.
sys: Library for system-specific parameters and functions.
==================================================================================================
'''
from tree_sitter import Language, Parser
import sys

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

def dfs_ast(node, level=0, node_list=None):
  """
  Perform a depth-first search (DFS) on the AST and store the nodes in a list. 
  Preorder traversal is used to visit the nodes.

  Parameters
  ---
  node: `Tree Sitter Node` The current node in the AST.

  level: `int` The current level in the tree. Default is 0.

  node_list: `list` The list to store the nodes. Default is None.

  Returns
  ---
  node_list: `list` The list of nodes in the AST.
  """
  if node_list is None:
      node_list = []
  
  node_list.append((node.type, level))

  # Recursively process child nodes
  for child in node.children:
      dfs_ast(child, level + 1, node_list)
  
  return node_list

# Generate the list of nodes using DFS
ast_nodes = dfs_ast(tree.root_node)

# Output.txt
for i in range(len(ast_nodes)):
    print(f"{ast_nodes[i][0]} {ast_nodes[i][1]}")