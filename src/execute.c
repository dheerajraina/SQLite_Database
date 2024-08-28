
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "execute.h"


void execute_command(SQLCommand *command)
{
        if (command->type == CREATE_DATABASE) {
            char path[300];
            snprintf(path, sizeof(path), "./%s", command->database_name);

            if (mkdir(path, 0777) == 0) {
                printf("Database '%s' created successfully.\n", command->database_name);
            } else {
                perror("Error creating database");
            }
        } else {
            printf("Unsupported command.\n");
        }
}
