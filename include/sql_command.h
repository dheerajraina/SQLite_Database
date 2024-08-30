#ifndef SQL_COMMAND_H
#define SQL_COMMAND_H

#include "constants.h"

typedef enum
{
    CREATE_DATABASE,
    CREATE_TABLE,
} CommandType;

typedef struct
{
    CommandType type;
    char database_name[255]; // Assuming max length of the database name is 255 characters
    TableSchema *schema;
} SQLCommand;

#endif
