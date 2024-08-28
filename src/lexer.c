#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "sql_command.h"




void init_lexer(Lexer *lexer, char *input) {
    lexer->token_count = 0;
    printf("%s",input);
    char *token = strtok(input, " ");
    while (token != NULL && lexer->token_count < MAX_TOKENS) {
        lexer->tokens[lexer->token_count++] = token;
        token = strtok(NULL, " ");
    }
}
