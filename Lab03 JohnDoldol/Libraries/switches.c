#include "derivative.h"
#include "my_delays.h"

/*********************************************************
;                                                      
;    Library:  Switches_C.c                              
;                                                        
;    Contains:                                           
;              Sw_Init(void)                             
;              Get_Switches()                            
;              Wait_for_Switches_up(void)                
;                                                        
;    Author:   John Doldol                                         
;                                                       
;    Last Modified: Jan 29, 2018 (Created)              
;*********************************************************

;********************************************************;                                                      
;    Subroutines:   Sw_Init()                           
;                                                       
;    Requires:      None                                
;    Returns:       None                                
;*********************************************************/

void Sw_Init(void)
{
  ATD1DIEN1 |= 0x1F;  
}

/*
;********************************************************                                                       
;    Subroutines:   Get_Switches(void)                  
;                                                        
;    Requires:      None                                 
;    Returns:       char - the down switches            
;********************************************************/

unsigned char Get_Switches(void)
{
  unsigned char Switches = 0;
  Switches = PT1AD1 & 0x1F;
  Delay_C(10);
  
  if((PT1AD1 & 0x1F) != Switches)
    Switches = 0;
  
  return Switches;
}

/*
;*********************************************************
;                                                        
;    Subroutines:   Wait_for_Switches_up(void)          
;                                                       
;    Requires:      None                                 
;    Returns:       None                                 
;********************************************************/

void Wait_for_Switches_up(void)
{
  while(PT1AD1 & 0x1F){}
}

/*
;********************************************************
;                                                        
;    Subroutines:                                        
;          Wait_for_Switches_up_mask(unsigned char mask) 
;                                                       
;    Requires:      None                                 
;    Returns:       None                                 
;********************************************************/


void Wait_for_Switches_up_mask(unsigned char mask)
{
  while(PT1AD1 & mask){}
}                 