#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 3

typedef struct {
    char *tokens[MAX_TOKENS];
    int token_count;
} Lexer;


void init_lexer(Lexer *lexer, char *input);

#endif
