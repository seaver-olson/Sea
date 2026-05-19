#include <stdio.h>
#include <string.h>
#include "lexer.h"

#define BUF_SIZE 256 // experiment with this num later

char file_buffer[BUF_SIZE];
char filename_buffer[BUF_SIZE];

int main(int argv, char * argc[]){
  Lexer lexer;
  Token tokens[BUF_SIZE];
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
  while (fgets(file_buffer, BUF_SIZE, file) != NULL){
    lexer.start = file_buffer;
    lexer.current = file_buffer;
    while (*lexer.current != '\0') {
      while (*lexer.current == ' ' || *lexer.current == '\t' || *lexer.current == '\r' || *lexer.current == '\n') {
        if (*lexer.current == '\n') {
          lexer.line++;
          lexer.col = 1;
        } else {
          lexer.col++;
        }
        lexer.current++;
        lexer.start = lexer.current;
      }

      if (*lexer.current == '\0') {
        break;
      }

      if ((*lexer.current >= '0' && *lexer.current <= '9') ||
          (*lexer.current >= 'a' && *lexer.current <= 'z') ||
          (*lexer.current >= 'A' && *lexer.current <= 'Z') ||
          *lexer.current == '_') {
        Token token = sea_lexer_parse_token(&lexer);
        if (token_count < BUF_SIZE) {
          tokens[token_count++] = token;
        }
        lexer.start = lexer.current;
        continue;
      }

      if (token_count < BUF_SIZE) {
        tokens[token_count].type = TOK_ERROR;
        tokens[token_count].start = lexer.current;
        tokens[token_count].length = 1;
        tokens[token_count].line = lexer.line;
        tokens[token_count].col = lexer.col;
        token_count++;
      }
      lexer.current++;
      lexer.start = lexer.current;
      lexer.col++;
    }
  }

  for (size_t i = 0; i < token_count; i++) {
    printf("Token: %.*s\n", (int)tokens[i].length, tokens[i].start);
    printf("Type: %s\n", token_type_name(tokens[i].type));
  }

  fclose(file);
  return 0;
}
