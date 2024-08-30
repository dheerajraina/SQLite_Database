#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "sql_command.h"

Token *get_next_token(char *input)
{
    Token *token = malloc(sizeof(Token));

    // printf("get_next_token ---------- %s", input);
    if (isalpha(*input))
    {
        if (strcmp(input, "CREATE") == 0)
        {
            token->type = TOKEN_CREATE;
        }
        else if (strcmp(input, "DATABASE") == 0)
        {
            token->type = TOKEN_DATABASE;
        }
        else if (strcmp(input, "TABLE") == 0)
        {
            token->type = TOKEN_TABLE;
        }
        else if (strcmp(input, "INTEGER") == 0 || strcmp(input, "TEXT") == 0)
        {
            token->type = TOKEN_DATA_TYPE;
        }
        else if (strcmp(input, "NOT_NULL") == 0)
        {
            token->type = TOKEN_NOT_NULL;
        }
        else if (strcmp(input, "PRIMARY_KEY") == 0)
        {
            token->type = TOKEN_PRIMARY_KEY;
        }
        else
        {
            token->type = TOKEN_IDENTIFIER;
        }
        token->value = input;
    }
    else if (*input == '(')
    {
        token->type = TOKEN_LPAREN;
    }
    else if (*input == ')')
    {
        token->type = TOKEN_RPAREN;
    }
    else if (*input == ',')
    {
        token->type = TOKEN_COMMA;
    }
    else if (*input == ';')
    {
        token->type = TOKEN_SEMICOLON;
    }
    else if (*input == '\0')
    {
        token->type = TOKEN_EOF;
    }
    else
    {
        token->type = TOKEN_UNKNOWN;
    }
    return token;
}

void init_lexer(Lexer *lexer, char *input)
{
    lexer->token_count = 0;
    char *token = strtok(input, " ");
    printf("initial token %s", token);
    while (token != NULL && lexer->token_count < MAX_TOKENS)
    {
        printf("%s\n", token);
        lexer->tokens[lexer->token_count++] = get_next_token(token);
        token = strtok(NULL, " ");
    }

    for (size_t i = 0; i < lexer->token_count; i++)
    {
        printf("init_lexer------------%d %s \n", lexer->tokens[i]->type, lexer->tokens[i]->value);
    }
}
