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
#include "my_delays.h"
#include "switches.h"
#include "led_7seg.h"
/********************************************************************/
//		Library includes
/********************************************************************/


/********************************************************************/
//		Prototypes
/********************************************************************/
void ToggleIncChar(void);

/********************************************************************/
//		Variables
/********************************************************************/
unsigned char value;
unsigned char screenvalue;
unsigned char switches;
int column;
int toggle;
/********************************************************************/
//		Lookups
/********************************************************************/


void main() 

{
  /* put your own code here */   
	EnableInterrupts;
	
	lcdInit();                //initialize the LCD
	
	Set_R_C(1,15);             //put an X out to the screen row 1 col 15
	lcdData('a');  	
	
	Set_R_C(0,8);
	lcdString("John Doldol");
	
	Set_R_C(3,9);
	lcdData(0xb7);
	//Populate the LCD labels
	lcdLabels("Label 0:","Label 1:","Label 2:","Label 3:");
	
  value = 'A';
  toggle = 1;
  
  column = 8;
  screenvalue = 0x00;
  LEDS_7Seg_Init_C();
  Sw_Init();

  for(;;) 
  {  
      //ToggleIncChar();
      
      switches = Get_Switches();
      switch(switches) 
      {
        case 0x10:
          screenvalue += 0x01;
          break;
        case 0x04:
          screenvalue -= 0x01;
          break; 
        case 0x01:
        column++;
          Set_R_C(2,column);
          lcdData(screenvalue);
          break;
      }      
      
      Bot_8Out_C(screenvalue);
      Wait_for_Switches_up_mask(switches);
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


/********************************************************************/
//		Functions
/********************************************************************/

void ToggleIncChar(void) 
{
     Set_R_C(1,15);
    lcdData(value);
    
    if(toggle)
    {
         value += 0x20;
         Delay_C(1000);
    } 
    else
    {
         value -= 0x1f;
         Delay_C(2000);
    }           
    
    if(value == 'z')
    {
        value = 0x41; 
    }
    
    toggle = !toggle;
}


/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

