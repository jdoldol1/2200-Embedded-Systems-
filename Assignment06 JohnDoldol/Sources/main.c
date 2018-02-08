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
  void Inc(void);
  void Dec(void);
/********************************************************************/
//		Variables
/********************************************************************/
  unsigned int count;
  int loop;
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
	  
	  for (;;) 
	  {  
	    Top_16Out_C(count);
			switch(Get_Switches()) 
			{
			  case 0x10:
					while(Get_Switches()==0x10)
					{
					  Inc();
					}
					break;
			  case 0x04:
					while(Get_Switches()== 0x04)
					{
					  Dec();
					}         
					break;            
			  case 0x01:	                        
					count = 0x0000;  //clear count values           
					break;        	       
			}
			Delay_C(400);
			ClearAll(); 
			Delay_C(400); 	    
	  }    	
}
/********************************************************************/
//		Functions
/********************************************************************/
void Inc(void) 
    {
       count += 0x0001;
       Delay_C(25);
       Top_16Out_C(count);
    }
void Dec(void)
    {
       count -= 0x0001;
       Delay_C(25);
       Top_16Out_C(count);
    }

/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

