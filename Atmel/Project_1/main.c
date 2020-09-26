/*
* Project_1.c
*
* Created: 9/14/2020 14:48:48
* Author : Gage Gosset
*/

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
DDRD Pin Numbers
pinB = 7; //7
pinC = 6; //6
pinD = 5; //5
pinE = 4; //4
pinF = 3; //3
pb = 2;   //2
pinG = 1; //1
pinA = 0; //0

DDRB Pin Numbers
pinDP = 0;//8
D4 = 1;   //9
D3 = 2;   //10
D2 = 3;   //11
D1 = 4;   //12    */

//number bits
short num0bit = ~0B11111001; //0 disp bits
short num1bit = ~0B11000000; //1 disp bits
short num2bit = ~0B10110011; //2 disp bits
short num3bit = ~0B11100011; //3 disp bits
short num4bit = ~0B11001010; //4 disp bits
short num5bit = ~0B01101011; //5 disp bits
short num6bit = ~0B01111011; //6 disp bits
short num7bit = ~0B11000001; //7 disp bits
short num8bit = ~0B11111011; //8 disp bits
short num9bit = ~0B11001011; //9 disp bits

volatile int state = 0; //Button State

int debFlag = 0; //Disable interrupts (debounce flag)
int debTime = 0; //Debounce time counter

//7 seg disp digits
int dig1 = 0;
int dig2 = 0;
int dig3 = 0;
int dig4 = 0;

int main(void)
{
	//Timer interrupt setup
	cli();//stops all interrupts
	TCCR1A = 0;//set TCCR1A register = 0
	TCCR1B = 0;//set TCCR1B register = 0
	TCNT1  = 0;//starting counter value
	OCR1A = 624;// time when the timer interrupt is tripped
	TCCR1B |= (1 << WGM12);//timer1 turn on CTC (compare match)
	TCCR1B |= (1 << CS12);//pre-scaler of 256
	TIMSK1 |= (1 << OCIE1A);//enable timer compare interrupt
	sei();//allows for interrupts again

	//Button interrupt setup
	EIMSK = 0b00000001;
	PORTD = (1 << PORTD2); //Turn on pullup resistor

	DDRD = 0B11111011; //set pins 0-7 & !2 to output and pin 2 to input
	DDRB = 0B11111111; //set pins 8-13 to output

	//Set all ouput pins to low;
	PORTB =  0B00000001;
	PORTD = ~0B00000000;

	while (1)
	{
		//Loop

		if(dig1!=0){
			PORTB = 0B00010001;
			dispNum(dig1);
			_delay_ms(1);
		}

		PORTB = 0B00001000;
		dispNum(dig2);
		_delay_ms(1);

		PORTB = 0B00000101;
		dispNum(dig3);
		_delay_ms(1);

		PORTB = 0B0000011;
		dispNum(dig4);
		_delay_ms(1);
		
	}
}

//function that gets passed an integer value 0-10 and sets the proper pins to display that number on a 7 seg display
void dispNum (int num) {

	switch (num) {
		case 0:
		PORTD = num0bit;
		break;

		case 1:
		PORTD = num1bit;
		break;
		
		case 2:
		PORTD = num2bit;
		break;

		case 3:
		PORTD = num3bit;
		break;

		case 4:
		PORTD = num4bit;
		break;

		case 5:
		PORTD = num5bit;
		break;
		
		case 6:
		PORTD = num6bit;
		break;

		case 7:
		PORTD = num7bit;
		break;

		case 8:
		PORTD = num8bit;
		break;

		case 9:
		PORTD = num9bit;
		break;
		
		default:
		PORTD = num0bit;
		break;
	}
}


//Push button interrupt
ISR(INT0_vect){
	cli();

	EIMSK = 0b00000000; //Disable pb interrupt
	debFlag = 1;

	if (state==0){
		state = 1;
		} else{
		state = 0;
	}
}

//Timer interrupt
ISR(TIMER1_COMPA_vect) {
	
	//Debounce counter
	if(debFlag == 1){
		if(debTime>=50){
			debTime=0;
			debFlag=0;
			EIMSK = 0b00000001;
			}else{
			debTime++;
		}
	}

	//Counter incrementing
	if(state==1){
		dig4++;
		if (dig4>9){
			dig3++;
			dig4=0;
			if(dig3>9){
				dig2++;
				dig3=0;
				if (dig2>9){
					dig1++;
					dig2=0;
				}
			}
		}
	}
}





