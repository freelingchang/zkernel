typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

struct gdt_descriptor{
    u16 limit_low;
    u16 base_low;
    u8  base_mid;
    u8  access;
    u8  granularity;
    u8  base_high;
} __attribute__((packed));

struct gdtr_struct{
    u16 limit;
    u32 base;
}__attribute__((packed));
