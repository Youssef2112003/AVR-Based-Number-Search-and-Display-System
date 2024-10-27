#include "searching.h"
// 1 3 5 0 2 1 -1 0 0 0 0 0 0
// 0

void Searching_init()
{
	for (int i = 0; i < size; i++)
	{
		numbers[i] = 0;
		positions[i] = -1;
	}
	target = pos = 0;
}

void input_Numbers()
{
	LCD_PutString("Enter Numbers: ");
	LCD_gotoxy(1,0);
	int max = 0;
	while (1)
	{
		char key = Keypad_Read();
		if (key >= '0' && key <= '9')
		{
			LCD_PutChar(key); // key is char in PutChar
			numbers[pos] = numbers[pos] * 10 + (key - '0'); // store key as integer in array
			max++;
		}
		else if (key == '+')
		{
			pos++;
			LCD_PutString(",");
		}
		else if (key == '&' || max == 16) // exit from entering
		{
			numbers[pos + 1] = -1; // i end to put char
			_delay_ms(120);
			return;
		}
		_delay_ms(120);
	}
}

void input_Target()
{
	LCD_Clear();
	LCD_PutString("Enter Target: ");
	while (1)
	{
		char key = Keypad_Read();
		if (key >= '0' && key <= '9')
		{
			LCD_PutChar(key);
			target = target * 10 + key - '0';
		}
		if (key == '&')
		{
			return;
		}
			_delay_ms(120);
	}
}

void Search()
{
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] == -1) // Not Found
		{
			return;
		}
		if (target == numbers[i])
		{
			positions[j] = i;
			j++;
		}
	}
}

void LEDs_init()
{
	DDRA = 0b01110000; // Pin 4,5,6 PORTA
	SET_BIT(DDRB,7); // Pin 7 LED
}

void LEDs_ON(int i)
{
	switch(i)
	{
		case 0: SET_BIT(PORTA, 4); return;
		case 1: SET_BIT(PORTA, 5); return;
		case 2: SET_BIT(PORTA, 6); return;
		case 3: SET_BIT(PORTB, 7); return;
	}
}

void LEDs_OFF()
{
	CLR_BIT(PORTA, 4);
	CLR_BIT(PORTA, 5);
	CLR_BIT(PORTA, 6);
	CLR_BIT(PORTB, 7);
}

// positions => 0 2 5 15
// 0 => 0000
// 2 => 0010
// 5 => 0101
// 16 => 1111
	// test
	// 	positions[0] = 0;
	// 	positions[1] = 2;
	// 	positions[2] = 5;
	// 	positions[3] = 15;
	// 	positions[4] = -1;

void Display_Positions()
{
	Seven_Segment_init();
	LCD_Clear();
	LCD_PutString("Positions...");
	
	for (int i = 0; i < size; i++)
	{
		int num = positions[i];
		if (num == -1)return;
		
		Seven_Segment_display(num);		//display 7-segment
		
		for (int j = 0; j < 4; j++)		//display Leds
		{
			if (num % 2 != 0)
			{
				LEDs_ON(j);
			}
			num /= 2;
		}
		
		_delay_ms(1000);
		LEDs_OFF();
	}
}