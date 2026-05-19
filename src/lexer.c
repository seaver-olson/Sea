#include "lexer.h"

void sea_lexer_init(Lexer * lexer, const char * source){
  lexer->source = source;
  lexer->start = source;
  lexer->current = source;
  lexer->line = 1;
  lexer->col = 1;
}

char sea_lexer_peek(Lexer * lexer){
  return *lexer->current;
}

static char sea_lexer_advance(Lexer *lexer){
    char c = *lexer->current;
    lexer->current++;
    if (c == '\n') {
        lexer->line++;
        lexer->col = 1;
    } else {
        lexer->col++;
    }
    return *lexer->current;
}

static bool sea_isdigit(char c){
    return c >= '0' && c <= '9';
}

static bool sea_isalpha(char c){
  return (c >= 'a' && c <= 'z') ||
    (c >= 'A' && c <= 'Z') || c == '_';
}

static Token make_token(Lexer * lexer, token_t type){
  Token token;
  token.type = type;
  token.start = lexer->start;
  token.length = (size_t)(lexer->current - lexer->start);
  token.line = lexer->line;
  token.col = lexer->col;
  return token;
}

token_t keyword_scan(const char * token_buffer){
  if (strcmp(token_buffer, "if") == 0) return TOK_KW_IF;
  if (strcmp(token_buffer, "else") == 0) return TOK_KW_ELSE;
  if (strcmp(token_buffer, "while") == 0) return TOK_KW_WHILE;
  if (strcmp(token_buffer, "for") == 0) return TOK_KW_FOR;
  if (strcmp(token_buffer, "break") == 0) return TOK_KW_BREAK;
  if (strcmp(token_buffer, "continue") == 0) return TOK_KW_CONTINUE;
  if (strcmp(token_buffer, "struct") == 0) return TOK_KW_STRUCT;
  if (strcmp(token_buffer, "enum") == 0) return TOK_KW_ENUM;
  if (strcmp(token_buffer, "const") == 0) return TOK_KW_CONST;
  if (strcmp(token_buffer, "static") == 0) return TOK_KW_STATIC;
  if (strcmp(token_buffer, "extern") == 0) return TOK_KW_EXTERN;
  if (strcmp(token_buffer, "sizeof") == 0) return TOK_KW_SIZEOF;
  if (strcmp(token_buffer, "namespace") == 0) return TOK_KW_NAMESPACE;
  return TOK_ERROR;
}

Token sea_lexer_parse_token(Lexer * lexer){
  Token token;
  char token_buffer[256];
  int token_buffer_index = 0;
  char c;
  make_token(lexer, TOK_ERROR);
  while ((c = sea_lexer_peek(lexer)) != '\0'){
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
      sea_lexer_advance(lexer);
      lexer->start = lexer->current;
      continue;
    }
    if (sea_isdigit(c)){
      while (sea_isdigit(c)) {
        c = sea_lexer_advance(lexer);
      }
      token = make_token(lexer, TOK_INT_LITERAL);
      return token;
    }
    if (sea_isalpha(c)){
      while (sea_isalpha(c)) {
        if (token_buffer_index < 255) {
          token_buffer[token_buffer_index++] = c;
        }
        c = sea_lexer_advance(lexer);
      }
      token_buffer[token_buffer_index] = '\0';
      printf("Token buffer: %s\n", token_buffer);
      token = make_token(lexer, keyword_scan(token_buffer));
      return token;
    }
  }
  return token;
}