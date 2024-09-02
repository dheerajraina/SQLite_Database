
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

Column *create_column(char *name, char *type, int is_primary_key, int is_not_null)
{
    Column *column = malloc(sizeof(Column));
    column->name = strdup(name);
    column->type = strdup(type);
    column->is_primary_key = is_primary_key;
    column->is_not_null = is_not_null;
    return column;
}
int parse_create_database(Lexer *lexer, SQLCommand *command)
{
    if (lexer->token_count != 3)
    {
        return 0; // Invalid number of tokens
    }

    if (lexer->tokens[0]->type == TOKEN_CREATE && lexer->tokens[1]->type == TOKEN_DATABASE)
    {

        command->type = CREATE_DATABASE;
        strncpy(command->database_name, lexer->tokens[2]->value, sizeof(command->database_name) - 1);
        return 1;
    }
    return 0; // Invalid command
}

int parse_create_table(Lexer *lexer, SQLCommand *command)
{
    printf("entered create table parse fn %d", lexer->token_count);
    int i = 0;
    if (lexer->token_count < 7)
    {
        printf("Here1");
        return 0; // Invalid number of tokens
    }

    if (lexer->tokens[i++]->type != TOKEN_CREATE)
    {
        printf("Here2");
        // Handle error: Expected 'CREATE'
        return 0;
    }
    if (lexer->tokens[i++]->type != TOKEN_TABLE)
    {
        printf("Here3");
        // Handle error: Expected 'TABLE'
        return 0;
    }
    if (lexer->tokens[i]->type != TOKEN_IDENTIFIER)
    {
        printf("Here4");
        // Handle error: Expected table name
        return 0;
    }

    char *table_name = strdup(lexer->tokens[i++]->value);

    if (lexer->tokens[i++]->type != TOKEN_LPAREN)
    {
        printf("Here5");
        // Handle error: Expected '('
        return 0;
    }

    // Initialize table schema

    TableSchema *schema = malloc(sizeof(TableSchema));
    schema->table_name = table_name;
    schema->columns = NULL;
    lexer->tokens[i]->type;
    schema->column_count = 0;

    while (lexer->tokens[i]->type != TOKEN_RPAREN && lexer->tokens[++i]->type != TOKEN_SEMICOLON)
    {
        i--;
        if (lexer->tokens[i]->type != TOKEN_IDENTIFIER)
        {
            printf("Here5");
            // Handle error: Expected column name
            return 0;
        }
        char *column_name = strdup(lexer->tokens[i++]->value);

        if (lexer->tokens[i]->type != TOKEN_DATA_TYPE)
        {
            printf("Here6");
            // Handle error: Expected data type
            return 0;
        }

        char *column_type = strdup(lexer->tokens[i]->value);

        i++;
        // Check for optional constraints
        int is_primary_key = 0;
        int is_not_null = 0;
        while (lexer->tokens[i]->type == TOKEN_NOT_NULL || lexer->tokens[i]->type == TOKEN_PRIMARY_KEY)
        {
            if (lexer->tokens[i]->type == TOKEN_NOT_NULL)
            {
                is_not_null = 1;
            }
            else if (lexer->tokens[i]->type == TOKEN_PRIMARY_KEY)
            {
                is_primary_key = 1;
            }
            i++;
        }
        // Add Column to the schema

        if (is_primary_key)
        {
            printf("\n==============Entered is primary key\n");
            Index primary_index;
            primary_index.index_name = strdup("PRIMARY_KEY_INDEX");
            primary_index.column_name = strdup(column_name);
            primary_index.is_primary = 1;

            schema->indexes = realloc(schema->indexes, sizeof(Index) * (schema->index_count + 1));
            schema->indexes[schema->index_count++] = primary_index;
        }

        Column *column = create_column(column_name, column_type, is_primary_key, is_not_null);
        schema->columns = realloc(schema->columns, sizeof(Column) * (schema->column_count + 1));
        schema->columns[schema->column_count++] = *column;
        // Expect a comma or closing parenthesis
        if (lexer->tokens[i]->type == TOKEN_COMMA)
        {
            i++;
            continue; // Parse next column
        }
        else if (lexer->tokens[i]->type != TOKEN_RPAREN)
        {
            // printf("----%d",lexer->tokens[i]->type);
            printf("Here7");
            // Handle error: Expected ',' or ')'
            return 0;
        }
    }

    command->type = CREATE_TABLE;
    command->schema = schema;

    printf("----REturned schema ");
    return 1;
}

int parse_command(char *input, SQLCommand *command)
{
    Lexer lexer;
    printf("parse_command ------------ %s\n", input);
    init_lexer(&lexer, input);

    if (parse_create_database(&lexer, command))
    {
        return 1;
    }

    if (parse_create_table(&lexer, command))
    {

        printf("parse_create_table");
        return 1;
    }

    return 0; // Unsupported or invalid command
}
