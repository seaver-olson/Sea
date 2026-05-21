#include "token.h"

const char* token_to_string(TokenType type) {
  switch (type) {
    #define CASE(type, str) case type: return str;
    SEA_TOKEN_LIST(CASE)
    #undef CASE
    default: return "unknown";
  }
}

