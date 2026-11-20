/*
 * w1_ring_buffer.c （初版，含待修复缺陷）
 * 环形缓冲区（uint8_t buf[64]）
 */
#include <stdio.h>
#include <stdint.h>

#define RING_SIZE 64u

typedef struct {
    uint8_t buf[RING_SIZE];
    uint8_t head;
    uint8_t tail;
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

/* BUG: 判满条件误写成与判空相同，空缓冲区也被判满，写入被全部拒绝 */
static uint8_t ring_is_full(const ring_t *r)
{
    return r->head == r->tail;
}

static int8_t ring_push(ring_t *r, uint8_t data)
{
    if (ring_is_full(r)) {
        return -1;
    }
    r->buf[r->head] = data;
    r->head = (uint8_t)((r->head + 1u) % RING_SIZE);
    return 0;
}

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

    /* 尝试写入 70 字节：容量 64，正常应在写满后拒绝 */
    for (uint8_t i = 0; i < 70; i++) {
        if (ring_push(&r, i) == 0) {
            pushed++;
        }
    }
    while (ring_pop(&r, &v) == 0) {
        popped++;
    }
    printf("pushed=%d popped=%d (容量 %d)\n", pushed, popped, RING_SIZE);

    return 0;
}