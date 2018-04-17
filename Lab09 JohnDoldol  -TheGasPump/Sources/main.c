/********************************************************************/
// HC12 Program:	The Gas Pump
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			Yimin Yan
// Date:			  4/16/2018

// Details: A more detailed explanation of the program is entered here
/********************************************************************/

#include <hidef.h>         	// common defines and macros
#include <stdio.h>		    // ANSI C Standard Input/Output functions
#include <math.h>			      // ANSI C Mathematical functions
#include <stdlib.h>
#include <string.h>
#include "derivative.h"    	// derivative-specific definitions

/********************************************************************
*		Library includes - your libraries' header files
********************************************************************/
// #include "A2D_Lib_C.h"
#include "SCI_LIB_C.h"
#include "Delay_C.h"
#include "LCD_C.h" 
#include "LEDS_7Seg_C.h"
#include "Misc_Lib.h"
#include "RYG_LEDs_C.h"
#include "Switches_C.h"






/********************************************************************
*		Prototypes
********************************************************************/
void RenderLCD(void);


/********************************************************************
*		Variables
********************************************************************/
unsigned int msPast = 0;

// for output of float text to SCL
char DestString[25] = "";

// lines for LCD / SCI
char title[] = "    THE GAS PUMP";
char *lines[3];         
char *gradesText[3];

unsigned char switches; // for reading switches
char text[20]; // text for lcd

// program state
int i;
int currentScreen = 0;
int selectedGrade = -1;
float gradePrices[3];
float liters;
/********************************************************************
*		Lookups
********************************************************************/



void main(void) 	// main entry point
{  
  /* put your own code here */   
	// EnableInterrupts; // Question here? what is this line of code.
	
	SCI0_Init19200();
	lcdInit();
	// LEDS_7Seg_Init();
	led_sw_init();
	Sw_Init();
	// ATD0_Init();
 
  for(;;) {
    _FEED_COP(); /* feeds the dog */        

    lines[0] = "Please enter the gas price for Regular grade: ";
    lines[1] = "Please enter the gas price for Mid grade: ";
    lines[2] = "Please enter the gas price for Premium grade: ";  
    
    gradesText[0] = "Regular:   ";
    gradesText[1] = "MID-GRADE: ";
    gradesText[2] = "PREMIUM:   ";  
    
    RenderLCD();
    
    if (currentScreen == 0){
      // get the grade prices
      for (i = 0; i < 3; i++){
        do{
          // ask for a gas price in SCL
          gradePrices[i] = GetNumInputStr(DestString, lines[i]);
        // validate the gas price in SCL    
        }while(
          (sprintf(text, "%5.1f", gradePrices[i]) >= 0) &&
          (gradePrices[i] < 0)      
        );      
      }
      // enter the second screen
      currentScreen++;
      RenderLCD();            
    }
       
    SCI0_TxString("\x1B[2J\x1B[H");
    SCI0_TxString("Thank you, Please select a grade.");
    SCI0_TxString("\x1B[3;0H");
    SCI0_TxString("Regular: Top button.");  
    SCI0_TxString("\x1B[5;0H");
    SCI0_TxString("Mid-Grade: Center button.");    
    SCI0_TxString("\x1B[7;0H");
    SCI0_TxString("Premium: Bottom button.");    
    
    do {
      switches = Get_Switches();

      switch(switches)    
      {
        case TopButton:  
          Red_On();
          selectedGrade = 0;                      
          break;
        case CenterButton:
          Yellow_On();
          selectedGrade = 1;                        
          break;
        case BottomButton:
          Green_On();
          selectedGrade = 2;           
          break;
        default:
          All_Off();
          selectedGrade = -1;
          break;       
      } 
      while(PT1AD1 & switches);
    } while(selectedGrade == -1);  
    
    // enter the thrid screen
    currentScreen++;
    RenderLCD();
    
    // use SCL get liters
    do{
      liters = GetNumInputStr(DestString, "Enter desired liters: ");  
    }while(
      (sprintf(text, "%5.1f", liters) >= 0) &&
      (liters < 0)      
    );  
   
    // enter the fourth screen
    currentScreen++;
    RenderLCD(); 

    SCI0_TxString("\x1B[2J\x1B[H");
    SCI0_TxString("Thank you for using this gas pump.");
   
    // reset
    do {
      switches = Get_Switches();
      switch(switches)    
      {
        case CenterButton:
          Yellow_On();                       
          break;
        default:
          All_Off();
          break;       
      } 
      while(PT1AD1 & switches);
    } while(switches != CenterButton);   
    
    currentScreen = 1; // reset to select grade
    
    if (msPast % 25 == 0){ // render rate for lcd 25ms                       
    }     
                  
    Delay_C(10);
    msPast += 10; 
  } /* loop forever */
  /* please make sure that you never leave main */
}
/**************************************************************************
*		Function:  Note that functions reside outside of Main - so if you call
*              these from within Main, you must include its prototype     
*              above
***************************************************************************/
void RenderLCD() {
    lcdClear();
    switch(currentScreen)    
    {
      case 0:  
        Set_R_C(0, 4);
        lcdString("THE GAS PUMP");

        Set_R_C(1, 0);
        lcdString("ENTER TODAYS PRICES");                    
        break;
      case 1:
        lcdLabels(gradesText[0], gradesText[1], gradesText[2], "SELECT GRADE:");
        Set_R_C(0, strlen(gradesText[0]));
        if(sprintf(text, "%5.1f", gradePrices[0]) >= 0) {
        	lcdString(text);
        }          
        
        Set_R_C(1, strlen(gradesText[1]));
        if(sprintf(text, "%5.1f", gradePrices[1]) >= 0) {
        	lcdString(text);
        }   
              
        Set_R_C(2, strlen(gradesText[2]));
        if(sprintf(text, "%5.1f", gradePrices[2]) >= 0) {
        	lcdString(text);
        }          
        break;
      case 2:
        lcdLabels(title, "", gradesText[selectedGrade], "LITERS?");
            
        Set_R_C(2, strlen(gradesText[selectedGrade]));
        if(sprintf(text, "%5.1f", gradePrices[selectedGrade]) >= 0) {
        	lcdString(text);
        }          
        break;
      case 3:
        lcdLabels(title, "PRICE: ", "LITERS: ", "YOUR COST: ");
        Set_R_C(1, strlen("PRICE: "));
        if(sprintf(text, "%5.1f", gradePrices[selectedGrade]) >= 0) {
        	lcdString(text);
        }          
        
        Set_R_C(2, strlen("LITERS: "));
        if(sprintf(text, "%5.2f", liters) >= 0) {
        	lcdString(text);
        }   
              
        Set_R_C(3, strlen("YOUR COST: "));
        if(sprintf(text, "%5.2f", gradePrices[selectedGrade] * liters / 100.0) >= 0) {
        	lcdString(text);
        }          
        break;      
    }
}


/********************************************************************
*		Interrupt Service Routines
********************************************************************/



/*******************************************************************/
