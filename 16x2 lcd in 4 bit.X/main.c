#include <xc.h>                    //header file
#define _XTAL_FREQ 20000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2


void lcd_command( unsigned char command)
{
    PORTB = (command &0xF0);
    RS = 0;
    RW = 0;
    EN = 1; 
        __delay_ms(2);
    EN = 0;
    PORTB = ((command<<4) & 0XF0);
    RS = 0;
    RW = 0;
    EN = 1; 
        __delay_ms(2);
    EN = 0;
    
    
}
void lcd_data (unsigned char data)
{
  PORTB = (data & 0xF0);
    RS = 1;
    RW = 0;
    EN = 1; 
    __delay_ms(2);
    EN = 0;
    PORTB = ((data<<4)& 0xF0);
    RS = 1;
    RW = 0;
    EN = 1; 
    __delay_ms(2);
    EN = 0;
}

void lcd_initialize()
{
    lcd_command(0x02);
    lcd_command(0x28);
    lcd_command(0x0c);
    lcd_command(0x06);
    lcd_command(0x01);
}
void lcd_string(const unsigned char *string, unsigned char num)
{
    unsigned char i;
    for(i=0; i<num;i++)
    {
        lcd_data(string[i]);
    }
}
    

void main(void) {
    TRISB= 0x00;
    lcd_initialize();
    while(1)
    {
     lcd_command(0x80);
     lcd_string("RAMYA",5);
     lcd_command(0xc0);
     lcd_string("GOWDA",5);
    }
    return;
}






