#ifndef PARSER_H
#define PARSER_H
#include "sql_command.h"
#include "lexer.h"
#include "constants.h"

int parse_create_database(Lexer *lexer, SQLCommand *command);
int parse_create_table(Lexer *lexer, SQLCommand *command);
int parse_command(char *input, SQLCommand *command);
#endif