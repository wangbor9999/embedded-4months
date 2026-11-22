/*
 * w1_str.c
 * W1 地基练习：手写字符串 / 内存基本操作
 *   - my_memcpy : 内存拷贝（按非重叠缓冲区实现）
 *   - my_strlen : 求字符串长度（不含 '\0'）
 *   - my_strcmp : 字符串比较，返回 <0 / 0 / >0
 * 编译: gcc -std=c11 -Wall -Wextra w1_str.c -o w1_str.exe
 */
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* 内存拷贝：把 src 的 n 字节复制到 dst，返回 dst */
void *my_memcpy(void *dst, const void *src, size_t n)
{
    uint8_t       *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dst;
}

/* 求字符串长度（不含结尾 '\0'） */
size_t my_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

/* 字符串比较：相等返回 0；s1<s2 返回负值；s1>s2 返回正值 */
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int main(void)
{
    char        dst[32] = {0};
    const char *src     = "hello, embedded";

    my_memcpy(dst, src, my_strlen(src) + 1);
    printf("memcpy : %s (len=%zu)\n", dst, my_strlen(dst));

    printf("cmp \"abc\" vs \"abc\" = %d\n", my_strcmp("abc", "abc"));
    printf("cmp \"abc\" vs \"abd\" = %d\n", my_strcmp("abc", "abd"));
    printf("cmp \"abd\" vs \"abc\" = %d\n", my_strcmp("abd", "abc"));

    return 0;
}