# Add a test executable
add_executable(test_create_db test_create_db.c)

# Link the main library to the test executable
target_link_libraries(test_create_db sqlite_lib)
