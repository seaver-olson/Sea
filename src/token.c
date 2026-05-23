#include "token.h"
#include <string.h>

static bool token_equals(const char* lhs, const char* rhs) {
  return lhs[0] == rhs[0] && strcmp(lhs, rhs) == 0;
}

const char* token_to_string(TokenType type) {
  switch (type) {
    #define CASE(tok, str) case tok: return str;
    SEA_TOKEN_LIST(CASE)
    #undef CASE

    default: return "ERROR";
  }
}

TokenType string_to_token(const char* str_literal) {
  #define IF(tok, str) if (token_equals(str_literal, str)) return tok;
  SEA_TOKEN_LIST(IF)
  #undef IF

  return TK_ERROR;
}

bool is_keyword(const char* str_literal) {
  #define IF(tok, str) if (token_equals(str_literal, str)) return true;
  SEA_KEYWORD_TOKENS(IF)
  #undef IF

  return false;
}

bool is_operator(const char* str_literal) {
  #define IF(tok, str) if (token_equals(str_literal, str)) return true;
  SEA_OPERATOR_TOKENS(IF)
  #undef IF

  return false;
}

bool is_punctuation(const char* str_literal) {
  #define IF(tok, str) if (token_equals(str_literal, str)) return true;
  SEA_PUNCTUATION_TOKENS(IF)
  #undef IF

  return false;
}

bool is_literal(TokenType type) {
  switch (type) {
    #define CASE(tok, str) case tok: return true;
    SEA_LITERAL_TOKENS(CASE)
    #undef CASE

    default: return false;
  }
}
