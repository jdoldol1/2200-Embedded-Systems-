;****************************************************************************
;* HC12 Program:  YourProg - MiniExplanation                                *
;* Processor:     mc9s12xdp512                                              *
;* Xtal Speed:    16 MHz                                                    *
;* Author:        John Doldol                                               *
;* Date:          January 18 2018   	                                      *
;*                                                                          *
;* Details: A more detailed explanation of the program is entered here      *
;*                                                                          * 
;*                                                                          *
;*                                                                          *
;*                                                                          *
;****************************************************************************

; export symbols
            XDEF Entry            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point

; include derivative specific macros
            INCLUDE 'mc9s12xdp512.inc'
            
            
;**************************************************************
;*                  Equates Declared Here                     *
;**************************************************************
ROMStart    EQU  $4000  ; absolute address to place my code/constant data


            

;**************************************************************
;*                 Variables Declared Here                    *
;**************************************************************
            ORG RAMStart 			;Address $0400            
;Insert your variables here 




;**************************************************************
;*                 Constants Declared Here                    *
;**************************************************************
            
Constants	EQU $C000	
	ORG Constants 			;Address $C000

            
;Insert your constants here 




;**************************************************************
;*                 Code Section Here                          *
;**************************************************************
            ORG   ROMStart		  ;Address	$4000
Entry:
            LDS   #RAMEnd+1       ; initialize the stack pointer
                                  ; enable interrupts
                                  
                                  

;Place your code here starting at the Main label                                
                              
Main:
      JSR led_sw_init  
      LDD PT1AD1
      
LOOP:
      BCLR PT1AD1, #%11100000
ONE:                     
      BRSET PT1AD1,#%00001000,COUNT
      BRSET PT1AD1,#%00000001,LOOP ;clears then starts loop again
      BRA ONE
      
COUNT:
      JSR DBOUNCE                   ;debounce
      BRCLR PT1AD1,#%00001000,ONE          
      BRSET PT1AD1,#%00011000,ADD
      BRSET PT1AD1,#%00001100,SUB
      BRSET PT1AD1,#%00001001,ONE 
      BRA COUNT
      
ADD:
      JSR DBOUNCE                   ;debounce
      BRCLR PT1AD1,#%00011000,ONE 
      LDD PT1AD1
      ADDA #%00100000
      STD PT1AD1
      LDX #500
      JSR Delay
      BRA BUFFER
SUB:
      JSR DBOUNCE                    ;debounce
      BRCLR PT1AD1,#%00001100,ONE
      LDD PT1AD1
      SUBA #%00100000
      STD PT1AD1
      LDX #500
      JSR Delay       
      BRA BUFFER
BUFFER:   
      BRSET PT1AD1, #%00000100,BUFFER   ;buffer so that sticky keys dont decrement
      BRSET PT1AD1, #%00010000,BUFFER   ;buffer so that sticky keys dont increment
      BRA ONE

DBOUNCE:
      LDX #10
      JSR Delay 
      RTS
      
  
;**************************************************************
;*                 SCI VT100 Strings Defined Here             *
;**************************************************************  
  
     
     
;**************************************************************
;*                 Look-Up Table Includes                     *
;**************************************************************

          ;INCLUDE "YourLookUp.inc" 

 
     
;**************************************************************
;*            Absolute DP128 Library Includes                 *
;************************************************************** 
      
         
         ;INCLUDE "A2D_LIB.inc"
         ;INCLUDE "DAC4822_LIB.inc"
         ;INCLUDE "Delays.inc"
         ;INCLUDE "My Delays.inc"
          
         ;INCLUDE "LCD_LIB.inc"
         ;INCLUDE "LEDS_RYG.inc"
         ;INCLUDE "LEDS_7Seg.inc"
         ;INCLUDE "SCI_LIB.inc"
                  
         ;INCLUDE "SPI_4822.inc"
         ;INCLUDE "STRING_LIB.inc"
         ;INCLUDE "HC12_Switches.inc"
                   
         ;INCLUDE "UTILITY_LIB.inc"
         ;INCLUDE "Math_Utility_Lib.inc"
         
         
;**************************************************************
;*           Absolute XDP512 Library Includes                 *
;************************************************************** 
         ; XDP512 Libs
         ;INCLUDE "IIC-24AA512_EEPROM.inc"
         ;INCLUDE "LCD_XDP512.inc"
         ;INCLUDE "LEDS_7Seg.inc"        
         INCLUDE "MyDelays.inc"
         
         INCLUDE "LEDS_RYG_XDP512.inc" 
         ;INCLUDE "Switches_XDP512.inc"
         
       
         

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector
