#include "derivative.h"
#include "my_delays.h"

/*
;________________________________________________________
;                                                        |
;    Library:  Switches_C.c                              |
;                                                        |
;    Contains:                                           |
;              Sw_Init(void)                             |
;              Get_Switches()                            |
;              Wait_for_Switches_up(void)                |
;                                                        |
;    Author:   John Doldol                               |            |
;                                                        |
;    Last Modified: Jan 29, 2018 (Created)               |
;________________________________________________________|

;________________________________________________________
;                                                        |
;    Subroutines:   Sw_Init()                            |
;                                                        |
;    Requires:      None                                 |
;    Returns:       None                                 |
;________________________________________________________|

*/

void Sw_Init(void)
{
  ATD1DIEN1 |= 0x1F;  
}

/*
;________________________________________________________
;                                                        |
;    Subroutines:   Get_Switches(void)                   |
;                                                        |
;    Requires:      None                                 |
;    Returns:       char - the down switches             |
;________________________________________________________|                           
*/

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
;________________________________________________________
;                                                        |
;    Subroutines:   Wait_for_Switches_up(void)           |
;                                                        |
;    Requires:      None                                 |
;    Returns:       None                                 |
;________________________________________________________|
*/

void Wait_for_Switches_up(void)
{
  while(PT1AD1 & 0x1F){}
}

/*
;________________________________________________________
;                                                        |
;    Subroutines:                                        |
;          Wait_for_Switches_up_mask(unsigned char mask) |
;                                                        |
;    Requires:      None                                 |
;    Returns:       None                                 |
;________________________________________________________|
*/

void Wait_for_Switches_up_mask(unsigned char mask)
{
  while(PT1AD1 & mask){}
}                 