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
 float z = 0;
 char s[20] = "";
 char DestString[25] = "";
 char SrcString[2] = "";
 char RxData;
 
 char ClearAndHome[] = "\x1B[2J\x1B[H";
 char Starta[] = "\x1b[2;1H";
 char Startb[] = "\x1b[3;1H";
 char Startc[] = "\x1b[4;1H";
 char Startd[] = "\x1b[5;1H";
 char promptx[] = "Enter first decimal value: ";
 char prompty[] = "Enter second decimal value: ";
 char gotit[] = "Got it!  ";
 char result[]="";
 char product[] = "Products of both is: ";

/********************************************************************/
//		Lookups
/********************************************************************/
            

void main()   
{
  _DISABLE_COP();
  SCI0_Init19200();
  LEDS_7Seg_Init_C();
  
  
  //create labels for LCD SCREEN
  lcdInit();
  lcdLabels("THE MULTIPLIER","N1:","N2:","N1 x N2= ");
  
  SCI0_TxString(ClearAndHome);
  SCI0_TxString(promptx);
  for(;;)
  { 
  
    //get first decimal value
    GetValue();    
    x = atof(DestString);
    SCI0_TxString(Starta) ;
    SCI0_TxString(gotit);
    SCI0_TxString(DestString);
    SCI0_TxString(Startb);
    SCI0_TxString(prompty);
    
    DestString[0] = 0x00; //null termination
    
    //get second decimal value
    GetValue();
    y = atof(DestString);     
    SCI0_TxString(Startc);
    SCI0_TxString(gotit);
    SCI0_TxString(DestString);
    SCI0_TxString(Startd);
    
    //calculate products then display on the terminal
    z= x * y;
    sprintf(s,"%5.3f",z);
    SCI0_TxString(product);
    SCI0_TxString(s);
    
    
     Set_R_C(1,5);
    sprintf(s,"%5.3f",x);
    lcdString(s);
    
    Set_R_C(2,5);
    sprintf(s,"%5.2f",y);
    lcdString(s);
    
    Set_R_C(3,10);
    sprintf(s,"%5.3f",z);
    lcdString(s);
    
    
      
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

