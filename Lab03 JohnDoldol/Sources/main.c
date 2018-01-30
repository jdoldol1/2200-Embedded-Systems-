/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			January 30, 2018

// Details: A more detailed explanation of the program is entered here
/********************************************************************/


#include <hidef.h>      		/* common defines and macros 		*/
#include "derivative.h"      	/* derivative-specific definitions 	*/
/********************************************************************/
//		Library includes
/********************************************************************/

#include "switches.h"
#include "led_ryg.h"
#include "my_delays.h"


/********************************************************************/
//		Prototypes
/********************************************************************/


/********************************************************************/
//		Variables
/********************************************************************/

  unsigned char switches;
  
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
 
  led_sw_init();
  for (;;)
	{
	//main program loop
	  switches = Get_Switches();
	  
	  if(switches == 0x18) 
	  { 	  
	      PT1AD1 += 0x20;
	      Wait_for_Switches_up_mask(0x10);	      
	  } 
	  else if(switches == 0x0C) 
	  {
	      PT1AD1 -= 0x20;
	      Wait_for_Switches_up_mask(0x04);
	  } 
	  else if(switches == 0x01) 
	  {
	      Clear_Led();
	  } 	  	  	  
	}
}



/********************************************************************/
//		Functions
/********************************************************************/




/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

