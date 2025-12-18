// 在parser.c中添加完整的行统计实现
#include "parser.h"
#include <ctype.h>
#include <errno.h>

// ... 现有的字符串函数保持不变 ...

// 完整的行统计功能实现
int count_lines(const char* filename) {
    if (!filename) {
        fprintf(stderr, "错误: 文件名不能为空\n");
        return -1;
    }
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "错误: 无法打开文件 '%s': %s\n", 
                filename, strerror(errno));
        return -1;
    }
    
    int line_count = 0;
    int ch;
    int in_line = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
            in_line = 0;
        } else {
            in_line = 1;
        }
    }
    
    // 如果文件不以换行符结尾但包含内容，增加一行
    if (in_line) {
        line_count++;
    }
    
    fclose(file);
    return line_count;
}

int count_words(const char* filename) {
    if (!filename) {
        fprintf(stderr, "错误: 文件名不能为空\n");
        return -1;
    }
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "错误: 无法打开文件 '%s': %s\n", 
                filename, strerror(errno));
        return -1;
    }
    
    int word_count = 0;
    int ch;
    int in_word = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',' || ch == '.' || ch == ';' || ch == ':' || 
            ch == '!' || ch == '?' || ch == '(' || ch == ')' || 
            ch == '[' || ch == ']' || ch == '{' || ch == '}' || 
            ch == '"' || ch == '\'') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }
    
    // 最后一个单词
    if (in_word) {
        word_count++;
    }
    
    fclose(file);
    return word_count;
}

int count_chars(const char* filename) {
    if (!filename) {
        fprintf(stderr, "错误: 文件名不能为空\n");
        return -1;
    }
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "错误: 无法打开文件 '%s': %s\n", 
                filename, strerror(errno));
        return -1;
    }
    
    int char_count = 0;
    
    // 移动到文件末尾
    if (fseek(file, 0, SEEK_END) == 0) {
        char_count = ftell(file);
    } else {
        // 如果fseek失败，逐个字符计数
        fseek(file, 0, SEEK_SET);
        char_count = 0;
        while (fgetc(file) != EOF) {
            char_count++;
        }
    }
    
    fclose(file);
    return char_count;
}
