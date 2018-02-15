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
/********************************************************************/
//		Library includes
/********************************************************************/


/********************************************************************/
//		Prototypes
/********************************************************************/


/********************************************************************/
//		Variables
/********************************************************************/
unsigned char value;
int toggle;
/********************************************************************/
//		Lookups
/********************************************************************/


void main() 

{
  /* put your own code here */
  
  char str[19] = "My Cats"; 
	EnableInterrupts;
	
	lcdInit();                //initialize the LCD
	
	Set_R_C(1,15);             //put an X out to the screen row 1 col 15
	lcdData('a');
	

	Set_R_C(3,10);             // Set_R_C(row,col)
	lcdString(str);
	
	
	Set_R_C(0,8);
	lcdString("John Doldol");
	
	Set_R_C(3,9);
	lcdData(0xb7);
	//Populate the LCD labels
	lcdLabels("Label 0:","Label 1:","Label 2:","Label 3:");
	
  value =0x41;
  toggle = 1;

  for(;;) {
  
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
    
    if(value == 0x7a)
    {
        value = 0x41; 
    }
    
    toggle = !toggle;
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


/********************************************************************/
//		Functions
/********************************************************************/




/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

