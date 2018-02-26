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
#include "LCD_C.h"
#include "switches.h"
#include "led_7seg.h"
/********************************************************************/
//		Library includes
/********************************************************************/


/********************************************************************/
//		Prototypes
/********************************************************************/

unsigned int HexToBCD(unsigned int value);
/********************************************************************/
//		Variables
/********************************************************************/
unsigned char switches;
unsigned int value;
/********************************************************************/
//		Lookups
/********************************************************************/
            

void main() 

{
  /* put your own code here */   
	EnableInterrupts;
	
	lcdInit();                //initialize the LCD  
  LEDS_7Seg_Init_C();
  Sw_Init(); 
  value = 0x0000;
  for(;;) 
  {  
      //ToggleIncChar();
     switches = Get_Switches(); 
     switch(switches)
     {
      case 0x04:
            value -= 0x0001;
            break;
      case 0x02:
            value -= 0x0100;
            break;
      case 0x08:
            value += 0x0100;
            break;
      case 0x10:
            value += 0x0001;
            break; 
      case 0x01:
            if(value>0x270F) 
            {
               	Set_R_C(1,4);
	              lcdString("Input number");
	              Set_R_C(2,6);
	              lcdString("too high!");
            } 
            else
            {
              Bot_16Out_C(HexToBCD(value));
            };
            break;     
     }        
      Top_16Out_C(value);
      Wait_for_Switches_up_mask(switches);
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


/********************************************************************/
//		Functions
/********************************************************************/
unsigned int HexToBCD(unsigned int value)
{
    unsigned int ret = 0x0000;     
    unsigned int div = 0x03e8;
    int i;
    for(i = 0; i < 4; ++i)
    {
       ret = ret << 4;
       ret += value / div;
       value %= div;
       div /= 0x000A;
      
    }
    return ret;   
    
}

/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

