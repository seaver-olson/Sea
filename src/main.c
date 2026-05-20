#include <stdio.h>
#include <string.h>
#include "lexer.h"

#define BUF_SIZE 256 // experiment with this num later

char file_buffer[BUF_SIZE];
char filename_buffer[BUF_SIZE];

int main(int argv, char * argc[]){
  Lexer lexer;
  Token tokens[BUF_SIZE]; // fix later
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
  sea_lexer_init(&lexer, file_buffer);
  while (fgets(file_buffer, BUF_SIZE, file) != NULL){ // for each line
    lexer.start = file_buffer;
    lexer.current = file_buffer;
    Token token_buff[256];
    size_t token_buff_count = 0;
    if (sea_lexer_parse_token(token_buff, &token_buff_count, &lexer)){
      for (size_t i = 0; i < token_buff_count; i++) {
        tokens[token_count++] = token_buff[i];
      }
    } else {
      printf("Error: Failed to parse token at line %d, col %d\n", lexer.line, lexer.col);
    }
  }
  for (size_t i = 0; i < token_count; i++) {
    Token token = tokens[i];
    printf("Token Num: %zu Type: %s, Line: %d, Col: %d\n", i, token_type_name(token.type), token.line, token.col);
  }
  fclose(file);
  return 0;
}
