#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 函数声明
typedef struct {
    char* data;
    int length;
} String;

// 解析器函数
String* parse_string(const char* input);
void free_string(String* str);
void print_string(const String* str);
int string_length(const String* str);
char* string_to_cstr(const String* str);

// 行统计功能（将在分支中添加）
int count_lines(const char* filename);
int count_words(const char* filename);
int count_chars(const char* filename);

#endif
