#include "parser.h"
#include <ctype.h>

// 创建字符串对象
String* parse_string(const char* input) {
    if (!input) return NULL;
    
    String* str = (String*)malloc(sizeof(String));
    if (!str) {
        fprintf(stderr, "内存分配失败\n");
        return NULL;
    }
    
    str->length = strlen(input);
    str->data = (char*)malloc(str->length + 1);
    if (!str->data) {
        free(str);
        fprintf(stderr, "内存分配失败\n");
        return NULL;
    }
    
    strcpy(str->data, input);
    return str;
}

// 释放字符串对象
void free_string(String* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

// 打印字符串
void print_string(const String* str) {
    if (str && str->data) {
        printf("字符串内容: %s\n", str->data);
        printf("字符串长度: %d\n", str->length);
    }
}

// 获取字符串长度
int string_length(const String* str) {
    return str ? str->length : 0;
}

// 转换为C字符串
char* string_to_cstr(const String* str) {
    return str ? str->data : NULL;
}

// 行统计功能（占位符，将在分支中实现）
int count_lines(const char* filename) {
    fprintf(stderr, "行统计功能未实现\n");
    return -1;
}

int count_words(const char* filename) {
    fprintf(stderr, "单词统计功能未实现\n");
    return -1;
}

int count_chars(const char* filename) {
    fprintf(stderr, "字符统计功能未实现\n");
    return -1;
}
