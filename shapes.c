//------------------------------------------------------------------------------
//
//  Description: This file contains the routines for turning the motors on and
//      off as well as the functons handling the shapes.
//
//  Michelle Allison
//  February 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

extern char display_line[DISP_LINES][DISP_COL];
extern char *display[DISP_LINES];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern unsigned int Time_Sequence;
extern unsigned int Line_Time;
extern int time_elapsed;
extern char mdisplay[DISP_COL];
extern unsigned long mtimer;
extern char msix = RESET_STATE;
extern char mfive = RESET_STATE;
extern char mfour = RESET_STATE;
extern char mthree = RESET_STATE;
extern char mtwo = RESET_STATE;
extern char mone = RESET_STATE;

void Right_Reverse(int speed) {
  //turns motor on/off according to speed
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = speed; 
}

void Left_Reverse(int speed) {
  //turns motor on/off according to speed
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = speed; 
}

void Right_Forward(int speed) {
  //turns motor on/off according to speed
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = speed; 
}

void Left_Forward(int speed) {
  //turns motor on/off according to speed
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = speed; 
}

void Mtimer_D(void) {
//modifies msix,mfive,mfour,mthree,mtwo,mone
  
//basically H to D function except for a much bigger number
  long value_passed = mtimer;
  long try_numb = MHTHOUS;
  msix = RESET_STATE;
  while(msix == RESET_STATE) { //hundred thousands place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      msix = (try_numb / HTHOUS) + ASCIIO;
      break;
    }
    try_numb -= HTHOUS;
  }
  try_numb = MTTHOUS;
  mfive = RESET_STATE;
  while(mfive == RESET_STATE) { //ten thousands place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      mfive = (try_numb / TTHOUS) + ASCIIO;
      break;
    }
    try_numb -= TTHOUS;
  }
  try_numb = MTHOUS;
  mfour = RESET_STATE;
  while(mfour == RESET_STATE) { //thousands place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      mfour = (try_numb / THOUS) + ASCIIO;
      break;
    }
    try_numb -= THOUS;
  }
  try_numb = MHUND;
  mthree = RESET_STATE;
  while(mthree == RESET_STATE) { //hundreds place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      mthree = (try_numb / HUND) + ASCIIO;
      break;
    }
    try_numb -= HUND;
  }
  try_numb = MTEN;
  mtwo = RESET_STATE;
  while(mtwo == RESET_STATE) { //tens place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      mtwo = (try_numb / TENS) + ASCIIO;
      break;
    }
    try_numb -= TENS;
  }
  try_numb = STNINE;
  mone = RESET_STATE;
  while(mone == RESET_STATE) { //ones place
    if(value_passed >= try_numb) {
      value_passed -= try_numb;
      mone = (try_numb / ALWAYS) + ASCIIO;
      break;
    }
    try_numb -= ALWAYS;
  }
}

void Display_Text(char *string_one, char *string_two, char *string_three, char *string_four) {
  // sets up display to show whatever the arguments are
  P5OUT |= LCD_BACKLITE; // turns on backlight
  strcpy(display_line[DISP_ZERO], string_one);
  update_string(display_line[DISP_ZERO], DISP_ZERO);
  strcpy(display_line[DISP_ONE], string_two);
  update_string(display_line[DISP_ONE], DISP_ONE);
  strcpy(display_line[DISP_TWO], string_three);
  update_string(display_line[DISP_TWO], DISP_TWO);
  strcpy(display_line[DISP_THRE], string_four);
  update_string(display_line[DISP_THRE], DISP_THRE);
  display_changed = ALWAYS;
  update_display = ALWAYS;
  enable_display_update();
  Display_Process();
}