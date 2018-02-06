/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			DATE

// Details: A more detailed explanation of the program is entered here
/********************************************************************/


#include <hidef.h>      		/* common defines and macros 		*/
#include "derivative.h"      	/* derivative-specific definitions 	*/
/********************************************************************/
//		Library includes
/********************************************************************/
#include "led_7seg.h"
#include "switches.h"
#include "my_delays.h"

/********************************************************************/
//		Prototypes
/********************************************************************/


/********************************************************************/
//		Variables
/********************************************************************/ 
 unsigned char msec;
 unsigned char mmsec;
 unsigned char seconds;
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
  Sw_Init();
  msec = 0x09;
  mmsec = 0x09;
  seconds = 0x09;  
  for (;;) 
  {     
    mmsec -= 0x01;
    if(mmsec == 0xff)    
    {
      mmsec = 0x09;
      msec -= 0x01;
      if(msec == 0xff) 
      {
        msec = 0x09;
        seconds -= 0x01;
        if(seconds == 0xff) 
        {
          seconds = 0x09;
        }        
      }  
    }
    
    Char_Cust7Seg_C(7,mmsec);
    Char_Cust7Seg_C(6,msec);
    Char_Cust7Seg_C(5,seconds);
    Delay_C(50);     
  }    	
}



/********************************************************************/
//		Functions
/********************************************************************/




/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

