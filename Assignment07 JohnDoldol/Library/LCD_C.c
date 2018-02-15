#include "derivative.h"
#include "LCD_C.h"
/*
;---------------------------------------------------------------------------------
|                  set the R/W* line high (reading)
|                            in C - MDA                              
;---------------------------------------------------------------------------------
*/ 
void lcdRWUp(void) 
  {
  
   PORTK |= 0x02;  // 0000 0010 set R/W* as high
  }
  
/*  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set the R/W* line low (writing)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdRWDown:  bclr PORTK,#$02	; set R/W* as low
		    	  rts
 */
/*
;---------------------------------------------------------------------------------
|                  set the R/W* line low (writing)
|                            in C - MDA                                 
;---------------------------------------------------------------------------------
*/  
void lcdRWDown(void) 
  {
  
   PORTK &= 0xFD;  // 1111 1101 set R/W* as low
  }
/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set the E line high (enable LCD)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdEUp:		  bset PORTK,#$01	; set E as high
			      rts
*/
/*
;---------------------------------------------------------------------------------
|                  set the E line high (enable LCD)
|                            in C - MDA                                 
;---------------------------------------------------------------------------------
*/ 
 void lcdEUp(void) 
 {
   PORTK |= 0x01;  //0000 0001  set E as high
 }
 
 /*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set the E line low (disable LCD)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdEDown:	  bclr PORTK,#$01	; set E as low
			      rts
*/
/*
;---------------------------------------------------------------------------------
|                  set the E line low (disable LCD)
|                             in C - MDA                                 
;---------------------------------------------------------------------------------
*/ 
 void lcdEDown(void) 
 {
    PORTK &= 0xFE;  //1111 1110  set E as low
 }

/*			      

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set the A line high (address 1 (data))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdRSUp:		bset PORTK,#$04	; set A as high
			      rts
*/
/*
;---------------------------------------------------------------------------------
|                   set the A line high (address 1 (data)))
|                             in C - MDA                                 
;---------------------------------------------------------------------------------
*/
void lcdRSUp(void) 
 {
    PORTK |= 0x04;  //0000 0100  set A as high
 }
 
 /*
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set the A line low (address 0 (instruction))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdRSDown:	bclr PORTK,#$04	; set A as low
			      rts
*/
  /*
;---------------------------------------------------------------------------------
|                   set the A line low (address 0 (instruction))
|                              in C - MDA                                 
;---------------------------------------------------------------------------------
*/
			      
void lcdRSDown(void) 
 {
    PORTK &= 0xFB;  //1111 1011  set A as low
 }
 /*			      
			      
			                                                       

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; cause a short delay ~20us                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdSDelay:  pshy
            ldy #10
            dbne y,*
            puly
            rts
            
 */
 /*
;---------------------------------------------------------------------------------
|                         cause a short delay ~20us 
|                               in C - MDA                                 
;---------------------------------------------------------------------------------
*/
  void lcdSDelay(void) 
  {
   asm         ldy #10
   asm         dbne y,*
  }
 
 /*           
            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; cause a long delay (scope measures to be ~~ 49.2ms (w/calls)
; decrements to ffff firs then checks for zero, hence the long delay                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdLDelay:  pshy
            ldy #0
            dbne y,*
            puly
            rts
            
            
  */
  /*
;---------------------------------------------------------------------------------
|         Cause a long delay (scope measures to be ~~ 49.2ms (w/calls)
|   decrements to ffff firs then checks for zero, hence the long delay  (in C) - MDA                                 
;---------------------------------------------------------------------------------
*/
  void lcdLDelay(void) 
  {    
   asm         ldy #0
   asm         dbne y,*
  }
 
 /*   

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; init LCD (pu/reset init)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdInit:    clr PTH               ; premark all outputs as low
            movb #$FF,DDRH        ; set port H as all outputs
            
            bclr PORTK,#$07       ; premark control outputs as low (A=RW=E = 0)            
            bset DDRK,#$07        ; set port K0:2 as outputs
            
            ; all pins now are low
            ; e could have been running a little high
            ; cause delay to allow LCD to get it together
            jsr lcdLDelay
            jsr lcdLDelay
            jsr lcdLDelay         ; spec says 40ms after Vcc > 2.7V, but seems to need much longer
            
            movb #$38,PTH         ; Function Set = 8 bit i.f., 2 line, 5 * 7 
            jsr lcdEUp  
            jsr lcdEDown             
            jsr lcdLDelay         ; wait for unclog (> 4.1ms)            

            jsr lcdEUp   
            jsr lcdEDown             
            jsr lcdLDelay         ; wait for unclog ( > 100us)            
            
            jsr lcdEUp   
            jsr lcdEDown             
            jsr lcdLDelay         ; final init sequence    
                        
            jsr lcdEUp   
            jsr lcdEDown
            jsr lcdLDelay         ; from spec, shows a 4th itt. of this command...    
            
            movb #$0C,PTH         ; Disp Control = Disp On, no cursor, no blink
            jsr lcdEUp   
            jsr lcdEDown
            jsr lcdLDelay             
            
            movb #$01,PTH         ; Clear Disp
            jsr lcdEUp   
            jsr lcdEDown
            jsr lcdLDelay             

            movb #$06,PTH         ; Entry Mode Set = inc + no disp shift
            jsr lcdEUp   
            jsr lcdEDown
            jsr lcdLDelay                                     
            
            rts
 
 
 ;---------------------------------------------------------------------------------
 | Initialize LCD (pu/reset init)     C Version - MDA 
 ;----------------------------------------------------------------------------------
*/
void lcdInit(void) 
{ 
  
 PTH = 0x00;                   // premark all outputs as low      
 DDRH = 0xff;                   // set port H as all outputs
 
 PORTK &= ~0x07;                // premark control outputs as low (A=RW=E = 0)
 DDRK |= 0x07;                   // set port K0:2 as outputs
            
                                // all pins now are low
                                // e could have been running a little high
                                // cause delay to allow LCD to get it together
 lcdLDelay();
 lcdLDelay();
 lcdLDelay();                   // spec says 40ms after Vcc > 2.7V, but seems to need much longer
                             
 PTH = 0x38;                     // Function Set = 8 bit i.f., 2 line, 5 * 7 
 lcdEUp();  
 lcdEDown();
 lcdLDelay();                   // wait for unclog (> 4.1ms)   

 lcdEUp();   
 lcdEDown();             
 lcdLDelay();                    // wait for unclog ( > 100us)            
            
 lcdEUp();   
 lcdEDown();             
 lcdLDelay();                   // final init sequence    
                        
 lcdEUp();   
 lcdEDown();
 lcdLDelay();                   // from spec, shows a 4th itt. of this command...
 
 PTH = 0x0C;                    // Disp Control = Disp On, no cursor, no blink
 lcdEUp();   
 lcdEDown();
 lcdLDelay();             
            
 PTH = 0x01;                     // Clear Disp
 lcdEUp();   
 lcdEDown();
 lcdLDelay();             

 PTH = 0x06;                     // Entry Mode Set = inc + no disp shift
 lcdEUp();   
 lcdEDown();
 lcdLDelay();
 
 }                                     
            
           
/*

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; send a byte to the inst reg of LCD on custom port                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

lcdInst:    psha
            
            jsr lcdBusy     ; wait for LCD to be not busy

            bclr PORTK,#$07 ; premark control outputs as low (A=RW=E = 0)
            
            staa PTH        ; send out to port q
            movb #$FF,DDRH  ; set port H as all outputs 
            
            jsr lcdSDelay   ; debug
            
            jsr lcdEUp
            jsr lcdEDown 
            
            pula
            rts          





 ---------------------------------------------------------------------------------
|  send a byte to the instruction reg of LCD on custom port - byte comes in as cIn 
|                                 in C - MDA                                
 ---------------------------------------------------------------------------------
*/

void lcdInst(char cIn) 
{
            
lcdBusy();                       // wait for LCD to be not busy

PORTK &= ~0x07;                  // premark control outputs as low (A=RW=E = 0)
            
PTH = cIn;                       // send out to port q
DDRH = 0xFF;                     // set port H as all outputs
 
            
lcdSDelay();                     // debug
            
lcdEUp();
lcdEDown();

}

  
/*  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; send a byte to the data reg of LCD on custom port                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdData:    psha
                       
            jsr lcdBusy     ; wait for LCD to be not busy

            bclr PORTK,#$07 ; premark all control outputs as low (data and writing)
            
            staa PTH        ; send out to port q
            movb #$FF,DDRH  ; set port H as all outputs                             
            
            jsr lcdRSUp     ; is data
            jsr lcdEUp      
            jsr lcdEDown    ; latch LCD, latch!            

            pula
            rts              
  
  
            
                                 
 ---------------------------------------------------------------------------------
|   send a byte to the LCD at current the cursor location - byte comes in as cIn
|   Use Set_R_C(char,char) to set the Row,Col prior to calling this function 
|                                in C - MDA                              
 ---------------------------------------------------------------------------------
 */
 
void lcdData(char cIn) 
{
                       
lcdBusy();                      // wait for LCD to be not busy

PORTK &= ~0x07;                 // premark all control outputs as low (data and writing)
            
PTH = cIn;                      // send out to port q
DDRH = 0xFF;                    // set port H as all outputs                             
            
lcdRSUp();                      // is data
lcdEUp();      
lcdEDown();                     // latch LCD, latch!            
              
}
            
            
            
                          
/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; wait for the LCD to be not busy                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdBusy:    psha
                        
            clr DDRH        ; set port H, inputs
            
            jsr lcdRSDown   ; is instruction
            jsr lcdRWUp     ; reading
            
lcdBusyLoop:jsr lcdSDelay                        
            jsr lcdEUp
            jsr lcdSDelay   ; prolly not necessary                     
            ldaa PTH        ; status (d7) and address (d6:0)
            jsr lcdEDown            

            anda #$80
            bne lcdBusyLoop                                    
            
            pula
            rts
*/

/*             

 ---------------------------------------------------------------------------------
|                   wait for the LCD to be not busy in C - MDA                              
 ---------------------------------------------------------------------------------
 */            

void lcdBusy(void) 
{ 
  char Lcd_Busy = 0;                         
  DDRH = 0x00;                  // set port H, inputs
            
  lcdRSDown();                  // is instruction
  lcdRWUp();                    // reading

  do 
  {       
    lcdSDelay();                        
    lcdEUp();
    lcdSDelay();                //probably not necessary                     
    Lcd_Busy = PTH;             //status (d7) and address (d6:0)
    Lcd_Busy &= 0x80;
    lcdEDown(); 
            
  }
  while (Lcd_Busy != 0);
           
}
            
            
            
           

/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set addr in A to LCD
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


lcdAddr:    psha
            
            jsr lcdBusy
            oraa #$80
            jsr lcdInst
            
            pula
            rts
            
*/
 
 /*
 ---------------------------------------------------------------------------------
|                          set addr in A to LCD    in C - MDA                           
 ---------------------------------------------------------------------------------
 */
 
 void lcdAddr(char cAddress) 
 {
  
   lcdBusy();
   cAddress |= 0x80;
   lcdInst(cAddress);
 
 }
  
 
 
 
                      
/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set CG addr in A to LCD
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


lcdCGAddr:  psha
            
            jsr lcdBusy
            anda #$3F
            oraa #$40
            jsr lcdInst
            
            pula
            rts 
 */           
            
 /*
 ---------------------------------------------------------------------------------
|                          set CG addr in A to LCD in C - MDA                              
 ---------------------------------------------------------------------------------
 */                


 void lcdCGAddr(char cAddress) 
 {
    lcdBusy();
    cAddress &= 0x3F;
    cAddress |= 0x40;
    lcdInst(cAddress);
 
 }
  


 /*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; send a string to the data reg of LCD on custom port                                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdString:  psha
            pshx
            
_lcds_loop: ldaa 0,x
            beq _lcds_done
            
            jsr lcdData
            inx
            bra _lcds_loop
            
_lcds_done: pulx
            pula
            rts            
 */
 
 
  /*
 ---------------------------------------------------------------------------------
|               Send a string to the LCD starting 
|                  at current cursor position in C - MDA 
---------------------------------------------------------------------------------
 */                
  
 void lcdString(char* InputString) 
 {
  char cLetter = '0'; 
  int iIndex = 0;
  
  while (InputString[iIndex] != '\0' && iIndex <20)
  {
      cLetter = InputString[iIndex];
      lcdData(cLetter);
      iIndex++;
  }
 }
  
  
 
/* 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set cursor to blinking
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdBlink:   psha
            
            jsr lcdBusy
            ldaa #$0d
            jsr lcdInst
            
            pula
            rts            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; set cursor to not blinking
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdNoBlink: psha
            
            jsr lcdBusy
            ldaa #$0c
            jsr lcdInst
            
            pula
            rts            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; clear the display
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdClear:   psha
            
            jsr lcdBusy
            ldaa #1
            jsr lcdInst
            
            pula
            rts      
            
  */          
            
  /*
 ---------------------------------------------------------------------------------
|               clear the display  in C - MDA                             
 ---------------------------------------------------------------------------------
 */ 
void lcdClear(void) 
{
           lcdBusy();           
           lcdInst(1);
}
            
/*                    

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; go Home
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdHome:    psha
            
            jsr lcdBusy
            ldaa #2
            jsr lcdInst
            
            pula
            rts            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; shift display left
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdShiftL:  psha
            
            jsr lcdBusy
            ldaa #$18
            jsr lcdInst
            
            pula
            rts            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; shift display right
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdShiftR:  psha
            
            jsr lcdBusy
            ldaa #$1C
            jsr lcdInst
            
            pula
            rts            

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; make the cursor solid and visible
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
lcdCurSld:  psha
            
            jsr lcdBusy
            ldaa #$0e
            jsr lcdInst
            
            pula
            rts 


            
; __________________________________________________________________________
;'																			
;|																			
;|					           Set_R_C	  (Set Cursor at Row/Column)									
;|																			
;|	  Author:     Marc Anderson
;|    Date:       May 06, 2013
;|																		
;|		Requires:		X contains the column in Zero based DECIMAL (0 - 19)
;|                Y contains the row in Zero based DECIMAL (0 - 3)  										
;|		Returns:		Calls Simon's lcdAddr to set the appropriate cursor position												
;|		Regs Affected:	None												
;|																			
;|		Details:		This subroutine can be used to convert desired Row and Col 
;|					      cursor position (passed in X and Y) to LCD address.
;|                After calculation of the LCD Address, Simon's lcdaddr is 
;|						    called with the data in Acca to position the cursor.
;|    Note: If the row is not in the range 0 to 3, or the column is not in the
;|          range 0 to 19 the calculated address will default to $00.
;|
;|__________________________________________________________________________             
  
Set_R_C:        pshd

                cpx #$13          ;The check for invalid row
                bhi NotValid_R_C
                  
Is_Row_0:       cpy #0            ;If row "0", address is just the col# in dec
                bne Is_Row_1
                 
                xgdx              
                tba      
                bra End_Set_R_C
                
Is_Row_1:       cpy #1
                bne Is_Row_2
                
                xgdx              ;If row "1", address is $40 + the col# in dec
                ldaa #$40
                aba
                bra End_Set_R_C
                
Is_Row_2:       cpy #2
                bne Is_Row_3
                
                xgdx              ;If row "2", address is $14 + the col# in dec
                ldaa #$14
                aba
                bra End_Set_R_C

Is_Row_3:       cpy #3
                bne NotValid_R_C  ;If you land here you have an out of
                                  ;bounds row number
                
                xgdx              ;If row "3", address is $54 + the col# in dec
                ldaa #$54
                aba
                bra End_Set_R_C
                
NotValid_R_C:   ldaa #$00                
End_Set_R_C:    jsr lcdAddr       ;Now call Simon's set cursor address routine

                puld   
                rts    
                
                
                
 */               
                
/*               
; __________________________________________________________________________
;'																			
;|																			
;|					           Set_R_C	in C  (Set Cursor at Row/Column)									
;|																			
;|	  Author:     Marc Anderson
;|    Date:       May 29, 2015
;|																		
;|		Requires:		cRow contains the row in Zero based DECIMAL (0 - 3)
;|                cCol contains the column in Zero based DECIMAL (0 - 19)
;|                  										
;|		Returns:		Calls Simon's lcdAddr to set the appropriate cursor position												
;|																			
;|		Details:		This function can be used to convert desired Row and Col 
;|					      cursor position (passed in as cCol and cRow) to LCD address.
;|                After calculation of the LCD Address, Simon's lcdaddr is 
;|						    called with the data in cAddr to position the cursor.
;|    Note: If the row is not in the range 0 to 3, or the column is not in the
;|          range 0 to 19 the calculated address will default to 0x00.
;|
;|__________________________________________________________________________             
  
*/

void Set_R_C(char cRow, char cCol) 
{

  char cAddr = 0;
  
  if(cCol >= 0 && cCol < 20)  //Check for valid column number, if valid
                              //Column, calcuate address based on row, and col.
  {                           //If the row or col happens to be invalid, set the
                              //LCD address to 0x00, and print there without crashing.
    
  
                switch(cRow) 
                {                  
                  case 0:
                  cAddr = cCol;
                  lcdAddr(cAddr); //Now call Simon's set cursor address routine
                  break;
                  
                 
                  case 1:
                  cAddr = 0x40 + cCol;
                  lcdAddr(cAddr);  //Now call Simon's set cursor address routine
                  break;


                  case 2:
                  cAddr = 0x14 + cCol;
                  lcdAddr(cAddr);   //Now call Simon's set cursor address routine
                  break;
                  
                  
                  case 3:
                  cAddr = 0x54 + cCol;
                  lcdAddr(cAddr);   //Now call Simon's set cursor address routine
                  break;
                  
                  default:
                  cAddr = 0;
                  lcdAddr(cAddr);   //Now call Simon's set cursor address routine
                  break;
                }
                
  }
   
  else
   
  {
   lcdAddr(cAddr);       //Now call Simon's set cursor address routine
  }           

}


 /*               
; __________________________________________________________________________
;'																			
;|																			
;|					           LCD_Labels	 in C (Populate up to 4 LCD Labels)									
;|																			
;|	  Author:     Marc Anderson
;|    Date:       June 1, 2015
;|																		
;|		Requires:	  The call requires 4 strings. (Use "" if no label required)
;|              	Lb0 Label for Row 0
;|                Lb1 Label for Row 1
;|              	Lb2 Label for Row 2
;|                Lb3 Label for Row 3
;|                  										
;|		Returns:	  Populates 4 LCD Labels
;|																			
;|		Details:		This function can be replaced and done manually, one label 
;|                at a time, but you can use this to populate 4 LCD labels all 
;|                at once, one label at the beginning of each row.   
;|					      You could modify the location of each label
;|                by altering the (row,col) data for that label in the 
;|                code below.
;|
;|__________________________________________________________________________             
  
*/

void lcdLabels(char* Lb0,char* Lb1,char* Lb2,char* Lb3)
{
     Set_R_C(0,0);
     lcdString(Lb0);
     Set_R_C(1,0);
     lcdString(Lb1);
     Set_R_C(2,0);
     lcdString(Lb2);
     Set_R_C(3,0);
     lcdString(Lb3);
     
}
  
          