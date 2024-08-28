#ifndef SQL_COMMAND_H
#define SQL_COMMAND_H

typedef enum {
    CREATE_DATABASE,
} CommandType;

typedef struct {
    CommandType type;
    char database_name[255]; // Assuming max length of the database name is 255 characters
} SQLCommand;

#endif
