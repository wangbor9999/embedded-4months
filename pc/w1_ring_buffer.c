/*
 * w1_ring_buffer.c
 * 环形缓冲区（uint8_t buf[64]）
 *   - head: 下一个写入位置；tail: 下一个读取位置
 *   - 判空: head == tail
 *   - 判满: (head + 1) % SIZE == tail （预留一个空位区分空 / 满，容量 63）
 *   - 写满策略: 满则拒绝写入并返回 -1，不覆盖未读数据
 * 编译: gcc -std=c11 -Wall -Wextra w1_ring_buffer.c -o w1_ring_buffer.exe
 */
#include <stdio.h>
#include <stdint.h>

#define RING_SIZE 64u

typedef struct {
    uint8_t buf[RING_SIZE];
    uint8_t head;   /* 写指针：下一个写入位置 */
    uint8_t tail;   /* 读指针：下一个读取位置 */
} ring_t;

static void ring_init(ring_t *r)
{
    r->head = 0;
    r->tail = 0;
}

static uint8_t ring_is_empty(const ring_t *r)
{
    return r->head == r->tail;
}

static uint8_t ring_is_full(const ring_t *r)
{
    return ((r->head + 1u) % RING_SIZE) == r->tail;
}

/* 写入 1 字节：0 成功，-1 缓冲区已满 */
static int8_t ring_push(ring_t *r, uint8_t data)
{
    if (ring_is_full(r)) {
        return -1;
    }
    r->buf[r->head] = data;
    r->head = (uint8_t)((r->head + 1u) % RING_SIZE);
    return 0;
}

/* 读出 1 字节到 *out：0 成功，-1 缓冲区已空 */
static int8_t ring_pop(ring_t *r, uint8_t *out)
{
    if (ring_is_empty(r)) {
        return -1;
    }
    *out = r->buf[r->tail];
    r->tail = (uint8_t)((r->tail + 1u) % RING_SIZE);
    return 0;
}

int main(void)
{
    ring_t  r;
    uint8_t v;
    int     pushed = 0;
    int     popped = 0;

    ring_init(&r);

    /* 写入 70 字节：预留一个空位后容量为 63，写满后应拒绝 */
    for (uint8_t i = 0; i < 70; i++) {
        if (ring_push(&r, i) == 0) {
            pushed++;
        }
    }
    while (ring_pop(&r, &v) == 0) {
        popped++;
    }
    printf("pushed=%d popped=%d (容量 %d, 有效容量 %d)\n",
           pushed, popped, RING_SIZE, RING_SIZE - 1u);

    return 0;
}