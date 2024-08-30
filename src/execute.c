
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "execute.h"

void execute_command(SQLCommand *command)
{
    if (command->type == CREATE_DATABASE)
    {
        char path[300];
        snprintf(path, sizeof(path), "./%s", command->database_name);

        if (mkdir(path, 0777) == 0)
        {
            printf("Database '%s' created successfully.\n", command->database_name);
        }
        else
        {
            perror("Error creating database");
        }
    }
    else if (command->type == CREATE_TABLE)
    {

        if (execute_create_table(command->schema) == 0)
        {
            printf("\nTable %s create successfully\n", command->schema->table_name);
        }
        else
        {
            perror("\nError creating table\n");
        }
    }
    else
    {
        printf("Unsupported command.\n");
    }
}

int write_table_schema_to_file(TableSchema *schema)
{
    char filename[256];
    snprintf(filename, sizeof(filename), "%s.tbl", schema->table_name);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        return -1; // Error opening file
    }

    fprintf(file, "Table: %s\n", schema->table_name);
    for (int i = 0; i < schema->column_count; i++)
    {
        Column col = schema->columns[i];
        fprintf(file, "Column: %s %s %s %s\n",
                col.name, col.type,
                col.is_not_null ? "NOT NULL" : "",
                col.is_primary_key ? "PRIMARY KEY" : "");
    }

    fclose(file);
    return 0;
}

int execute_create_table(TableSchema *schema)
{
    if (!schema)
    {
        return -1;
    }
    // Check if a table with the same name already exists
    char filename[256];
    snprintf(filename, sizeof(filename), "%s.tbl", schema->table_name);
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        // Handle error: Table already exists
        perror("Table Already exists!!");
        return -1;
    }

    // Write the table schema to a file
    return write_table_schema_to_file(schema);
}
