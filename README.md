# embedded-4months

2026.11.23 开始，目标：2027 嵌入式（工业控制 / 装备制造方向）实习。

配套《四个月嵌入式软件实习冲刺带教方案》《项目实战手册》执行，按周推进，
每周保留可演示产出与 Git 提交记录。

## 目录结构

```
embedded-4months/
├── pc/        # PC 端 gcc 练习（W1 C 语言地基）
└── stm32/     # STM32 工程（W2 起，按周归档）
```

## W1 进度（工具链 + C 语言地基）

- [x] 工具链：Keil MDK、VS Code + C/C++ 插件、Git、SSCOM、PC 端 gcc(w64devkit)
- [x] `pc/w1_str.c`        手写 my_memcpy / my_strlen / my_strcmp
- [x] `pc/w1_ring_buffer.c` 环形缓冲区（head/tail，判空判满，满则拒绝写入）
- [x] `pc/w1_shell.c`      命令解析器（结构体数组 + 函数指针表分发）

## PC 端编译方法

```
cd pc
gcc -std=c11 -Wall -Wextra w1_str.c        -o w1_str.exe
gcc -std=c11 -Wall -Wextra w1_ring_buffer.c -o w1_ring_buffer.exe
gcc -std=c11 -Wall -Wextra w1_shell.c      -o w1_shell.exe
```

## 约束

- 手写代码只写在 CubeMX 的 USER CODE 保护区内。
- 提交信息使用 `feat / fix / refactor / docs / test` 前缀，不用 update。