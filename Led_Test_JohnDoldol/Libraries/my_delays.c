/**************************************************************************** 
;*              Library: MyDelays.inc                                       *
;*                                                                          *
;* Contains:       Delay                                                    *
;*                                                                          *
;* Author:         John Doldol                                              *
;*                 CMPE2200-A01                                             *
;*                                                                          *
;* Last Modified:  January 26, 2018                                         *
;*                                                                          *
;***************************************************************************/

/**************************************************************
;*                Red On-Off_Toggle                           *
;* Requires:      Number of msec specified in x               *
;* Returns:       None                                        *
;* Regs Affected: Trashes Y                                   *
;* Details:       This preforms a delay of the number of ms   *
;*                Specified by the X register                 *
;*************************************************************/


void Delay_C(int mSec) 
{
  asm ldx mSec
  asm Delay: ldy #2665
  asm delay_2: dbne y, delay_2
  asm dbne x, Delay
}

/**************************************************************
;*                                                            *
;*         cause a short delay ~20us in C - JCPD              *
;*                                                            *
;*************************************************************/

void Short_Delay(void) 
{
  asm ldy #10
  asm dbne y,*
}

/**************************************************************
;*                                                            *
;*      Cause a long delay(49.2ms)                            *
;*                                                            *
;*************************************************************/

void Long_Delay(void) 
{
  asm ldy #0
  asm dbne y,* 
}