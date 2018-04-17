#include "derivative.h"
#include "Misc_Lib.h"

unsigned int HexToBCD(unsigned int iHexIn)
{
  unsigned int iBCDOut = 0;
  unsigned char count;
  unsigned int power = 1;

//  if (iHexIn > BCDToHex(9999)){
//    return 0; 
//  }

  for(count = 0; count < 4; count++)
  {
    iBCDOut += (iHexIn % 10) * power;
    iHexIn /= 10;
    power *= 16;
  }
      
  return iBCDOut;

}

unsigned int BCDToHex(unsigned int iBCDIn)
{
  unsigned int iHexOut = 0;
  unsigned char count = 0;
  unsigned char digit;
  unsigned int power = 1;

  while (count < 4)
  {
    digit = iBCDIn % 16;
    if (digit < 10) 
    {
      iHexOut += digit * power;
      iBCDIn /= 16;
      count++;
      power *= 10;
    } 
    else 
    {
      iHexOut = 0;
      count = 4;
    }
  }
  
  return iHexOut;
}

void TimeSetup10ms(void)
{
	TimeSetup(625, 0b00000111);
}

void TimeSetup(int timeVal, byte prescaler)
{
	TSCR1  = 0b10000000; // enable timer module
	TSCR2 &= 0b11111000; // set precale to Bus/128 (16 us per tick)
	TSCR2 |= prescaler;
	TIOS  |= 0b00000001; // set IOS0 to output compare
	TCTL2 &= 0b11111100; // set PT0 to toggle mode
	TCTL2 |= 0b00000001;
	TIE   |= 0b00000001; // enable channel 0 interrupts. 
	TFLG1  = 0b00000001; // clear TC0 flag
	
	TC0 = TCNT + timeVal;
}