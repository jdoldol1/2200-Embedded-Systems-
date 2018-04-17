/**********************************************************************
*HC12 Header:	IIC0_Lib.h
*Processor:		MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Marc Anderson
*Date:		Friday April 29,2016                                       
*Details: Header file for IIC library
***********************************************************************/

  void IIC0_Init(void);
  void IIC0_Write(unsigned char cAddr, unsigned char cReg, unsigned char cData);
  unsigned char IIC0_Read(unsigned char cAddr, unsigned char cReg);
  void IIC0_WriteDAC(unsigned char cAddr, unsigned char cCommand, int iData);