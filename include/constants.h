#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef struct Column
{
        char *name;
        char *type;
        int is_primary_key;
        int is_not_null;
} Column;

typedef struct Index
{
        char *index_name;
        char *column_name;
        int is_primary; // 1 if index is primary key else 0
} Index;
typedef struct TableSchema
{
        char *table_name;
        Column *columns;
        int column_count;
        Index *indexes; // array of indexes
        int index_count;

} TableSchema;

#endif