;**************************************************************************** 
;*              Library: MyDelays.inc                                       *                                              * 
;*                                                                          *
;* Contains:       Delay                                                    *
;*                                                                          *
;* Author:         John Doldol                                              *
;*                 CMPE2200-A01                                             *
;*                                                                          *
;* Last Modified:  January 15, 2018                                         *
;*                                                                          *
;****************************************************************************

;**************************************************************
;*                Red On-Off_Toggle                           *
;* Requires:      Number of msec specified in x               *
;* Returns:       None                                        *
;* Regs Affected: Trashes Y                                   *
;* Details:       This preforms a delay of the number of ms   *
;*                Specified by the X register                 *
;**************************************************************

Delay:    LDY #2665
delay_2:  DBNE Y, delay_2
          DBNE X, Delay
          
          RTS

