cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(json-parser-c C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        main.c
        utf-8.c
        array_list.c
        tokenizer.c
        parser.c
)

set(HEADERS
        utf-8.h
        array_list.h
        tokenizer.h
        parser.h
)

list(TRANSFORM SOURCES PREPEND "src/")
list(TRANSFORM HEADERS PREPEND "include/")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME}
        PRIVATE -Wall
        PRIVATE -Wextra
        PRIVATE -Wno-format
        PRIVATE -Wno-format-extra-args
)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
