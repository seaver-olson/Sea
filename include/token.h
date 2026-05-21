#ifndef SEA_SPEC_TOKENS_H
#define SEA_SPEC_TOKENS_H

#define SEA_SPEC_TOKENS(OP) \
  OP(TK_EOF, "EOF") \
  OP(TK_ERROR, "ERROR")

#define SEA_LITERAL_TOKENS(OP) \
  OP(TK_STRING_LITERAL, "string") \
  OP(TK_INT_LITERAL, "int") \
  OP(TK_FLOAT_LITERAL, "float") \
  OP(TK_CHAR_LITERAL, "char") \
  OP(TK_IDENTIFIER, "identifier")

#define SEA_KEYWORD_TOKENS(OP) \
  OP(TK_DT_VOID, "void") \
  OP(TK_DT_BOOL, "bool") \
  OP(TK_DT_CHAR, "char") \
  OP(TK_DT_INT, "int") \
  OP(TK_DT_FLOAT, "float") \
  OP(TK_DT_STRING, "string") \
  OP(TK_DT_STRUCT, "struct") \
  OP(TK_DT_ENUM, "enum") \
  OP(TK_KW_RETURN, "return") \
  OP(TK_KW_TRUE, "true") \
  OP(TK_KW_FALSE, "false") \
  OP(TK_KW_NULL, "null") \
  OP(TK_KW_IF, "if") \
  OP(TK_KW_ELSE, "else") \
  OP(TK_KW_FOR, "for") \
  OP(TK_KW_WHILE, "while") \
  OP(TK_KW_BREAK, "break") \
  OP(TK_KW_CONTINUE, "continue") \
  OP(TK_KW_SWITCH, "switch") \
  OP(TK_KW_CASE, "case") \
  OP(TK_KW_DEFAULT, "default") \
  OP(TK_KW_NAMESPACE, "namespace")

#define SEA_OPERATOR_TOKENS(OP) \
  OP(TK_PLUS, "+") \
  OP(TK_MINUS, "-") \
  OP(TK_STAR, "*") \
  OP(TK_SLASH, "/") \
  OP(TK_PERCENT, "%") \
  OP(TK_EQ, "==") \
  OP(TK_NEQ, "!=") \
  OP(TK_LT, "<") \
  OP(TK_GT, ">") \
  OP(TK_LTE, "<=") \
  OP(TK_GTE, ">=") \
  OP(TK_AND, "&&") \
  OP(TK_OR, "||") \
  OP(TK_NOT, "!") \
  OP(TK_ASSIGN, "=") \
  OP(TK_PLUS_ASSIGN, "+=") \
  OP(TK_MINUS_ASSIGN, "-=") \
  OP(TK_STAR_ASSIGN, "*=") \
  OP(TK_SLASH_ASSIGN, "/=") \
  OP(TK_PERCENT_ASSIGN, "%=") \
  OP(TK_INCREMENT, "++") \
  OP(TK_DECREMENT, "--")

#define SEA_PUNCTUATION_TOKENS(OP) \
  OP(TK_LPAREN, "(") \
  OP(TK_RPAREN, ")") \
  OP(TK_LBRACE, "{") \
  OP(TK_RBRACE, "}") \
  OP(TK_LBRACKET, "[") \
  OP(TK_RBRACKET, "]") \
  OP(TK_COLON, ":") \
  OP(TK_SEMICOLON, ";") \
  OP(TK_COMMA, ",") \
  OP(TK_DOT, ".") \
  OP(TK_ARROW, "->")

#define SEA_TOKEN_LIST(OP) \
  SEA_SPEC_TOKENS(OP) \
  SEA_LITERAL_TOKENS(OP) \
  SEA_KEYWORD_TOKENS(OP) \
  SEA_OPERATOR_TOKENS(OP) \
  SEA_PUNCTUATION_TOKENS(OP)

typedef enum {
  #define OP(tok, str) tok,
  SEA_TOKEN_LIST(OP)
  #undef OP
} TokenType;

#endif // SEA_SPEC_TOKENS_H
