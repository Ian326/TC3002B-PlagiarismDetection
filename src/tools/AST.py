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


# Read codes from the provided file paths
with open(file, 'rb') as f:
    code = f.read()

# Generate the AST for the provided code snippets
tree = parser.parse(code)

# Recursive function to print the AST with indentation
def print_ast(node, level=0):
    print("\t" * level + f"{node.type} [{node.start_point} - {node.end_point}]")
    for child in node.children:
        print_ast(child, level + 1)

# Print the entire AST
print_ast(tree.root_node)

# # Recursive function to perform DFS and store nodes in a list
# def dfs_ast(node, level=0, node_list=None):
#     if node_list is None:
#         node_list = []
    
#     # Append the current node's information to the list
#     node_list.append((node.type, node.start_point, node.end_point, level))
    
#     # Recursively process child nodes
#     for child in node.children:
#         dfs_ast(child, level + 1, node_list)
    
#     return node_list

# # Generate the list of nodes using DFS
# ast_nodes = dfs_ast(tree.root_node)

# print(ast_nodes)