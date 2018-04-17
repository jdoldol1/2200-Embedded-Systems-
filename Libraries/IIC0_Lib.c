/**********************************************************************
*HC12 IIC0 Library:	IIC0_Lib.c
*Processor:		MC9S12XDP512
*Xtal Speed:	16 MHz
*Author:		Marc Anderson
*Date:		Friday April 29,2016                                       
*Details: Library file for IIC0
***********************************************************************/

#include <hidef.h>
#include "derivative.h"
#include "IIC0_Lib.h"

void IIC0_Init(void) 
{
    IIC0_IBFD = 0x47;
    IIC0_IBCR = 0x80;
    IIC0_IBCR &= 0b10111100; 
  
}

void IIC0_Write(unsigned char cAddr, unsigned char cReg, unsigned char cData)
{
	while(IIC0_IBSR & 0b00100000);		//wait for not busy flag
	IIC0_IBCR |= 0b00110000;			//micro as master, start transmitting

	IIC0_IBDR = cAddr & 0b11111110;		//place address on bus with /Write
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBSR |= 0b00000010;			//clear flag

	IIC0_IBDR = cReg;					//locate desired register
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBSR |= 0b00000010;			//clear flag

	IIC0_IBDR = cData;					//send command
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBCR &= 0b11001111;		//stop transmitting, exit Master mode			IIC0_IBSR |= 0b00000010;		//clear flag *** must be last!
	IIC0_IBSR |= 0b00000010;			//clear flag
}

unsigned char IIC0_Read(unsigned char cAddr, unsigned char cReg)
{
	unsigned char cData;

	while(IIC0_IBSR & 0b00100000);		//wait for not busy flag
	IIC0_IBCR |= 0b00110000;			//micro as master, start transmitting

	IIC0_IBDR = cAddr & 0b11111110;		//place address on bus with /Write
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBSR |= 0b00000010;			//clear flag

	IIC0_IBDR = cReg;					//locate desired register
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBSR |= 0b00000010;			//clear flag

	IIC0_IBCR |= 0b00000100;			//restart
	
	IIC0_IBDR = (cAddr | 0b00000001);	//place address on bus with Read
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
	IIC0_IBSR |= 0b00000010;			//clear flag

    IIC0_IBCR |= 0b00001000;			//reading 1 unsigned char only
    IIC0_IBCR &= 0b11101111;			//receive unsigned char
    cData = IIC0_IBDR;					//not actually -- starts the process
	while(!(IIC0_IBSR & 0b00000010));	//wait for flag 
    IIC0_IBCR &= 0b11011111;			//stop
	IIC0_IBSR |= 0b00000010;			//clear flag
	cData = IIC0_IBDR;					//for real this time
	
	return cData;    
}



/*

void IIC0_Write(unsigned char cAddr, unsigned char cReg, unsigned char cData) 
{
    while(IIC0_IBSR & 0b00100000);        //wait for not busy flag
    IIC0_IBCR |= 0b00110000;              //micro as master, start transmitting
    
    IIC0_IBDR = cAddr & 0b11111110;       //place address on the bus with Write
    while (!(IIC0_IBSR & 0b00100000));    //wait for flag
    IIC0_IBSR |= 0b00000010;              //clear flag
    
    IIC0_IBDR = cReg;                     //locate desired register
    while (!(IIC0_IBSR & 0b00000010));    //wait for flag
    IIC0_IBSR |= 0b00000010;              //clear flag
    
    IIC0_IBDR = cData;                    //send command
    while (!(IIC0_IBSR & 0b00000010));    //wait for flag
    IIC0_IBSR |= 0b00000010;              //clear flag
    
    IIC0_IBCR &= 0b11001111;              //stop transmitting
  
}  



unsigned char IIC0_Read(unsigned char cAddr, unsigned char cReg) 
{
    unsigned char cData;

    while(IIC0_IBSR & 0b00100000);        //wait for not busy flag
    IIC0_IBCR |= 0b00110000;               //micro as master, start transmitting
    
    IIC0_IBDR = cAddr & 0b11111110;       //place address on the bus wit Write
    while (!(IIC0_IBSR & 0b00000010));    //wait for flag
    IIC0_IBSR |= 0b00000010;              //clear flag
    
    IIC0_IBDR = cReg;                      //locate desired register
    while (!(IIC0_IBSR & 0b00000010));    //wait for flag
    IIC0_IBSR |= 0b00000010;              //clear flag
    
    IIC0_IBCR |= 0b00000100;             //restart
    
    
    IIC0_IBDR = (cAddr | 0b00000001);     //place address on the bus with Read
    while (!(IIC0_IBSR & 0b00000010));   //wait for flag
    IIC0_IBSR |= 0b00000010;             //clear flag
    
    
    IIC0_IBCR |= 0b00001000;             //reading 1 unsigned char only
    IIC0_IBCR &= 0b11101111;             //receive unsigned char
    cData = IIC0_IBDR;                   //not atually - starts the process
    
    while (!(IIC0_IBSR & 0b00000010));   //wait for flag
    IIC0_IBCR &= 0b11011111;             //stop
    cData = IIC0_IBDR = 0b00000010;      //clear flag
    cData = IIC0_IBDR;                   //for real this time
    
    return cData;
    
  
}
*/