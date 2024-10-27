#ifndef SEARCHING_H_
#define SEARCHING_H_

#include "LCD.h"
#include "keypad.h"
#include "seven_segment.h"

#define size 17 

int numbers[size], positions[size], target, pos;

void Searching_init(void);
void input_Numbers(void);
void input_Target(void);
void Search(void);
void Display_Positions_7Segment(void);
void LEDs_init();
void LEDs_ON(int);
void LEDs_OFF();
void Display_Positions();
void Display_Positions_LEDs();

#endif /* SEARCHING_H_ */