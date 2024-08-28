#ifndef PARSER_H
#define PARSER_H
#include "sql_command.h"
#include "lexer.h"
int parse_create_database(Lexer *lexer, SQLCommand *command);
int parse_command(char *input, SQLCommand *command);
#endif