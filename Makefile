# Makefile for parser project
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
AR = ar
RM = rm -f

# 目标文件
TARGET = parser_app
STATIC_LIB = libparser.a
DYNAMIC_LIB = libparser.so

# 源文件
SRCS = parser.c main.c
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET) $(STATIC_LIB) $(DYNAMIC_LIB)

# 生成可执行文件（静态链接）
$(TARGET): $(OBJS) $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $@ main.o -L. -lparser

# 生成静态库
$(STATIC_LIB): parser.o
	$(AR) rcs $@ $^

# 生成动态库
$(DYNAMIC_LIB): parser.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ parser.c

# 编译源文件
%.o: %.c parser.h
	$(CC) $(CFLAGS) -c $< -o $@

# 静态链接测试
static_test: $(STATIC_LIB) main.o
	$(CC) $(CFLAGS) -o static_test main.o -L. -lparser
	./static_test

# 动态链接测试
dynamic_test: $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) -o dynamic_test main.c -L. -lparser -Wl,-rpath=.
	./dynamic_test

# 调试编译
debug: CFLAGS += -DDEBUG -O0
debug: clean all

# 性能优化编译
release: CFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# 清理
clean:
	$(RM) $(OBJS) $(TARGET) $(STATIC_LIB) $(DYNAMIC_LIB) \
	      static_test dynamic_test test.txt core core.* \
	      parser_dyn parser_static

# 运行测试
test: all
	./$(TARGET)

# 生成文档
doc:
	doxygen Doxyfile 2>/dev/null || echo "请安装doxygen以生成文档"

# 安装（需要root权限）
install: $(DYNAMIC_LIB)
	cp $(DYNAMIC_LIB) /usr/local/lib/
	cp parser.h /usr/local/include/
	ldconfig

# 卸载
uninstall:
	$(RM) /usr/local/lib/$(DYNAMIC_LIB)
	$(RM) /usr/local/include/parser.h

.PHONY: all clean test debug release static_test dynamic_test install uninstall doc
