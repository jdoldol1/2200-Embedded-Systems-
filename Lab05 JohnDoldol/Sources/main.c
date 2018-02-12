/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			  February 12, 2018

// Details:     8bit counter displays on 7segment LED with switches
/********************************************************************/


#include <hidef.h>      		/* common defines and macros 		*/
#include "derivative.h"      	/* derivative-specific definitions 	*/
/********************************************************************/
//		Library includes
/********************************************************************/
 #include "my_delays.h"
 #include "led_7seg.h"
 #include "switches.h"

/********************************************************************/
//		Prototypes
/********************************************************************/
void TogglePA6(void);
/********************************************************************/
//		Variables
/********************************************************************/

unsigned char bcount;
int timer;
/********************************************************************/
//		Lookups
/********************************************************************/

void main(void)
{ 


// main entry point
_DISABLE_COP();


/********************************************************************/
// initializations
/********************************************************************/
 
    LEDS_7Seg_Init_C();
    DDRA |= 0xff;
	  bcount = 0x00;
	  timer = 0;
	  for (;;) 
	  {   	     
	  
	     if(timer % 333 == 0) 
	     {
	         Bot_8Out_C(++bcount);
	     }
	     if(timer % 100 == 0) 
	     {  	     
	       TogglePA6();
	     }
	     timer++; 
	     Delay_C(1); 
	  }    	
}
/********************************************************************/
//		Functions
/********************************************************************/
void TogglePA6(void)
{
  asm LDAA PORTA
  asm EORA #$40
  asm STAA PORTA
}

/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

