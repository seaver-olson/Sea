#ifndef SEA_LEXER_H
#define SEA_LEXER_H

#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  const char * source;
  const char * start;
  const char * current;

  int line;
  int col;
} Lexer;

void sea_lexer_init(Lexer * lexer, const char * source);
char sea_lexer_peek(Lexer * lexer);
Token sea_lexer_parse_token(Lexer * lexer);


#endif 
