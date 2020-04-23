#include "gdt.h"

extern void gdt_flush(u32);
static void gdt_set_descriptor(int num,u32 base,u32 limit,u8 access,u8 gran);

struct gdt_descriptor gdt[5];
struct gdtr_struct gdtr;

void init_gdt(){

    gdtr.limit = (sizeof(struct gdt_descriptor) * 5 - 1);
    gdtr.base = (u32)&gdt;

    gdt_set_descriptor(0,0,0,0,0);
    gdt_set_descriptor(1,0,0xFFFFFFFF,0x9A,0xCF); //内核代码段
    gdt_set_descriptor(2,0,0xFFFFFFFF,0x92,0xCF); //内核数据段
    gdt_set_descriptor(3,0,0xFFFFFFFF,0xFA,0xCF); //用户代码段
    gdt_set_descriptor(4,0,0xFFFFFFFF,0xF2,0xCF); //用户数据段

    gdt_flush((u32)&gdtr);
}

void gdt_set_descriptor(int num,u32 base,u32 limit,u8 access,u8 gran){

    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0xF;
    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;

}
