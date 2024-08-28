cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(SQLite C)

include_directories(include)


set(SOURCES
        src/main.c
        src/lexer.c
        src/parser.c
        src/execute.c
)

add_library(sqlite_lib ${SOURCES})


add_executable(sqlite ${SOURCES})

target_link_libraries(sqlite sqlite_lib)

add_subdirectory(tests)
