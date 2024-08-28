
#include <stdio.h>
#include <string.h>
#include "parser.h"

int parse_create_database(Lexer *lexer, SQLCommand *command)
{
    if (lexer->token_count != 3)
    {
        return 0; // Invalid number of tokens
    }

    if ((strcmp(lexer->tokens[0], "CREATE") == 0 || (strcmp(lexer->tokens[0], "create") == 0 ) &&
       ( strcmp(lexer->tokens[1], "DATABASE") == 0)|| strcmp(lexer->tokens[1], "database") == 0))
    {

        command->type = CREATE_DATABASE;
        strncpy(command->database_name, lexer->tokens[2], sizeof(command->database_name) - 1);
        return 1;
    }
    return 0; // Invalid command
}

int parse_command(char *input, SQLCommand *command) {
    Lexer lexer;
    init_lexer(&lexer, input);

    if (parse_create_database(&lexer, command)) {
        return 1;
    }

    return 0; // Unsupported or invalid command
}
