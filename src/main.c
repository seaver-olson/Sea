#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

#define BUF_SIZE 256 // experiment with this num later

char filename_buffer[BUF_SIZE];

int main(int argv, char * argc[]){
  Lexer lexer;
  Token tokens[BUF_SIZE]; // fix later
  int lexer_error_count = 0;
  size_t token_count = 0;
  if (argv < 2) {
    printf("Usages: ./sea filename.sea\n");
    return 1;
  }
  strncpy(filename_buffer, argc[1], BUF_SIZE);
  FILE * file = fopen(filename_buffer, "r");
  if (file == NULL){
    printf("Error: Failed to open file");
    return 1;
  }
  //get file size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  char* source = malloc(file_size + 1);
  if (source == NULL) {
    printf("Error: Failed to allocate memory for file content");
    fclose(file);
    return 1;
  }
  fread(source, 1, file_size, file);
  source[file_size] = '\0';
  
  sea_lexer_init(&lexer, source);
  if (!sea_lexer_parse_token(tokens, &token_count, &lexer)) {
    printf("Error: Failed to parse tokens");
    free(source);
    fclose(file);
    return 1;
  }
  for (size_t i = 0; i < token_count; i++) {
    if (tokens[i].type == TOK_ERROR) {
      printf("Error: Failed to parse token at line %d, col %d\n", tokens[i].line, tokens[i].col);
      lexer_error_count++;
      continue;
    }
    Token token = tokens[i];
    printf("Token Num: %zu Type: %s, Line: %d, Col: %d\n", i, token_type_name(token.type), token.line, token.col);
  }
  if (lexer_error_count > 0) {
    printf("Total lexer errors: %d\n", lexer_error_count);
  }
  fclose(file);
  free(source);
  return 0;
}
