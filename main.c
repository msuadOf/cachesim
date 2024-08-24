#include <stdio.h>
#include <stdlib.h>
#include "cachesim.h"
char *mem;
typedef struct
{
    uint32_t u7_0 : 8;
    uint32_t u15_8 : 8;
    uint32_t u23_16 : 8;
    uint32_t u31_24 : 8;
} word32_u;

void init_memory(void)
{
    mem = malloc(0x100000000UL * sizeof(char));
}
cachesim_word_t mem_read(cachesim_addr_t addr, int len)
{
    cachesim_word_t data = 0;
    for (int i = 0; i < len; i++)
    {
        data |= (mem[addr + i] & 0xffUL) << (8 * i);
    }
    return data;
}
void mem_write(cachesim_addr_t addr, int len, cachesim_word_t data)
{
    switch (len)
    {
    case 1:
        mem[addr] = data & 0xffUL;

        break;
    case 2:
        mem[addr] = data & 0xffUL;
        mem[addr + 1] = data >> 8 & 0xffUL;
        break;
    case 4:
        mem[addr] = data & 0xffUL;
        mem[addr + 1] = data >> 8 & 0xffUL;
        mem[addr + 2] = data >> 16 & 0xffUL;
        mem[addr + 3] = data >> 24 & 0xffUL;
        break;

    default:
        break;
    }
}
int main(void)
{
    printf("Hello World!\n");
    init_memory();
    init_cachesim(mem_read, mem_write, 12, 2);

    for (int i = 0; i < 0x100; i++)
    {
        uint32_t num = i;
        mem_write(i, 4, num);
        if (mem_read(i, 4) != num)
        {
            printf("Error at %d[0x%x,0x%x,0x%x,0x%x]\n", i, i, mem_read(i, 4), mem[i], mem[i + 1]);
        }
    }
    free(mem);
    return 0;
}