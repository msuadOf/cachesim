#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "cachesim.h"

typedef cachesim_word_t word_t;
typedef cachesim_addr_t addr_t;

typedef struct runtime_memory
{
    word_t (*mem_read)(addr_t addr, int len);
    void (*mem_write)(addr_t addr, int len, word_t data);
} runtime_memory_t;
typedef struct config
{
    word_t (*runtime_replacePolicies)();
    int total_size_width;
    int associativity_width;
    int cacheline_bytes;
} config_t;
typedef struct 
{
    word_t *data;
    int len_bytes;
} cacheline_t;

runtime_memory_t rt_m = {
    .mem_read = NULL,
    .mem_write = NULL};
config_t cache_cfg = {
    .runtime_replacePolicies = NULL,
    .total_size_width = 0,
    .associativity_width = 0,
    .cacheline_bytes = 0
    };

cacheline_t cacheline_read(addr_t addr){
    int len=cache_cfg.cacheline_bytes;
    addr=(addr>>len)<<len; //cacheline对齐
    word_t* read_buf=malloc(len);
    for(int ofs=0;ofs<len;ofs++){
        read_buf[ofs] = rt_m.mem_read(addr+ofs,1);
    }
    return (cacheline_t){
        .data = read_buf,
        .len_bytes = cache_cfg.cacheline_bytes};
}
void cacheline_write(){
}
void init_cachesim(word_t (*mem_read)(addr_t addr, int len), void (*mem_write)(addr_t addr, int len, word_t data), int total_size_width, int associativity_width, int cacheline_bytes)
{
    assert(mem_read);
    assert(mem_write);
    rt_m = (runtime_memory_t){
        .mem_read = mem_read,
        .mem_write = mem_write};
    cache_cfg = (config_t){
        //TODO: 配置替换算法
        .runtime_replacePolicies = NULL,
        .total_size_width = total_size_width,
        .associativity_width = associativity_width,
        .cacheline_bytes = cacheline_bytes};
}
void display_cache_config()
{
    int index_with=cache_cfg.total_size_width-cache_cfg.cacheline_bytes- cache_cfg.associativity_width;
    int offset_width=cache_cfg.cacheline_bytes;
    int tag_width=32-index_with-offset_width;
    
    if(index_with<0) {printf("Error: index_with < 0 !");assert(0);}
    if(offset_width<0) {printf("Error: offset_width < 0 !");assert(0);}
    if(tag_width<0) {printf("Error: tag_width < 0 !");assert(0);}
    

    int offset_down=0;
    int offset_up=0+offset_width-1;
    int index_down=offset_up+1;
    int index_up=index_down+index_with-1;
    int tag_down=index_up+1;
    int tag_up=tag_down+tag_width-1;
    char* info="Memmory address casts to cache:""\n"
"    %2d     %2d %-2d    %1d %1d      0" "\n"
"   +---------+-------+--------+" "\n"
"   |   tag   | index | offset |" "\n"
"   +---------+-------+--------+" "\n"
    "";
    printf(info,tag_up,tag_down,index_up,index_down,offset_up,offset_down);
}
// 从 cache 中读出 addr 地址处的 4 字节数据
// 若缺失，需要先从内存中读入数据
uint32_t cache_read(addr_t addr, int len)
{
    // 先默认读4字节

    // 1。发起请求
    // 2.分配地址
    int index_with=cache_cfg.total_size_width-cache_cfg.cacheline_bytes- cache_cfg.associativity_width;
    int offset_width=cache_cfg.cacheline_bytes;
    int tag_width=32-index_with-offset_width;

    addr_t offset_msk=(1<<offset_width)-1;
    addr_t offset=addr&offset_msk;

    addr_t index_msk=(1<<index_with)-1;
    addr_t index=((addr>>offset_width)&(index_msk))  ;
    
    addr_t tag_msk=(1<<tag_width)-1;
    addr_t tag=((addr>>(offset_width+index_with))&(tag_msk))  ;

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