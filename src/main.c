#include "lexer.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
    return 1;
  }
  FILE* source_file = fopen(argv[1], "r");
  if (!source_file) {
    perror("Error opening source file");
    return 1;
  }
  Lexer lexer;
  lexer_init_source(&lexer, "");
 
  return 0;
}