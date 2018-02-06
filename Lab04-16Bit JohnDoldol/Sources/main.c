/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			  February 6, 2018

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


/********************************************************************/
//		Variables
/********************************************************************/
  unsigned int topcount;
  unsigned int botcount;
  unsigned char switches;
  int toggle = 1;

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
  topcount = 0x0000;
  botcount = 0x0000;
  for (;;) 
  {
      switches = Get_Switches();   
	    
	    switch(switches) 
	    {
	      case 0x10:
	            topcount += 0x0001; //increment topcount	            
	            break;
	      case 0x04:
	            botcount -= 0x0001;	//decrement botcount            
	            break;            
	      case 0x01:	                        
	            topcount = 0x0000;  //clear count values
	            botcount = 0x0000;	            
	            break;
	      case 0x02:      	            
	            toggle = !toggle; //toggle boolean for display switch          
              break;  
	    }
	    
	    //display both counts
	    if(toggle) 
	    {
	         Top_16Out_C(topcount);
	         Bot_16Out_C(botcount);
	    } 
	    else 
	    {
    	     Top_16Out_C(botcount);
    	     Bot_16Out_C(topcount);
	    }
	    
	    //debounce
	    Wait_for_Switches_up_mask(switches);
  }   	
}



/********************************************************************/
//		Functions
/********************************************************************/




/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

