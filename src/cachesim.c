#include <stddef.h>
#include <stdint.h>
#include "cachesim.h"

typedef cachesim_word_t word_t;
typedef cachesim_addr_t addr_t;

typedef struct runtime_memory
{
    word_t (*mem_read)(addr_t addr, int len);
    void (*mem_write)(addr_t addr, int len, word_t data);
} runtime_memory_t;

runtime_memory_t rt = {
    .mem_read = NULL,
    .mem_write = NULL};

void init_cachesim(word_t (*mem_read)(addr_t addr, int len), void (*mem_write)(addr_t addr, int len, word_t data), int total_size_width, int associativity_width)
{
    rt = (runtime_memory_t){
        .mem_read = mem_read,
        .mem_write = mem_write};
}
// 从 cache 中读出 addr 地址处的 4 字节数据
// 若缺失，需要先从内存中读入数据
uint32_t cache_read(addr_t addr, int len)
{
    // 先默认读4字节

    // 1。发起请求
    // 2.分配地址
    // 3.判断是否命中
    // 命中：
    // a.1 读出
    // 未命中：
    // b.1 通过算法确定替换的位置
    // b.2 从内存中读出
    // b.3 写入sram，并返回
}

// 往 cache 中 addr 地址所属的块写入数据 data，写掩码为 wmask
// 例如当 wmask 为 0xff 时，只写入低8比特
// 若缺失，需要从先内存中读入数据
void cache_write(addr_t addr, int len, word_t data)
{
}