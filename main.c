//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Michelle Allison
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include "msp430.h"
#include "functions.h"
#include <string.h>
#include "macros.h"

// Global Variables
//volatile char slow_input_down;
extern char display_line[DISP_LINES][DISP_COL]; //used for display
extern char *display[DISP_LINES];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern unsigned int Time_Sequence; //general use timer
extern unsigned int Line_Time; //timers for black line
extern unsigned int Turn_Time; 

extern volatile char thousands; //H to D values (for detectors)
extern volatile char hundreds;
extern volatile char tens;
extern volatile char ones;
extern volatile int ADC_Thumb; //thumb wheel value
extern volatile int ADC_Right_Detector; //right detector value
extern volatile int ADC_Left_Detector; //left detector value
extern volatile char emit_state; //has if emitter is on/off
extern unsigned long mtimer; //millisecond timer value
extern char msix; //millisecond timer number places
extern char mfive;
extern char mfour;
extern char mthree;
extern char mtwo;
extern char mone;
extern int ambience = MAXBIT; //black line calibration values
extern int onblackR = DEFRB; 
extern int onblackL = DEFLB;
extern int onwhiteR = OFFLINE;
extern int onwhiteL = OFFLINE;
extern char calibrate = RESET_STATE; //calibrate state
extern char one_time = RESET_STATE; //used for baudrate state machine
extern unsigned int check_time; //timer used for testing
extern int UCA3_index = RESET_STATE; //TX state machines
extern int UCA0_index = RESET_STATE; 
extern char test_command[COMSIZE]; //used for testing
extern unsigned int usb0_rx_ring_wr; //various TX/RX ring buffer indexes
extern unsigned int usb0_rx_ring_rd;
extern unsigned int usb0_tx_ring_wr;
extern unsigned int usb0_tx_ring_rd;
extern unsigned int usb3_rx_ring_wr;
extern unsigned int usb3_rx_ring_rd;
extern unsigned int usb3_tx_ring_wr;
extern unsigned int usb3_tx_ring_rd;
extern char USB0_Char_Rx[SMALL_RING_SIZE] ; //UCA0 buffer
extern char USB3_Char_Rx[SMALL_RING_SIZE] ; //UCA3 buffer
extern char baudone[DISP_COL] = "  115,200 "; //baudrate for display
extern char baudtwo[DISP_COL] = "  460,800 "; //baudrate for display
extern char cbaud = BAUDRONE; //current baudrate
extern char command[SMALL_RING_SIZE] = {RESET_STATE}; //holds stuff received through IOT
extern char stage = RESET_STATE; //stage of IOT interpretation
extern char ipaddr1[DISP_RCOL] = {' '}; //holds first half of IP
extern char ipaddr2[DISP_RCOL] = {' '}; //holds second half of IP
extern char ssid[DISP_RCOL] = "ncsu"; //holds ssid
extern char empty_line[DISP_COL] = "          "; //empty line for display
extern char command_buffer[CLENTHR] = {RESET_STATE}; //holds 3 IOT commands
extern char cbuffs = RESET_STATE; //location of next command slot to fill in command_buffer
extern char cnum = RESET_STATE; //location of next command to execute in command_buffer
extern char startup = RESET_STATE; //has whether in startup state or not
extern char excommand[CLENGTH] = {RESET_STATE}; //has current command to execute
extern char IOT_Check; //stage of project, from IOT control to black line
extern char m_display[DISP_COL] = "T:    .   "; //displays millisecond timer

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  
  
  Init_Ports();                        // Initialize Ports
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  
  Init_Buttons();
  
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timer_A0();
  Init_Timer_B0();
  Init_ADC();
  Init_LCD();                          // Initialize LCD
  lcd_4line();
  Init_Serial_UCA0(BAUDRONE); // Initialize Serial Port for USB
  Init_Serial_UCA3(BAUDRONE);
  char empty_line[DISP_COL] = "          ";
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  Display_Text("  waiting ",empty_line,empty_line,empty_line);
  int i;
  P3OUT |= IOT_RESET;
  char get_ip[CLENTWO] = "AT+S.STS=ip_ipaddr";
  char open_port[SOCKLEN] = "AT+S.SOCKD=43333,u"; 
  char only_once = RESET_STATE;
  char IOT_State = ALWAYS;
  
  char on_line;
  int left_detector;
  int right_detector;
  while(ALWAYS) {                      // Can the Operating system run
    Mtimer_D();
    m_display[STTHRE] = msix; //update display line of timer
    m_display[STFOUR] = mfive;
    m_display[STFIVE] = mfour;
    m_display[STSEV] = mthree;
    m_display[STEIGH] = mtwo;
    m_display[STNINE] = mone;
    
    
    left_detector = ADC_Left_Detector;
    right_detector = ADC_Right_Detector;
     
    switch(Time_Sequence) {
    case STFOUR: //every 200 ms, update timer display
      strcpy(display_line[DISP_ZERO], m_display);
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      break;
    case TENSEC: //every ten seconds, reset Time_Sequence
      Time_Sequence = RESET_STATE;
      break;
    default:
      break;
    }
    Display_Process();
    
    if((Time_Sequence >= EIGHSEC) && (startup == RESET_STATE)) {
      //let wifi module start up, then fetch IP and open socket
        lcd_4line();
        for(i=RESET_STATE;i<IPCLEN; i++) {
          out_character3(get_ip[i]);
        }
        out_character3(LF);
        out_character3(ENDF);
        usb3_rx_ring_wr = RESET_STATE;
        startup = ALWAYS;
        stage = STTEN;
    }
    
    switch(one_time) { //set baudrate
      case RESET_STATE:
         if(cbaud == BAUDRFOUR) {
          Init_Serial_UCA3(BAUDRFOUR); 
         }
         if(cbaud == BAUDRONE) {
          Init_Serial_UCA3(BAUDRONE);
         }
         one_time = ALWAYS;
         break;
      default: break;
    }   
    
  if(IOT_Check == RESET_STATE) { //if in control mode, receive commands from wifi module
    if(usb3_rx_ring_rd != usb3_rx_ring_wr) {
      usb3_rx_ring_rd = usb3_rx_ring_wr;
        for(i=RESET_STATE; i<(SMALL_RING_SIZE); i++) {
          command[i] = USB3_Char_Rx[i];
        }
      }
      update_display = ALWAYS;
      display_changed = ALWAYS;
      if((stage < STNINE) && (stage >= ALWAYS)) { //keep command queue between 1 and 9
        command_handle(USB3_Char_Rx);
        if(stage != STNINE) {
          fetch_command(); //get command into buffer
          execute_command(excommand); //execute command
        }
        stage -= ALWAYS;
        if(stage == STNINE) {
          stage = RESET_STATE;
        }
      }
      if(stage == STTEN) { //fetches IP, opens socket
        ip_finger(USB3_Char_Rx);
        for(i=RESET_STATE;i<SOCKLEN; i++) {
          out_character3(open_port[i]);
        }
        out_character3(LF);
        out_character3(ENDF);
        stage = RESET_STATE;
      }
  }
  if(IOT_Check == STTWO) { //if in black line mode, keep an eye out for exit command and follow line
    lcd_4line();
    command_handle(USB3_Char_Rx);
    switch(IOT_State) {
    case ALWAYS: //ready
      Emit_Power(ALWAYS);
      strcpy(display_line[DISP_ZERO], "  Ready   ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      IOT_State = STTWO;
      break;
    case STTWO: //go forward, look for black line
      Emit_Power(ALWAYS);
      left_detector = ADC_Left_Detector;
      right_detector = ADC_Right_Detector;
      if((left_detector > (1.1*onwhiteL)) || (right_detector > (1.1*onwhiteR))) {
        on_line = CHARO;
      } else {
        on_line = CHARZ;
      }
      strcpy(display_line[DISP_ZERO], "  Looking ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      if(only_once == RESET_STATE) {
        Left_Forward(defaulspeedL);
        Right_Forward(defaulspeedR);
        mtimer = RESET_STATE;
        only_once = ALWAYS;
      }
      if(on_line != CHARZ) { //if on line, move on to stop state
        IOT_State = STTHRE;
        only_once = RESET_STATE;
        Left_Forward(RESET_STATE);
        Right_Forward(RESET_STATE);
        Line_Time = RESET_STATE;
      }
      break;
    case STTHRE: //stop for 1.5 seconds
        Left_Forward(RESET_STATE);
        Right_Forward(RESET_STATE);
        strcpy(display_line[DISP_ZERO], "  Waiting ");
        update_string(display_line[DISP_ZERO], DISP_ZERO);
        display_changed = ALWAYS;
        update_display = ALWAYS;
        if(Line_Time > OHSEC) {
          strcpy(display_line[DISP_ZERO], "          ");
          update_string(display_line[DISP_ZERO], DISP_ZERO);
          display_changed = ALWAYS;
          update_display = ALWAYS;
          IOT_State = STFOUR;
          Turn_Time = RESET_STATE;
        }
        break; 
    case STFOUR: //go forward until off line or right detector hits the black--
      //only left detector should be on black
      strcpy(display_line[DISP_ZERO], "  Forward ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      if(only_once == RESET_STATE) {
        Left_Forward(defaulspeedL);
        Right_Forward(defaulspeedR);
        only_once = ALWAYS;
      }
      if((left_detector < onblackL) && (right_detector < onblackR)) { //off line, that means
        //car strayed from line towards the right, which means it should turn left
        IOT_State = STFIVE;
        only_once = RESET_STATE;
      }
      else if(right_detector >= onblackR) { //right detector is on line, start turning right
        IOT_State = STSIX;
        only_once = RESET_STATE;
      }
      break;
    case STFIVE: //turn left
      strcpy(display_line[DISP_ZERO], "   Left   ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      if(only_once == RESET_STATE) {
        Left_Forward(RESET_STATE);
        Right_Forward(defaulspeedR);
        only_once = ALWAYS;
      }
      if((left_detector >= onblackL) && (right_detector < onblackR)) { //only left detector is on line,
        //go forward
        only_once = RESET_STATE;
        IOT_State = STFOUR;
      }
      else if(right_detector >= onblackR){ //the right detector is on the line, so turn right
        only_once = RESET_STATE;
        IOT_State = STSIX;
      }
      break;
    case STSIX: //turn right
      strcpy(display_line[DISP_ZERO], "   Right  ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      if(only_once == RESET_STATE) {
        Left_Forward(defaulspeedL);
        Right_Forward(RESET_STATE);
        only_once = ALWAYS;
      } 
      if((left_detector >= onblackL) && (right_detector < onblackR)) { //only left detector is on line,
        //go forward
        only_once = RESET_STATE;
        IOT_State = STFOUR;
      }
        break;
  }
  if(IOT_Check == STTHRE) { //car has received exit command, exit circle
      strcpy(display_line[DISP_ZERO], " Stopping ");
      update_string(display_line[DISP_ZERO], DISP_ZERO);
      display_changed = ALWAYS;
      update_display = ALWAYS;
      Left_Forward(defaulspeedL);
      Right_Forward(defaulspeedR);
      Time_Sequence = RESET_STATE;
      while(Time_Sequence < FIVSEC) { //drive straight for 5 seconds
        
      }
      Left_Forward(RESET_STATE);
      Right_Forward(RESET_STATE);
      IOT_Check = RESET_STATE;
    }
  
  }
  
  }
}
//------------------------------------------------------------------------------


