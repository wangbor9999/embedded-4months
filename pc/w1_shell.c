/*
 * w1_shell.c
 * 命令解析器：结构体数组 {命令名, 处理函数指针}，按输入命令名分发执行
 * 编译: gcc -std=c11 -Wall -Wextra w1_shell.c -o w1_shell.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 命令处理函数原型：返回 0 成功，负数为错误码 */
typedef int (*cmd_handler)(int argc, char *argv[]);

typedef struct {
    const char  *name;     /* 命令名 */
    cmd_handler  handler;  /* 对应处理函数 */
    const char  *usage;    /* 帮助说明 */
} cmd_entry_t;

static int cmd_help(int argc, char *argv[]);
static int cmd_add(int argc, char *argv[]);
static int cmd_echo(int argc, char *argv[]);

/* 命令表：新增命令只需在这里加一行 */
static const cmd_entry_t g_cmds[] = {
    {"help", cmd_help, "help             显示帮助"},
    {"add",  cmd_add,  "add <a> <b>    两数相加"},
    {"echo", cmd_echo, "echo <text>    回显文本"},
};
#define CMD_COUNT (sizeof(g_cmds) / sizeof(g_cmds[0]))

static int cmd_help(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    for (size_t i = 0; i < CMD_COUNT; i++) {
        printf("  %s\n", g_cmds[i].usage);
    }
    return 0;
}

static int cmd_add(int argc, char *argv[])
{
    if (argc < 3) {
        printf("用法: add <a> <b>\n");
        return -1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("%d + %d = %d\n", a, b, a + b);
    return 0;
}

static int cmd_echo(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    }
    printf("\n");
    return 0;
}

/* 解析一行输入，按空格切分，命中命令则调用对应处理函数 */
static int dispatch(char *line)
{
    char *argv[8];
    int   argc = 0;
    char *tok  = strtok(line, " \t\r\n");

    while (tok != NULL && argc < 8) {
        argv[argc++] = tok;
        tok = strtok(NULL, " \t\r\n");
    }
    if (argc == 0) {
        return 0;
    }

    for (size_t i = 0; i < CMD_COUNT; i++) {
        if (strcmp(argv[0], g_cmds[i].name) == 0) {
            return g_cmds[i].handler(argc, argv);
        }
    }
    printf("未知命令: %s (输入 help 查看列表)\n", argv[0]);
    return -1;
}

int main(void)
{
    /* 非交互自测：直接跑三条命令 */
    char l1[] = "help";
    char l2[] = "add 35 7";
    char l3[] = "echo hello embedded";

    dispatch(l1);
    dispatch(l2);
    dispatch(l3);

    return 0;
}