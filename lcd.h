#ifndef LCD_H
#define LCD_H

void lcd_init();
void lcd_string(unsigned char *);
void LCD_Command (unsigned char);
void lcd_write(unsigned char);
void delay(unsigned int);
#endif