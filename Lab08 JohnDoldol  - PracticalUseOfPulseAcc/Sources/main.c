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
 #include "Delay_C.h"
 #include "LCD_C.h" 
 #include "LEDS_7Seg_C.h"
 #include "Misc_Lib.h"
// #include "RYG_LEDs_C.h"
// #include "Switches_C.h"






/********************************************************************
*		Prototypes
********************************************************************/



/********************************************************************
*		Variables
********************************************************************/
unsigned int _count = 0;
char text[20];
/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{  
  /* put your own code here */   
	
	// SCI0_Init19200();
	 lcdInit();
  // Sw_Init();
	 LEDS_7Seg_Init();
	// led_sw_init();
	// Sw_Init();
	// ATD0_Init();  	
	
	// EnableInterrupts; // Question here? what is this line of code.
	
	PACTL = 0x40;

  lcdLabels("  WIND SPEED SENSOR", "SENSOR FREQ: ", "WIND SPEED: ", "");
	
  for(;;) {
    Delay_C(1000);  
    _count = PACN32;        
    Top_16Out(HexToBCD(_count));
    
    Set_R_C(1, strlen("SENSOR FREQ: "));	
    if(sprintf(text, " %d HZ", _count) >= 0) {
      lcdString(text);
    }
    
    Set_R_C(2, strlen("WIND SPEED: "));	
    if(sprintf(text, " %1.0f KPH", _count * 0.1949 + 1.0415) >= 0) {
      lcdString(text);
    }
    
    PACN32 = 0;
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


/*******************************************************************/

