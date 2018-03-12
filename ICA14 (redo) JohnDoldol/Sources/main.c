/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			DATE

// Details: A more detailed explanation of the program is entered here
/********************************************************************/


#include <stdio.h>
#include <hidef.h>      		/* common defines and macros 		*/
#include "derivative.h"      	/* derivative-specific definitions 	*/
#include "A2D_C.h"
#include "LCD_C.h"
#include "my_delays.h"
/********************************************************************/
//		Library includes
/********************************************************************/


/********************************************************************/
//		Prototypes
/********************************************************************/


/********************************************************************/
//		Variables
/********************************************************************/

unsigned int reading = 0;
char s[20];
double voltage = 0;
double temperature = 0;
unsigned int sample = 0;
/********************************************************************/
//		Lookups
/********************************************************************/


void main(void)
{
// main entry point
_DISABLE_COP();

ATD0_Init();
lcdInit();

/********************************************************************/
// initializations
/********************************************************************/
 
 lcdLabels("Sample: ", "Voltage: ", "Temp: ", " ");
  
  for (;;)     
	{    
	
	 	
	  reading = ATD0_Sample7(); 
	  
	  sample += 1;
	  voltage = reading * 0.005;
	  temperature = (voltage * 1.56) + 22;
	  
	  Set_R_C(0,10);
    if(sprintf(s,"%03X",reading) > 0)  
    {
      lcdString(s);
    }
    	
    Set_R_C(1,10);
    if(sprintf(s,"%4.3f V", voltage) > 0)
    {            
     lcdString(s);
    }
    
    Set_R_C(2,10);
    if(sprintf(s,"%2.1f C", temperature) > 0)
    {            
     lcdString(s);
    }	
    
    
    Set_R_C(3,0);
    if(sprintf(s,"Sample # %d",sample) > 0)
    {         
     lcdString(s);
    }	
    
    Delay_C(1000);
	}
	
}



/********************************************************************/
//		Functions
/********************************************************************/




/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/
