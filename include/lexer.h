#ifndef SEA_LEXER_H
#define SEA_LEXER_H

#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define UPPER_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define VAR_SYMS ""
#define DIGITS "0123456789"
#define SYMBOLS "+-*/%=(){}[];,.<>!&:#|\"\\"

typedef struct {
  const char * source;
  const char * start;
  const char * current;

  int line;
  int col;
} Lexer;

void sea_lexer_init(Lexer * lexer, const char * source);
char sea_lexer_peek(Lexer * lexer);
bool sea_lexer_parse_token(Token * token_buff, size_t * token_buff_count, Lexer * lexer);


#endif 
