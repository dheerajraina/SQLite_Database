#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef struct Column
{
        char *name;
        char *type;
        int is_primary_key;
        int is_not_null;
} Column;

typedef struct TableSchema
{
        char *table_name;
        Column *columns;
        int column_count;

} TableSchema;

#endif