#include "seven_segment.h"

void Seven_Segment_init(void)
{
	DDRB |= 0b00010111;
}

void Seven_Segment_display(int digit)
{
	digit %= 10;
	PORTB &= 0b11101000; 
	PORTB |= (((digit & 0b00001000) << 1) | (digit & 0b00000111));
}