#include "lexer.h"

#include <stdio.h>
#include <string.h>


void lexer_init_source(Lexer * lexer, const char * source) {
  lexer->source = source;
  lexer->start = source;
  lexer->current = source;
  
  lexer->line = 1;
  lexer->col = 1;
}
// internal functions (keep as much inside as possible)
static char lexer_peek(const Lexer * lexer){
  return *lexer->current;
}

static bool is_end(const Lexer * lexer){
  return lexer_peek(lexer) == '\0';
} 

static char lexer_advance(Lexer * lexer){
  char c = lexer_peek(lexer);
  lexer->current++;

  if (c == '\n') {
    lexer->line++;
    lexer->col = 1;
  } else {
    lexer->col++;
  } return c;
}

static Token token_error(const Lexer * lexer, const char * message){
  Token token;
  token.type = TK_ERROR;
  token.start = message;
  token.length = strlen(message);
  token.line = lexer->line;
  token.col = lexer->col;
  return token;
}

static bool is_digit(const char c){
  return c >= '0' && c <= '9';
}

static bool is_symbol(const char c){
  switch (c) {
    #define SYM(tok, str) case str[0]: return true;
    SEA_SYMBOL_LIST(SYM);
    #undef SYM
    default: return false;
  }
}

static bool is_char(const char c){
  switch (c) {
    #define CHAR(tok, str) case str[0]: return true;
    SEA_KEYWORD_TOKENS(CHAR);
    #undef CHAR
    default: return false;
  }
}

// external again
Token lexer_next_token(Lexer * lexer){
  Token token;
  char c;
  lexer->start = lexer->current; // start of token
  
  while (!is_end(lexer)) {
    c = lexer_advance(lexer);
    if (is_digit(c)){
      printf("Number token at line: %d, col: %d\n", lexer->line, lexer->col);
    } else if (is_sym(c)) {
      printf("Symbol token at line: %d, col: %d\n", lexer->line, lexer->col);
    } else if (is_char(c)) {
      printf("Char token at line: %d, col: %d\n", lexer->line, lexer->col);
    } else {
      printf("Unrecognized symbol at line: %d, col: %d\n", lexer->line, lexer->col);
      return token_error(lexer, "Unrecognized symbol");
    }
  }
}

