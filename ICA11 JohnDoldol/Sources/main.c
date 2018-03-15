/********************************************************************/
// HC12 Program:	YourProg - MiniExplanation
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			John Doldol
// Date:			DATE

// Details: A more detailed explanation of the program is entered here
/********************************************************************/

#include <hidef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "derivative.h"

/********************************************************************/
//		Library includes
/********************************************************************/
 #include "LCD_C.h"
 #include "SCI_Lib_C.h"
 #include "my_delays.h"
 #include "led_7seg.h"

/********************************************************************/
//		Prototypes
/********************************************************************/

 void GetValue(void);
 
/********************************************************************/
//		Variables
/********************************************************************/
 float x = 0;
 float y = 0;
 char DestString[25] = "";
 char SrcString[2] = "";
 char RxData;
 
 char ClearAndHome[] = "\x1B[2J\x1B[H";
 char StartXValue[] = "\x1b[2;10H";
 char StartYValue[] = "\x1b[5;5H";
 char promptx[] = "Enter first value: ";
 char prompty[] = "Enter second value: ";
 char gotit[] = "Got it!";
 char result[]="";

/********************************************************************/
//		Lookups
/********************************************************************/
            

void main()   
{
  _DISABLE_COP();
  SCI0_Init19200();
  LEDS_7Seg_Init_C();
  
  SCI0_TxString(ClearAndHome);
  SCI0_TxString(promptx);
  for(;;)
  { 
  
    GetValue();    
    x = atof(DestString);   
       
    Delay_C(5000);   
    
    SCI0_TxString(gotit);
    SCI0_TxString(DestString);
    SCI0_TxString(StartXValue);
    SCI0_TxString(prompty);
    
    GetValue();
    y = atof(DestString);
    Delay_C(5000);
    
    SCI0_TxString(StartYValue);
    SCI0_TxString(DestString);
      
  } /* loop forever */
  /* please make sure that you never leave main */
}

/********************************************************************/
//		Functions
/********************************************************************/
void GetValue(void)
{
  do
    {
    
      RxData = SCI0_RxByte();
      SCI0_TxByte(RxData);
      SrcString[0] = RxData;
      (void)strcat(DestString,SrcString);
    
    }while(RxData != 0x0d);
}
/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/

