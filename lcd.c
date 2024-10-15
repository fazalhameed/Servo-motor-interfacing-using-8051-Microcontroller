#include <reg51.h>
#include "lcd.h"
#define LCD_data P0
sbit rs = P2^6;
sbit rw = P2^5;
sbit en = P2^7;
void lcd_clear();
void LCD_Command(unsigned char cmd) {
    LCD_data = cmd;
    rs = 0;       /* Command reg. */
    rw = 0;       /* Write operation */
    en = 1;
    delay(1);
    en = 0;
    delay(5);
}
void lcd_write(unsigned char lcd_data) {
    LCD_data = lcd_data;
    rs = 1;
    rw = 0;
    en = 1;
    delay(1);
    en = 0;
}
void lcd_init() {
    delay(20);      /* LCD Power ON Initialization time >15ms */
    LCD_Command(0x38);  /* Initialization of 16X2 LCD in 8-bit mode */
    LCD_Command(0x0E);  /* Display ON Cursor blinking */
    LCD_Command(0x06);  /* Auto Increment cursor */
    LCD_Command(0x01);  /* Clear display */
    LCD_Command(0x80);  /* Cursor at home position */
}

