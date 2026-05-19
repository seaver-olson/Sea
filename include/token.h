#ifndef SEA_TOKEN_H
#define SEA_TOKEN_H

#include <stddef.h>


typedef enum {
  TOK_ERROR,
  TOK_EOF,
  TOK_INT_LITERAL,
  TOK_FLOAT_LITERAL,
  TOK_CHAR_LITERAL,
  TOK_STRING_LITERAL,
  TOK_KW_FN,
  TOK_KW_RETURN,
  TOK_KW_NAMESPACE,

  TOK_KW_INT,
  TOK_KW_FLOAT,
  TOK_KW_VOID,
  TOK_KW_CHAR,
  TOK_KW_DOUBLE,
  TOK_KW_BOOL,

  TOK_KW_IF,
  TOK_KW_ELSE,
  TOK_KW_WHILE,
  TOK_KW_FOR,
  TOK_KW_BREAK,
  TOK_KW_CONTINUE,

  TOK_KW_STRUCT,
  TOK_KW_ENUM,
  TOK_KW_CONST,
  TOK_KW_STATIC,
  TOK_KW_EXTERN,
  TOK_KW_SIZEOF,

  //punctuation
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_LBRACE,
  TOK_RBRACE,
  TOK_LBRACKET,
  TOK_RBRACKET,
  TOK_SEMICOLON,
  TOK_COMMA,
  TOK_DOT,
  TOK_COLON,
  TOK_SCOPE,// ::
  TOK_ARROW,// ->
  
  TOK_PLUS,
  TOK_MINUS,
  TOK_STAR,
  TOK_SLASH,
  TOK_PERCENT,
  TOK_ASSIGN,// =
  TOK_EQ,
  TOK_NEQ,
  TOK_LT,
  TOK_LTE,
  TOK_GT,
  TOK_GTE
  
} token_t;

typedef struct {
  token_t type;
  const char * start;
  size_t length;

  int line;
  int col;
} Token;

const char* token_type_name(token_t token_type);
#endif 
