#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include "lcd.h"

/* Define value to be loaded in timer for PWM period of 20 milliseconds */
#define PWM_Period 0xB7FE

sbit Servo_Motor_Pin = P2^0;
sbit k1 = P3^1; // K1 button connected to P3.1
sbit k2 = P3^0; // K2 button connected to P3.0

unsigned int ON_Period, OFF_Period, DutyCycle;

void delay(unsigned int count) {
    unsigned int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < 112; j++);
}

void lcd_string(unsigned char *lcd_data) {
    while (*lcd_data) {
        lcd_write(*lcd_data++);
    }
}

void lcd_clear() {
    LCD_Command(0x01);  /* Clear display */
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
    if (row == 1) {
        LCD_Command(0x80 + col - 1);
    } else if (row == 2) {
        LCD_Command(0xC0 + col - 1);
    }
}
// Function to update LCD display with servo position
void Update_LCD_Display(int position) {
    char lcd_buffer[16];
    sprintf(lcd_buffer, "Servo Pos: %d    ", position);  // Extra spaces to clear previous content
    lcd_clear();
    lcd_set_cursor(1, 1);
    lcd_string(lcd_buffer);
}

void Timer_init() {
    TMOD = 0x01;        /* Timer0 mode1 */
    TH0 = (PWM_Period >> 8);/* 20ms timer value */
    TL0 = PWM_Period;
    TR0 = 1;        /* Start timer0 */
}

/* Timer0 interrupt service routine (ISR) */
void Timer0_ISR() interrupt 1 {
    Servo_Motor_Pin = !Servo_Motor_Pin;
    if (Servo_Motor_Pin) {
        TH0 = (ON_Period >> 8);
        TL0 = ON_Period;
    } else {
        TH0 = (OFF_Period >> 8);
        TL0 = OFF_Period;
    }
}

/* Calculate ON & OFF period from duty cycle */
void Set_DutyCycle_To(float duty_cycle) {
    float period = 65535 - PWM_Period;
    ON_Period = ((period / 100.0) * duty_cycle);
    OFF_Period = (period - ON_Period);    
    ON_Period = 65535 - ON_Period;    
    OFF_Period = 65535 - OFF_Period;
}

int main() {
    EA  = 1;        /* Enable global interrupt */
    ET0 = 1;         /* Enable timer0 interrupt */
    Timer_init();
    DutyCycle = 2; // Initialize duty cycle to 2%
    lcd_init();

    while (1) {
        if (k1 == 0) {
            // K1 button is pressed, move to 180 degrees
            while (k1 == 0);  // Wait for button release (debouncing)
            DutyCycle = 12; // Set duty cycle to 12% for 180-degree rotation
            Update_LCD_Display(180);
        } else if (k2 == 0) {
            // K2 button is pressed, move to 1 degree
            while (k2 == 0);  // Wait for button release (debouncing)
            DutyCycle = 2; // Set duty cycle to 2% for 1-degree rotation
            Update_LCD_Display(0);
        }
        Set_DutyCycle_To(DutyCycle);
        delay(500);
    }
}

