#include "derivative.h"
#include "led_7seg.h"

/*
;________________________________________________________
;                                                        
;    Library:  LEDS_7Seg.inc                             
;                                                        
;    Contains: Bot_8Out                                          
;              Bot_16Out                                 
;              Char_7Seg                                 
;              Char_7Seg_D                               
;              Clear_7Seg                                
;              LEDS_7Seg_Init                            
;              Seg_write                                 
;              Top_8Out                                
;              Top_16Out                                 
;    Author:   John Doldol                                           |
;                                                        
;    Last Modified: February 1 2018(Created)            
;________________________________________________________

;________________________________________________________
;           
;             Bot_8Out
;
;       Requires:       unsigned char input parameter
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: This routine places input data on
;       the bottom row of the 7 segement LEDS, upper
;       two digits of row are blanked
;
;________________________________________________________
*/
void Bot_8Out_C(unsigned char c) 
{
  unsigned char val;
  
  Clear_7Seg(0x04);
  Clear_7Seg(0x05);
  
  val = c >> 4;			    //move upper nibble to lower
  Char_7Seg_C(6,val);   //send nible to poisition 6
  
  val = c & 0x0f;		    //only lower nibble needed
  Char_7Seg_C(7,val);   //send lower nible to position 7
}

/*
;________________________________________________________
;           
;             Bot_16Out_C
;
;       Requires:       16 bit data is in iIn
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: This routine places 16 bit data contained
;                in iIn on the bottom row of the 
;                7 segment LEDS
;________________________________________________________
*/
void Bot_16Out(unsigned int iIn)
{
	unsigned char val;

	val = iIn & 0x00ff;		//mask to obtain only two lower nibble
	Char_7Seg_C(7,val);		//send out to position 6 & 7 

	val = iIn >> 8;			//move upper two nibble to lowest
	Char_7Seg_C(5,val);		//send out to position 4 & 5

}
/*
;________________________________________________________
;           
;             Char_7Seg_C
;
;       Requires:       A has position, B has char
;                       (both in lower nibble)
;                       Character has NO decimal
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: Sends character in B to position in A
;________________________________________________________
*/

void Char_7Seg_C(unsigned char pos, unsigned char c) 
{             
  pos |= 0x50;
  PORTB = pos;
  
  PORTA = 0x02;
  PORTA = 0x03;
  
  PORTB = (c|=0x80); //no decimal point
  
  PORTA = 0x00;
  PORTA = 0x01;
}

/*
;________________________________________________________
;           
;             Char_7Seg_C_D
;
;       Requires:       A has position, B has char
;                       Character has no decimal
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: Sends character in b to position in A 
;________________________________________________________
*/
void Char_7Seg_C_D(unsigned char Pos, unsigned char character) 
{
	Pos |= 0x05;
	PORTB = Pos;

	PORTA = 0x02;
	PORTA = 0x03;

	PORTB = character;

	PORTA = 0x00;
	PORTA = 0x01;
}

/*
;________________________________________________________
;
;             Clear_7Seg_C
;
;       Requires:     Pos has position 
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: Clears all segments of char in position A
;________________________________________________________
*/

void Clear_7Seg(unsigned char Pos)
{
	Pos |= 0x70;
	PORTB = Pos;

	PORTA = 0x02;
	PORTA = 0x03;

	PORTB = 0x80;

	PORTA = 0x00;
	PORTA = 0x01;
}

/*
;________________________________________________________
;
;             LEDS_7Seg_Init_C
;
;       Requires:		None
;
;       Returns:        None
;       Regs Affected:  None
;
;       Details: This is a set of instructions to clear 
;		the memory of the 7 segment LED digits - 
;		used prior to writing anything to them
;________________________________________________________
*/

void LEDS_7Seg_Init_C(void)
{
	signed char i = 0;
	unsigned char Digit = 0;
	
	DDRA = 0x03;
	DDRB = 0xff;
	
	PORTA = 0x03;

	for (i = 8; i >= 0; i--)
	{
		Digit = (0x70 | i);
		PORTB = Digit;

		PORTA = 0b00000010;
		PORTA = 0b00000011;

		PORTB = 0b10000000;
		PORTA = 0b00000000;
		PORTA = 0b00000001;
		Digit++;
	}
}

/*
;________________________________________________________
;
;             Top_8Out_C
;
;       Requires:		unsigned char input parameter
;
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: This routine places input data on the 
;		top row of the 7 segment LEDS, 
		;upper two digits of row are blanked
;________________________________________________________
*/
void Top_8Out_C(unsigned char c)
{
	unsigned char val;

	Clear_7Seg(0x00);
	Clear_7Seg(0x01);

	val = c >> 4;			//move upper nibble to lower
	Char_7Seg_C(2, val); //send nible to poisition 6

	val = c & 0x0f;		//only lower nibble needed
	Char_7Seg_C(3, val);  //send lower nible to position 7
}

/*
;________________________________________________________
;
;             Top_16Out_C
;
;       Requires:		16 bit data is in iIn
;
;       Returns:        n/a
;       Regs Affected:  n/a
;
;       Details: This routine places 16 bit data contained 
;		iIn on the top row of the 7 segment LEDS
;________________________________________________________
*/

void Top_16Out_C(unsigned int iIn)
{
	unsigned char val;

	val = iIn & 0x00ff;		//mask to keep two lower nibbles only
	Char_7Seg_C(2,val);		//send out position 2 & 3

	val = iIn >> 8;			//move upper two bits to lowest
	Char_7Seg_C(0,val);		//send out to position 0 & 1;
}




