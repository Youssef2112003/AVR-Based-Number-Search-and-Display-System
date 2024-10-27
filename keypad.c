#include "KEYPAD.h"

const unsigned char arr[4][4]= {{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'&','0','=','+'}
};
void Keypad_init(){
	// inputs(columns)
	CLR_BIT(DDRD,7);
	CLR_BIT(DDRD,6);
	CLR_BIT(DDRD,5);
	CLR_BIT(DDRD,3); 
	// outputs (rows)
	SET_BIT(DDRC,5);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,2);
	
	
	SET_BIT(PORTD,7);
	SET_BIT(PORTD,6);
	SET_BIT(PORTD,5);
	SET_BIT(PORTD,3);
	_delay_ms(5);
}
unsigned char Keypad_Read(void){
	unsigned char col,row,ans = INVALID_KEYPAD_PRESS; // three variables for scanning Keypad
	for (row=5;row>=2;row--) // loop on output pins
	{
		PORTC |= 0b00111100; // 2 3 4 5
		CLR_BIT(PORTC,row); // check rows in for loop
		for (col=7;col>=3;col--) // loop on inputs 
		{
			if (col==4)
			{
				col--;
			}
			if (GET_BIT(PIND,col)==0)
			{
				_delay_ms(120);
				if (GET_BIT(PIND,col)==0)
				{
					if (col==3) // special case pin 3
					{
						ans=arr[5-row][7-col-1];
						break;
					}
					else 
					{ // all cases pin 5,6,7
						ans=arr[5-row][7-col];
						break;
					}
					
				}
			}
		}
	}
	return ans;
}