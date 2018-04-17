/********************************************************************/
// HC12 Program:	Real Clock (Timer and Interrupts)
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			Yimin Yan
// Date:			  3/29/2018

// Details: A more detailed explanation of the program is entered here
/********************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
#include <math.h>			      // ANSI C Mathematical functions
#include <stdlib.h>
#include <string.h>
#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
// #include "A2D_Lib_C.h"
// #include "SCI_LIB_C.h"
// #include "Delay_C.h"
// #include "LCD_C.h" 
// #include "LEDS_7Seg_C.h"
 #include "Misc_Lib.h"
// #include "RYG_LEDs_C.h"
// #include "Switches_C.h"






/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/

/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{  
  /* put your own code here */   
	
	// SCI0_Init19200();
	// lcdInit();
  // Sw_Init();
	// LEDS_7Seg_Init();
	// led_sw_init();
	// Sw_Init();
	// ATD0_Init();  
	           
	// Question: need 210Hz, at 50% duty cycle. Required TCNT at least 4500. (TCNT is the number of tick!)       
	// Step 1:   210Hz / 0.5 = 420Hz, Time interval duration: 1 / 420Hz = 2.380952 ms (DON'T ROUND!)
	// Step 2:   use Time interval duration divided by TCNT: 2.380952ms / 4500 = 529.1005 nano second
	//           so one tick should take 529.1005 nano second.
	// Step 3:   we need prescaler to set tick duration.
	//           529.1005 ns / 125 ns = 4.2328.     
	//           Prescaler = log(4.2328) / log(2) = (int)2.08 = 2 = 0b00000010;
	// Step 4:   actual tick duration = 2^Prescaler * 125ns = 500ns;
	//           TCNT: use 2.389052 ms (Don't round) divided by 500ns = 4762!
	// Step 5:   Make sure EnableInterrupts, Then measure pulse signal from pin9!
	
	TimeSetup(4762, 0b00000010);
	
	EnableInterrupts; // YOU NEED THIS TO MAKE TIMER INTERUPT WORK!
	
  for(;;) {        
    asm WAI;
  } /* loop forever */
  /* please make sure that you never leave main */
}
/**************************************************************************
*		Function:  Note that functions reside outside of Main - so if you call
*              these from within Main, you must include its prototype     
*              above
***************************************************************************/



/********************************************************************
*		Interrupt Service Routines
********************************************************************/
interrupt VectorNumber_Vtimch0 void TimerInterval(void){
  TFLG1 |= 0b00000001;
  TC0 += 4762;
}

/*******************************************************************/
