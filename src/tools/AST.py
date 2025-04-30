'''
=================================================================================================
AST Parser
==================================================================================================
Authors: 
  José Armando Rosas Balderas | A01704132
  Ramona Najera Fuentes       | A01423596
  Ian Joab Padron Corona      | A01708940
Date: 2025-Apr-28
==================================================================================================
Libraries
==================================================================================================
This file contains the code to parse the AST of a given code snippet using tree-sitter.

tree-stitter: Library for parsing source code into an AST.
sys: Library for system-specific parameters and functions.
==================================================================================================
'''
from tree_sitter import Language, Parser
import sys

# Define the constants for the Parser
lang_grammar, path_grammar, file1, file2 = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]

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
with open(file1, 'rb') as f:
    code1 = f.read()

with open(file2, 'rb') as f:
    code2 = f.read()

# Generate the AST for the provided code snippets
tree1 = parser.parse(code1)
tree2 = parser.parse(code2)

print("Tree 1 root:", tree1.root_node)
print("Tree 2 root:", tree2.root_node)
