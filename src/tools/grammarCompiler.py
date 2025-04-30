from tree_sitter import Language

# Compile and link the grammar into a .so file
Language.build_library(
  './java.so',  # Output path
  ['tree-sitter-java']       # Path to the C++ grammar. Part of the tree-sitter repository
)