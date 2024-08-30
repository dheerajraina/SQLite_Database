#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 100

typedef enum
{
    TOKEN_CREATE,      // 0
    TOKEN_DATABASE,    // 1
    TOKEN_TABLE,       // 2
    TOKEN_IDENTIFIER,  // 3
    TOKEN_DATA_TYPE,   // 4
    TOKEN_NOT_NULL,    // 5
    TOKEN_PRIMARY_KEY, // 6
    TOKEN_LPAREN,      // 7
    TOKEN_RPAREN,      // 8
    TOKEN_COMMA,       // 9
    TOKEN_SEMICOLON,   // 10
    TOKEN_EOF,         // 11
    TOKEN_UNKNOWN      // 12
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;
typedef struct
{
    Token *tokens[MAX_TOKENS];
    int token_count;
} Lexer;

Token *get_next_token(char *input);

void init_lexer(Lexer *lexer, char *input);

#endif
