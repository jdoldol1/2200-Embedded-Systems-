#include "derivative.h"

/**************************************************************************** 
 Library: LEDS_RYG_XDP512.inc                                              
 Contains:                                                                
          Red_On                                                          
          Red_Off                                                         
          Red_Toggle                                                     
                                                                          
          Yellow_On                                                       
          Yellow_Off                                                      
          Yellow_Toggle                                                   
                                                                          
          Green_On                                                       
          Green_Off                                                       
          Green_Toggle                                                    
                                                                          
          led_sw_init                                                     
 Author:         John Doldol                                             
                                                                         
                 CMPE2200-A01                                            
                                                                         
 Last Modified:  January 26, 2018                                         
****************************************************************************/

/**************************************************************
;*                led_sw_init Subroutine                      *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;*                                                            *
;* Description:   This routine initializes the uuper half     *
;*                of portad for the RYG LEDS and the switches *
;*                                                            *
;*************************************************************/

void led_sw_init(void) 
{
  PT1AD1 &= 0x1F;
  DDR1AD1 |= 0xE0;
  ATD1DIEN1 |= 0x1F;
}

/**************************************************************
;*                Red On-Off_Toggle                           *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;*************************************************************/

void Red_On(void) 
{
  PT1AD1 |= 0x80;   
}

void Red_Off(void) 
{
  PT1AD1 &= 0x7F;
}

void Red_Toggle(void) 
{
  PT1AD1 ^= 0x80;
}

/**************************************************************
;*                Yellow On-Off_Toggle                        *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;*************************************************************/


               
void Yellow_On(void) 
{
  PT1AD1 |= 0x40;   
}

void Yellow_Off(void) 
{
  PT1AD1 &= 0xBF;
}

void Yellow_Toggle(void) 
{
  PT1AD1 ^= 0x40;
}

/**************************************************************
;*                Green On-Off_Toggle                         *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;*************************************************************/


void Green_On(void) 
{
  PT1AD1 |= 0x20;   
}

void Green_Off(void) 
{
  PT1AD1 &= 0xDF;
}

void Green_Toggle(void) 
{
  PT1AD1 ^= 0x20;
}         




