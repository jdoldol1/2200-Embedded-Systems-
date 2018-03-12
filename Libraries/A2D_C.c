#include "derivative.h"
#include "Delay_C.h"
#include "A2D_Lib_C.h"

void ATD0_Init(void){
  DDR1AD0 = 0x0;
  ATD0DIEN = 0x0;

  ATD0CTL2 = 0xE0;

  asm LDX #134;
  asm DBNE X, *;

  ATD0CTL3 = 0x02;
  ATD0CTL4 = 0x26;
  ATD0CTL5 = 0xB0;
}

unsigned int ATD0_Sample7(void){
  ATD0CTL5 = 0xB0;
  while (!(ATD0STAT0 & (1 << 7)));
  return ATD0DR7;
}