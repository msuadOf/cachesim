#ifndef CACHESIM_H
#include <stdint.h>

typedef uint32_t cachesim_word_t;
typedef uint32_t cachesim_addr_t;
#ifdef __cplusplus
extern "C"
{
    namespace cachesim
    {
        typedef uint32_t word_t;
    }
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    // 从 cache 中读出 addr 地址处的 4 字节数据
    // 若缺失，需要先从内存中读入数据
    uint32_t cache_read(cachesim_addr_t addr, int len);

    // 往 cache 中 addr 地址所属的块写入数据 data，写掩码为 wmask
    // 例如当 wmask 为 0xff 时，只写入低8比特
    // 若缺失，需要从先内存中读入数据
    void cache_write(cachesim_addr_t addr, int len, cachesim_word_t data);

    // 初始化一个数据大小为 2^total_size_width B，关联度为 2^associativity_width 的 cache
    // 例如 init_cache(14, 2) 将初始化一个 16KB，4 路组相联的cache
    // 将所有 valid bit 置为无效即可
    void init_cachesim(cachesim_word_t (*mem_read)(cachesim_addr_t addr, int len), void (*mem_write)(cachesim_addr_t addr, int len, cachesim_word_t data), int total_size_width, int associativity_width,int cacheline_bytes);
    void display_cache_config();
#ifdef __cplusplus
}
#endif

#endif // !CACHESIM_H