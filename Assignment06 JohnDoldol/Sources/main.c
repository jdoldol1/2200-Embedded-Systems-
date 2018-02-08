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
  unsigned int count;
  int loop;
  int base;
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
	  count = 0x0000;
	  loop = 0;
	  base = 1;
	  for (;;) 
	  {  
	    Top_16Out_C(count);	    
			
			
			
			if(loop > 5){
				    base = 20;
					}
					
					
			switch(Get_Switches()) 
			{
			  case 0x10:
			    loop++;
			    Delay_C(100);
			    count += base;					
					break;
			  case 0x04:
			    loop++;
			    count -= base;
			    Delay_C(100);					        
					break;            
			  case 0x01:	                        
					count = 0x0000;  //clear count values           
					break;
			  case 0x00:
			    loop = 0;
			    base = 1;
			    break;
			}
			Top_16Out_C(count); 	    
	  }    	
}
/********************************************************************/
//		Functions
/********************************************************************/


/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

