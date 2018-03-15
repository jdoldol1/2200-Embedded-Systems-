/*****************************************************

     Library: SCI_Lib_C.c
     Contains:
      Key_hit
            Rx_Byte
            SCI_19200
            Tx_Byte
            Tx_String
            TxSCI_String_B
            
     Author: John Doldol
     Last Modified: March 15, 2018
*****************************************************/

#include "derivative.h"
/*****************************************************    
          Key_hit Function  
          
          This is checking RDRF
          
          = 0x20 if a character is waiting
          = 0x00 if no character is in
          
          Calling program needs to look at the
          return value and run Rx_Byte if return
          value is non-zero                                      
*****************************************************/

unsigned char SCI0_Key_hit(void)
{                  
  unsigned char ucKey_In = 0;
  ucKey_In = SCI0SR1 & 0x20;
  return ucKey_In;
}

/*****************************************************
          Rx_Byte Function          
*****************************************************/

unsigned char SCI0_RxByte(void)
{

  unsigned char uckey = 0;
  
  while((SCI0SR1 & 0x20)==0);
  
  return SCI0DRL;

}

/*****************************************************
          SCI_19200 Initialization Function
          
          Initialization for 19200 Baud, 8N1
*****************************************************/

void SCI0_Init19200(void)
{

  SCI0BDH = 0;
  SCI0BDL = 26;
  SCI0CR1 = 0x00;
  SCI0CR2 = 0x0C;

}

/*****************************************************
          Tx_Byte Function
          
 Character to be sent is passed into the funciton as
 unsigned char. The transmit register is checked until
 it is empty prior to writing the character into it  
*****************************************************/

void SCI0_TxByte(unsigned char cVal)
{
  while((SCI0SR1 & 0x80) == 0)
  {
  
  
  }
  SCI0DRL = cVal;
}

/*****************************************************
         Tx_String Function
*****************************************************/

void SCI0_TxString(char * cString)
{

  while(*cString != 0)
  {
    SCI0_TxByte(*cString++);
  }
  
}

/*****************************************************

*****************************************************/


