#include "token.h"

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line, col; // start of token
} Token;

typedef struct {
  const char* source; 
  const char* start; 
  const char* current;
  int line, col;
} Lexer;

void lexer_init_source(Lexer * lexer, const char * source);
Token lexer_next_token(Lexer * lexer);

