//------------------------------------------------------------------------------
//
//  Description: This file contains the function that initializes both LEDs.
//
//
//  Michelle Allison
//  1/31/2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P1OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}