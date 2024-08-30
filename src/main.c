#include <stdio.h>
#include <string.h>
#include "sql_command.h"
#include "parser.h"
#include "execute.h"

int main()
{
    char input[512];
    SQLCommand command;

    printf("Enter SQL command:\n");
    fgets(input, sizeof(input), stdin);

    // // Remove newline character from input
    input[strcspn(input, "\n")] = 0;

    if (parse_command(input, &command))
    {
        printf("execute command");
        execute_command(&command);
    }
    else
    {
        printf("Invalid command.\n");
    }

    return 0;
}
