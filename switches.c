//------------------------------------------------------------------------------
//
//  Description: This file contains the function for the two buttons.
//
//  Michelle Allison
//  February 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

extern int select_shape; //0 - none, 1 - circle, 2 - triangle, 3 - 8
extern char display_line[DISP_LINES][DISP_COL];
extern char *display[DISP_LINES];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern unsigned int Time_Sequence;
extern char one_time;
extern volatile int debounce_count1;
extern volatile int debounce_count2;
extern volatile char debounce1_current;
extern volatile char debounce2_current;
/*
void Switches_Process(void){
//--------------------------------------------------------------------------------------
// checks whether button 1 or button 2 are pressed
  if (!(P5IN & BUTTON1)){
    P5IFG |= BUTTON1;
  }

  if (!(P5IN & BUTTON2)) {
  //when button 2 is pressed
    P5IFG |= BUTTON2;
  }
  if ((debounce1_current == RESET_STATE) && (debounce2_current == RESET_STATE)) {
    TA0CCTL1 &= ~CCIE;
  }
//------------------------------------------------------------------------------
}*/