//------------------------------------------------------------------------------
//
//  Description: This file contains the function that initializes the display.
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

// Global Variables
extern char display_line[DISP_LINES][DISP_COL];
extern char *display[DISP_LINES];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
  // Initializes the display
  //------------------------------------------------------------------------------
  int i;

  for(i=RESET_STATE;i<LOOP_TEN;i++){
    display_line[DISP_ZERO][i] = RESET_STATE;
    display_line[DISP_ONE][i] = RESET_STATE;
    display_line[DISP_TWO][i] = RESET_STATE;
    display_line[DISP_THRE][i] = RESET_STATE;
  }
  display_line[DISP_ZERO][DISP_RCOL] = RESET_STATE;
  display_line[DISP_ONE][DISP_RCOL] = RESET_STATE;
  display_line[DISP_TWO][DISP_RCOL] = RESET_STATE;
  display_line[DISP_THRE][DISP_RCOL] = RESET_STATE;

  display[DISP_ZERO] = &display_line[DISP_ZERO][RESET_STATE];
  display[DISP_ONE] = &display_line[DISP_ONE][RESET_STATE];
  display[DISP_TWO] = &display_line[DISP_TWO][RESET_STATE];
  display[DISP_THRE] = &display_line[DISP_THRE][RESET_STATE];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;

// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}