#include "LCD.h"

void LCD_init(void)
{
	SET_BIT(DDRA, 2);
	SET_BIT(DDRA, 3);
	SET_BIT(DDRB, 0);
	SET_BIT(DDRB, 1);
	SET_BIT(DDRB, 2);
	SET_BIT(DDRB, 4);
	
	_delay_ms(15);
	LCD_Command(0x02); // Home LCD
	LCD_Command(0x28); // 2-Lines,5x8 matrix and 4-bit mode 
	LCD_Command(0x0c); // Display On , Cursor Off
	LCD_Command(0x01); // clear Display screen
	LCD_Command(0x80); // cursor to the first Line
} 

void LCD_Command(unsigned char cmd)
{
	CLR_BIT(PORTA, 3); // RS=0
	
	PORTB &= 0b11101000; // Pin 0,1,2,4 
	unsigned char high = (cmd & 0xf0) >> 4;					//1111 0000		=>	 	//0000 1111
	unsigned char temp = ((high & 0b00001000) << 1) | (high & 0b00000111);			//0001 0111         
	PORTB |= temp;
	
	CLR_BIT(PORTA, 2); //ensure EN it is low
	SET_BIT(PORTA, 2);  // change to High
	_delay_ms(1);           
	CLR_BIT(PORTA, 2); //change to Low
	
	
	PORTB &= 0b11101000;
	unsigned char low = cmd & 0x0f;
	unsigned char temp2 = ((low & 0b00001000) << 1) | (low & 0b00000111);
	PORTB |= temp2;
	
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);

	_delay_ms(5);
}

void LCD_PutChar(unsigned char chr)
{
	SET_BIT(PORTA, 3); // RS=1
	
	PORTB &= 0b11101000;
	unsigned char high = (chr & 0xf0) >> 4;					//1111 0000		=>	 	//0000 1111
	unsigned char temp = ((high & 0b00001000) << 1) | (high & 0b00000111);			//0001 0111
	PORTB |= temp;
	
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);
	
	
	PORTB &= 0b11101000;
	unsigned char low = chr & 0x0f;
	unsigned char temp2 = ((low & 0b00001000) << 1) | (low & 0b00000111);
	PORTB |= temp2;
	
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 2);
	_delay_ms(1);
	CLR_BIT(PORTA, 2);

	_delay_ms(5);

}

void LCD_PutString(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		LCD_PutChar(str[i]); 
	}
}

void LCD_Clear()
{
	LCD_Command(0x01);
	_delay_ms(10);
}

void LCD_gotoxy(unsigned char row, unsigned char col)
{
	unsigned char address = 0;
	switch(row)
	{
		case 0:
		address = col;
		break;
		case 1:
		address = col + 0x40;
		break;
		case 2:
		address = col + 0x14;
		break;
		case 3:
		address = col + 0x54;
		break;
	}
	LCD_Command(address | 0x80);
}
