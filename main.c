#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

// 在main.c中更新test_linecount函数
void test_linecount() {
    printf("=== 行统计功能测试 ===\n");
    
    // 创建一个测试文件
    FILE* test_file = fopen("test.txt", "w");
    if (test_file) {
        fprintf(test_file, "Hello World!\n");
        fprintf(test_file, "This is line 2 with some words.\n");
        fprintf(test_file, "Line 3 has multiple    spaces.\n");
        fprintf(test_file, "这是第4行，包含中文\n");
        fprintf(test_file, "Last line without newline");
        fclose(test_file);
    } else {
        printf("无法创建测试文件\n");
        return;
    }
    
    // 测试统计功能
    printf("分析文件: test.txt\n");
    
    int lines = count_lines("test.txt");
    int words = count_words("test.txt");
    int chars = count_chars("test.txt");
    
    if (lines >= 0 && words >= 0 && chars >= 0) {
        printf("统计结果:\n");
        printf("  行数: %d\n", lines);
        printf("  单词数: %d\n", words);
        printf("  字符数: %d\n", chars);
        
        // 验证文件内容
        printf("\n文件内容预览:\n");
        FILE* f = fopen("test.txt", "r");
        if (f) {
            char buffer[256];
            int line_num = 1;
            while (fgets(buffer, sizeof(buffer), f)) {
                printf("  %2d: %s", line_num++, buffer);
                if (buffer[strlen(buffer)-1] != '\n') {
                    printf("\n");  // 最后一行可能没有换行符
                }
            }
            fclose(f);
        }
    } else {
        printf("统计失败\n");
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
