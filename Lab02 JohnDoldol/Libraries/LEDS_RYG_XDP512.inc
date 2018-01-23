;**************************************************************************** 
;* Library: LEDS_RYG_XDP512.inc                                             * 
;* Contains:                                                                *
;*          Red_On                                                          *
;*          Red_Off                                                         * 
;*          Red_Toggle                                                      *
;*                                                                          *
;*          Yellow_On                                                       *
;*          Yellow_Off                                                      *
;*          Yellow_Toggle                                                   *
;*                                                                          *
;*          Green_On                                                        *
;*          Green_Off                                                       *
;*          Green_Toggle                                                    *
;*                                                                          *
;*          led_sw_init                                                     *
;* Author:         John Doldol                                              *
;*                                                                          *
;*                 CMPE2200-A01                                             *
;*                                                                          *
;* Last Modified:  January 15, 2018                                         *
;****************************************************************************

;**************************************************************
;*                led_sw_init Subroutine                      *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;*                                                            *
;* Description:   This routine initializes the uuper half     *
;*                of portad for the RYG LEDS and the switches *
;*                                                            *
;**************************************************************

led_sw_init:  BCLR PT1AD1, #$E0
              BSET DDR1AD1, #$E0
              BSET ATD1DIEN1, #$1F
              RTS

;**************************************************************
;*                Red On-Off_Toggle                           *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;**************************************************************

Red_On:     PSHA
            PSHB
            
            LDD PT1AD1
            ORAA #%10000000
            STD PT1AD1
            
            PULB
            PULA
            RTS
            
Red_Off:    PSHA
            PSHB
            
            LDD PT1AD1
            ANDA #%01111111
            STD PT1AD1
            
            PULB
            PULA
            RTS
            
Red_Toggle: PSHA
            PSHB
            
            LDD PT1AD1
            EORA #%10000000
            STD PT1AD1
            
            PULB
            PULA
            RTS   
            
;**************************************************************
;*                Yellow On-Off_Toggle                        *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;**************************************************************

Yellow_On:     PSHA
               PSHB
            
               LDD PT1AD1
               ORAA #%01000000
               STD PT1AD1
            
               PULB
               PULA
               RTS
            
Yellow_Off:    PSHA
               PSHB
            
               LDD PT1AD1
               ANDA #%10111111
               STD PT1AD1
            
               PULB
               PULA
               RTS
            
Yellow_Toggle: PSHA
               PSHB
            
               ldd PT1AD1
               EORA #%01000000
               STD PT1AD1
            
               PULB
               PULA
               RTS 

;**************************************************************
;*                Green On-Off_Toggle                         *
;* Requires:      None                                        *
;* Returns:       None                                        *
;* Regs Affected: None                                        *
;**************************************************************

Green_On:      PSHA
               PSHB
            
               LDD PT1AD1
               ORAA #%00100000
               STD PT1AD1
            
               PULB
               PULA
               RTS
            
Green_Off:     PSHA
               PSHB
            
               LDD PT1AD1
               ANDA #%11011111
               STD PT1AD1
            
               PULB
               PULA
               RTS
            
Green_Toggle:  PSHA
               PSHB
            
               LDD PT1AD1
               EORA #%00100000
               STD PT1AD1
            
               PULB
               PULA
               RTS 




