#include "lexer.h"

void sea_lexer_init(Lexer * lexer, const char * source){
  lexer->source = source; // source: the entire file content
  lexer->start = source; // start: the beginning of the current token
  lexer->current = source; // current: the current position in the source
  lexer->line = 1; // line: the current line number
  lexer->col = 1; // col: the current column number
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

static bool in_string(const char * str, char c) {
  while (*str) {
    if (*str == c) return true;
    str++;
  }
  return false;
}

static bool sea_isalpha(char c) {
  return (in_string(UPPER_ALPHABET, c) || in_string(LOWER_ALPHABET, c) || c == '_');
}

static Token make_token(Lexer * lexer, token_t type, int line, int col) {
  Token token;
  token.type = type;
  token.start = lexer->start;
  token.length = (size_t)(lexer->current - lexer->start);
  token.line = line;
  token.col = col;
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
  if (strcmp(token_buffer, "float") == 0) return TOK_KW_FLOAT;
  if (strcmp(token_buffer, "void") == 0) return TOK_KW_VOID;
  if (strcmp(token_buffer, "char") == 0) return TOK_KW_CHAR;
  if (strcmp(token_buffer, "bool") == 0) return TOK_KW_BOOL;
  if (strcmp(token_buffer, "double") == 0) return TOK_KW_DOUBLE;
  return TOK_ERROR;
}

static token_t single_char_token(char c)
{
    switch (c) {
        case '(': return TOK_LPAREN;
        case ')': return TOK_RPAREN;
        case '{': return TOK_LBRACE;
        case '}': return TOK_RBRACE;
        case '[': return TOK_LBRACKET;
        case ']': return TOK_RBRACKET;
        case ';': return TOK_SEMICOLON;
        case ',': return TOK_COMMA;
        case '.': return TOK_DOT;
        case ':': return TOK_COLON;
        case '+': return TOK_PLUS;
        case '-': return TOK_MINUS;
        case '*': return TOK_STAR;
        case '/': return TOK_SLASH;
        case '%': return TOK_PERCENT;
        case '=': return TOK_ASSIGN;
        case '<': return TOK_LT;
        case '#': return TOK_PREPROC;
        case '>': return TOK_GT;
        default:  return TOK_ERROR;
    }
}

bool sea_lexer_parse_token(Token * token_buff, size_t * token_buff_count, Lexer * lexer){
  char c;
  while ((c = sea_lexer_peek(lexer)) != '\0') {
    int start_line = lexer->line;
    int start_col = lexer->col;
    lexer->start = lexer->current;
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
      sea_lexer_advance(lexer);
      continue;
    }
    if (in_string(DIGITS, c)) {
      while (in_string(DIGITS, sea_lexer_peek(lexer))) {
        sea_lexer_advance(lexer);
      }
      if (sea_lexer_peek(lexer) == '.' && in_string(DIGITS, lexer->current[1])) {
        sea_lexer_advance(lexer); 
        while (in_string(DIGITS, sea_lexer_peek(lexer))) {
          sea_lexer_advance(lexer);
        }
        token_buff[(*token_buff_count)++] = make_token(lexer, TOK_FLOAT_LITERAL, start_line, start_col);
      }
      else {
        token_buff[(*token_buff_count)++] = make_token(lexer, TOK_INT_LITERAL, start_line, start_col);
      }
      continue;
    }
    if (sea_isalpha(c)) {
      while (sea_isalpha(sea_lexer_peek(lexer)) || in_string(DIGITS, sea_lexer_peek(lexer))) {
        sea_lexer_advance(lexer);
      }

      char keyword_buffer[256]; // fix later
      size_t length = (size_t)(lexer->current - lexer->start);
      strncpy(keyword_buffer, lexer->start, length);
      keyword_buffer[length] = '\0';
      token_t type = keyword_scan(keyword_buffer);
      if (type != TOK_ERROR) {
        token_buff[(*token_buff_count)++] = make_token(lexer, type, start_line, start_col);
      } else {
        token_buff[(*token_buff_count)++] = make_token(lexer, TOK_IDENTIFIER, start_line, start_col);
      }
      continue;
    }
    if (in_string(SYMBOLS, c)) {
      switch (c) {
          case ':':
              if (lexer->current[1] == ':') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_SCOPE, start_line, start_col);
                  continue;
              }
              break;

          case '+':
              if (lexer->current[1] == '+') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_INCREMENT, start_line, start_col);
                  continue;
              }
              break;

          case '-':
              if (lexer->current[1] == '-') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_DECREMENT, start_line, start_col);
                  continue;
              }

              if (lexer->current[1] == '>') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_ARROW, start_line, start_col);
                  continue;
              }
              break;

          case '=':
              if (lexer->current[1] == '=') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_EQ, start_line, start_col);
                  continue;
              }
              break;

          case '!':
              if (lexer->current[1] == '=') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_NEQ, start_line, start_col);
                  continue;
              }
              break;

          case '<':
              if (lexer->current[1] == '=') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_LTE, start_line, start_col);
                  continue;
              }
              break;

          case '>':
              if (lexer->current[1] == '=') {
                  sea_lexer_advance(lexer);
                  sea_lexer_advance(lexer);
                  token_buff[(*token_buff_count)++] = make_token(lexer, TOK_GTE, start_line, start_col);
                  continue;
              }
              break;
      }
      sea_lexer_advance(lexer);
      token_buff[(*token_buff_count)++] = make_token(lexer, single_char_token(c), start_line, start_col);
      continue;
    }
    printf("Unrecognized character: %c at line %d, col %d\n", c, lexer->line, lexer->col);
    sea_lexer_advance(lexer);
  }
  if (*token_buff_count == 0) {
    return false;
  } return true;
}