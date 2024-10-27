#include "searching.h"

int main(void)
{
    // Initiation:
	Keypad_init();	
	LEDs_init();
	LCD_init();
	
	input_Numbers();
	input_Target();
	Search();
	Display_Positions();
	
    while (1) 
    {
    }
}

