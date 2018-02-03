#include "keyboard_map.h"
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C

void kb_init(void);
void keyboard_handler_main(void);


extern void kprint_char(const char str);
extern void kprint(char str);
extern unsigned char keyboard_map[128];
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

void keyboard_handler_main(void)
{
    unsigned char status;
    char keycode;

    /* write EOI */
    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if(keycode < 0)
            return;

        if(keycode == ENTER_KEY_CODE) {
            kprint_newline();
            return;
        }

        char key =  keyboard_map[(unsigned char) keycode];
        kprint_char(key);
        //vidptr[current_loc++] = keyboard_map[(unsigned char) keycode];
        //vidptr[current_loc++] = 0x07;
    }
}

void kb_init(void)
{
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    write_port(0x21 , 0xFD);
}
