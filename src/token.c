#include "token.h"

const char* token_to_string(TokenType type) {
  switch (type) {
    #define CASE(type, str) case type: return str;
    SEA_TOKEN_LIST(CASE)
    #undef CASE
    default: return "unknown";
  }
}

TokenType string_to_token(const char* str) {
  #define IF(str_literal, tok) if (strcmp(str, str_literal) == 0) return tok;
  SEA_TOKEN_LIST(IF)
  #undef IF
  return TK_UNKNOWN;
}

bool is_keyword(const char* str) {
  #define IF(str_literal, tok) if (strcmp(str, str_literal) == 0) return true;
  SEA_KEYWORD_TOKENS(IF)
  #undef IF
  return false;
}

bool is_operator(const char* str) {
  #define IF(str_literal, tok) if (strcmp(str, str_literal) == 0) return true;
  SEA_OPERATOR_TOKENS(IF)
  #undef IF
  return false;
}

bool is_punctuation(const char* str) {
  #define IF(str_literal, tok) if (strcmp(str, str_literal) == 0) return true;
  SEA_PUNCTUATION_TOKENS(IF)
  #undef IF
  return false;
}

bool is_literal(TokenType type) {
  switch (type) {
    #define CASE(type, str) case type: return true;
    SEA_LITERAL_TOKENS(CASE)
    #undef CASE
    default: return false;
  }
}

