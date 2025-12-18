#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

// 测试函数
void test_parser() {
    printf("=== 测试字符串解析器 ===\n");
    
    // 测试1: 正常解析
    String* str1 = parse_string("Hello, World!");
    if (str1) {
        print_string(str1);
        free_string(str1);
    }
    
    // 测试2: 空字符串
    String* str2 = parse_string("");
    if (str2) {
        print_string(str2);
        free_string(str2);
    }
    
    // 测试3: 测试转换函数
    String* str3 = parse_string("测试中文");
    if (str3) {
        printf("转换为C字符串: %s\n", string_to_cstr(str3));
        free_string(str3);
    }
    
    printf("=== 测试完成 ===\n\n");
}

// 产生段错误的函数（用于GDB调试）
void cause_segfault() {
    printf("即将产生段错误...\n");
    
    // 方法1: 访问空指针
    int* ptr = NULL;
    *ptr = 42;  // 这行会产生段错误
    
    // 方法2: 访问已释放的内存（备选）
    // int* arr = (int*)malloc(sizeof(int) * 10);
    // free(arr);
    // arr[5] = 42;  // 使用已释放的内存
    
    printf("这段代码不应该被执行\n");
}

// 行统计测试（将在分支中实现）
void test_linecount() {
    printf("=== 行统计功能测试 ===\n");
    
    // 创建一个测试文件
    FILE* test_file = fopen("test.txt", "w");
    if (test_file) {
        fprintf(test_file, "Hello World\n");
        fprintf(test_file, "This is line 2\n");
        fprintf(test_file, "This is line 3\n");
        fprintf(test_file, "And this is the last line\n");
        fclose(test_file);
    }
    
    // 测试统计功能
    int lines = count_lines("test.txt");
    int words = count_words("test.txt");
    int chars = count_chars("test.txt");
    
    if (lines >= 0) {
        printf("文件 test.txt 统计结果:\n");
        printf("  行数: %d\n", lines);
        printf("  单词数: %d\n", words);
        printf("  字符数: %d\n", chars);
    }
    
    printf("=== 测试完成 ===\n\n");
}

int main(int argc, char* argv[]) {
    printf("字符串解析器程序启动\n");
    
    // 解析命令行参数
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            String* str = parse_string(argv[i]);
            if (str) {
                printf("参数 %d: ", i);
                print_string(str);
                free_string(str);
            }
        }
    }
    
    // 运行测试
    test_parser();
    
    // 测试行统计功能
    test_linecount();
    
    // 段错误测试（默认注释掉，需要时启用）
    // printf("\n=== 段错误测试 ===\n");
    // cause_segfault();
    
    return 0;
}
