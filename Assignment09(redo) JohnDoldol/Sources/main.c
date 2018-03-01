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
#include "LCD_C.h"
#include "switches.h"
#include "led_7seg.h"
#include <math.h>
/********************************************************************/
//		Library includes
/********************************************************************/


/********************************************************************/
//		Prototypes
/********************************************************************/


/********************************************************************/
//		Variables
/********************************************************************/

double radius = 0.0;
double circlearea;
char s[20];
double circlearea;
double spherearea;
double volume;
double diameter;
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
  
  lcdLabels("Input Diameter:","Circle Area:","Sphere Area:","Sphere Vol:");
  diameter = 9;
  radius = diameter / 2.0;
  circlearea = radius * radius * _M_PI;
  spherearea = circlearea * 4;
  volume = (4.0 / 3.0) * _M_PI * radius * radius * radius;
  
  for(;;)     
  {    
       
       Set_R_C(0,16);
       sprintf(s,"%d",(int)diameter);
       lcdString(s);
       
       Set_R_C(1,13);
       sprintf(s,"%5.2f",circlearea);
       lcdString(s);
       
       Set_R_C(2,13);
       sprintf(s,"%5.1f",spherearea);
       lcdString(s);
       
       Set_R_C(3,13);
       sprintf(s,"%5.1f",volume);
       lcdString(s);
       
       
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

