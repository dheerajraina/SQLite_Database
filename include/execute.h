#ifndef EXECUTE_H
#define EXECUTE_H

#include "sql_command.h"
#include "parser.h"
void execute_command(SQLCommand *command);
int execute_create_table(TableSchema *schema);

#endif