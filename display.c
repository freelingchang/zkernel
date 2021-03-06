#include "display.h"
#include "common.h"

extern int current_loc;
extern  char *vidptr;
void set_ratio(){
    //s_set_ratio();
}

void kprint_char(const char str)
{
    vidptr[current_loc++] = str;
    vidptr[current_loc++] = 0x07;
    move_cursor();
}

void kprint(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
        vidptr[current_loc++] = str[i++];
        vidptr[current_loc++] = 0x07;
    }
    move_cursor();
}

void kprint_newline(void)
{
    unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc = current_loc + (line_size - current_loc % (line_size));
    kprintCmd();
    move_cursor();
}


void kprintEnter(){
    if (current_loc <=0){
        return;
    }
    unsigned int line_size = COLUMNS * 2;
    if (current_loc < line_size ){
        current_loc = line_size;
        return;
    }
    current_loc =  current_loc + (line_size -  current_loc%line_size);
    //kprintCmd();
    move_cursor();
}

void kprintCmd(){
    //kprint_newline();
    kprint(">");
    move_cursor();
}
void move_cursor()
{
    // 屏幕是 80 字节宽
    uint16_t cursorLocation = current_loc/2;

    
    // 在这里用到的两个内部寄存器的编号为14与15，分别表示光标位置
    // 的高8位与低8位。

    outb(0x3D4, 14);                    // 告诉 VGA 我们要设置光标的高字节
    outb(0x3D5, cursorLocation >> 8);   // 发送高 8 位
    outb(0x3D4, 15);                    // 告诉 VGA 我们要设置光标的低字节
    outb(0x3D5, cursorLocation);        // 发送低 8 位
}
