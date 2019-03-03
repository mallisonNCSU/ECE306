//------------------------------------------------------------------------------
//
//  Description: This file contains the functions that initialize and manage serial
// communication.
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

extern char display_line[DISP_LINES][DISP_COL];
extern char *display[DISP_LINES];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

extern unsigned int usb0_rx_ring_wr = RESET_STATE;
extern unsigned int usb0_rx_ring_rd = RESET_STATE;
extern unsigned int usb0_tx_ring_wr = RESET_STATE;
extern unsigned int usb0_tx_ring_rd = RESET_STATE;

extern unsigned int usb3_rx_ring_wr = BEGINNING;
extern unsigned int usb3_rx_ring_rd = BEGINNING;
extern unsigned int usb3_tx_ring_wr = BEGINNING;
extern unsigned int usb3_tx_ring_rd = BEGINNING;
extern char USB0_Char_Rx[SMALL_RING_SIZE] ;
extern char USB3_Char_Rx[SMALL_RING_SIZE] ;
extern char ipaddr1[DISP_RCOL] ;
extern char ipaddr2[DISP_RCOL] ;
extern char ssid[DISP_RCOL];
extern char empty_line[DISP_COL];
extern char command_buffer[CLENTHR] ;
extern char cbuffs ;
extern unsigned int Time_Sequence;
extern char startup;
extern char excommand[CLENGTH];
extern char cnum;
extern char stage;
extern char IOT_Check;
extern char m_display[DISP_COL];


void Init_Serial_UCA0(int serial){
  int i;
  for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
    USB0_Char_Rx[i] = RESET_STATE; // USB Rx Buffer
  }
  usb0_rx_ring_wr = BEGINNING;
  usb0_rx_ring_rd = BEGINNING;
  usb0_tx_ring_wr = BEGINNING;
  usb0_tx_ring_rd = BEGINNING;
  
  // Configure UART 0
  UCA0CTLW0 = RESET_STATE; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
  // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) – INT(N/16)] × 16)
  // = ([833.333/16-INT(833.333/16)]*16)
  // = (52.08333333-52)*16
  // = 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  
  if(serial==BAUDRONE) {
    UCA0BRW = ONEBRW; // 115,200 Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA0MCTLW = ONEN ;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
  }
  if(serial==BAUDRFOUR) {
    UCA0BRW = FOURBRW; // 4watever Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA0MCTLW = FOURN ;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
    
  }
}

void Init_Serial_UCA3(int serial){
  int i;
  for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
    USB3_Char_Rx[i] = RESET_STATE; // USB Rx Buffer
  }
  
  usb3_rx_ring_wr = BEGINNING;
  usb3_rx_ring_rd = BEGINNING;
  /*
  for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
  USB_Char_Tx[i] = 0x00; // USB Tx Buffer
}*/
 
  usb3_tx_ring_wr = BEGINNING;
  usb3_tx_ring_rd = BEGINNING;
  
  
  UCA3CTLW0 = RESET_STATE; // Use word register
  UCA3CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA3CTLW0 |= UCSWRST; // Set Software reset enable
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
  // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) – INT(N/16)] × 16)
  // = ([833.333/16-INT(833.333/16)]*16)
  // = (52.08333333-52)*16
  // = 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  
  if(serial==BAUDRONE) {
    
    UCA3BRW = BAUDRFOUR; // 115,200 Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA3MCTLW = ONEN ;
  }
  if(serial==BAUDRFOUR) {
    
    UCA3BRW = BAUDRONE; // 4 Baud
    // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
    // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
    UCA3MCTLW = FOURN ;
  }
    UCA3CTL1 &= ~UCSWRST; // Release from reset
    UCA3IE |= UCRXIE; // Enable RX interrupt
}

void out_character0(char character){
  //------------------------------------------------------------------------------
  // The while loop will stall as long as the Flag is not set [port is busy]
  while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
  UCA0TXBUF = character;
  //------------------------------------------------------------------------------
}

void out_character3(char character){
  //------------------------------------------------------------------------------
  // The while loop will stall as long as the Flag is not set [port is busy]
  while (!(UCA3IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
  UCA3TXBUF = character;
  //------------------------------------------------------------------------------
}

//fetches IP from module output, modifies ipaddr1 and ipaddr 2 (2 lines for display)
void ip_finger(char * ipaddr) {
  int i;
  char ip_state = RESET_STATE;
  char return_ip[IPLEN] = {RESET_STATE};
  char temp;
  for(i=RESET_STATE;i<DISP_RCOL;i++) {
    ipaddr1[i] = ' ';
    ipaddr2[i] = ' ';
  }
  for(i=RESET_STATE;i<IPLENT;i++) { //get full ip from ipaddr
    if((ipaddr[IPLENO + i] == ENDF) || (ipaddr[IPLENT + i] == LF)) {
      break;
    }
      return_ip[i] = ipaddr[IPLENT + i];
  }
  for(i=RESET_STATE;i<IPLENO;i++) { //copy first 2 sections into ipaddr1
    if(return_ip[i] == '.') {
      ip_state++;
    }
    if(ip_state < STTWO) {
      ipaddr1[STTWO + i] = return_ip[i];
    }
    if(ip_state > ALWAYS) {
      temp = i;
      break;
    }
  }
  for(i=RESET_STATE;i<IPLENT;i++) { //copy second 2 sections into ipaddr2
    if((return_ip[temp + i] == LF) || (return_ip[temp + i] == ENDF) || (return_ip[temp + i] == RESET_STATE)){
      break;
    }
      ipaddr2[STTWO+i] = return_ip[temp + i];
  }
  Display_Text(m_display,ipaddr1,ipaddr2,"          "); //display IP address
}

void command_handle(char * statement) { //makes sure command is valid
//modifies, cbuffs, command_buffer
  char newcommand[CLENGTH];
  int i;
  int temp;
  char valid = ALWAYS;
  for(i=RESET_STATE;i<SMALL_RING_SIZE;i++) { //is the prefix there?
    temp = RESET_STATE;
    valid = RESET_STATE;
    if(statement[i] == '*') {
      temp = i;
      valid = ALWAYS;
      break;
    }
  }
  if(statement[i+ALWAYS] == 'S') { //stop if theres an S after the prefix
          valid = ALWAYS;
          lcd_BIG_mid();
          Display_Text(ssid,"   STOP   ",empty_line,empty_line);
          Right_Forward(RESET_STATE);
          Left_Forward(RESET_STATE);
          stage = STNINE;
          return;
  }
  if(statement[temp + CLENGTH] != LF) { //is the command the correct length (11)?
      valid = RESET_STATE;
  }
  if(valid == RESET_STATE) { //if there is no prefix or incorrect length, error
      lcd_BIG_mid();
      Display_Text(ssid,"   Error  ","  invalid ",empty_line);
      stage = STNINE;
      return;
  } else {
    for(i=RESET_STATE;i<CLENGTH;i++) {
      newcommand[i] = statement[temp + i];
    }
    for(i=RESET_STATE;i<STFOUR;i++) { //checks security code
      switch (i){
      case RESET_STATE:
        if(newcommand[i+ALWAYS] == '4') {
          valid = ALWAYS;
          break;
        } else {
          valid = RESET_STATE;
        }
        break;
      case ALWAYS:
        if(newcommand[i+ALWAYS] != '3') {
          valid = RESET_STATE;
        }
        break;
      case STTWO:
      case STTHRE:
        if(newcommand[i+ALWAYS] != '1') {
          valid = RESET_STATE;
        }
        break;
      }
    }
    if(valid == RESET_STATE) { //security code wrong
      lcd_BIG_mid();
      Display_Text(ssid,"   Error  ","wrong code",empty_line);
      stage = STNINE;
      return;
    } else {
      if(newcommand[STFIVE] == 'K') { //enter black line mode
        IOT_Check = STTWO;
        Display_Text(m_display,"          ","          ","          ");
        return;
      }
      if(newcommand[STFIVE] == 'E') { //exit black line mode
        IOT_Check = STTHRE;
        Display_Text(m_display,"          ","          ","          ");
        return;
      }
      if(IOT_Check > RESET_STATE) { //if in black line mode, don't edit buffer
        return;
      }
      if(cbuffs > LENSAFE) { //loop cbuffs
        cbuffs = RESET_STATE;
      }
      for(i=RESET_STATE;i<CLENGTH;i++) { //copy command into buffer
        command_buffer[cbuffs + i] = newcommand[i];
      }
      cbuffs += CLENGTH; //cbuffs is where the next command should go in the buffer
      }
    }
  lcd_BIG_mid();
  Display_Text("   ncsu   ",newcommand,empty_line,empty_line); //display command
}

void fetch_command(void) { //gets a command to execute
  //modifies cnum, excommand
  int i;
  switch(cnum) { //buffer holds 3 commands, cnum is where the next command to execute is
    case RESET_STATE: //command in first slot
      for(i=RESET_STATE;i<CLENGTH;i++) {
        excommand[i] = command_buffer[i];
      }
        cnum = CLENGTH;
        break;
    case CLENGTH: //command in second slot
      for(i=RESET_STATE;i<CLENGTH;i++) {
        excommand[i] = command_buffer[i+CLENGTH];
      }
      cnum = CLENTWO;
      break;
    case CLENTWO: //command in third slot
      for(i=RESET_STATE;i<CLENGTH;i++) {
        excommand[i] = command_buffer[i+CLENTWO];
      }
      cnum = RESET_STATE;
      break;
    }
  }


void execute_command(char * statement) { //interprets and executes command
  //command structure: *4311F00F00 first F is left wheel, second is right, 00s are speed from 0-99
  int speedL = 300*((TEN*(statement[STSIX]-ASCIIO)) + (statement[STSEV]-ASCIIO));
  int speedR = 300*((TEN*(statement[STNINE]-ASCIIO)) + (statement[STTEN]-ASCIIO));
  switch(statement[STFIVE]) {
    case 'F':
      Left_Forward(speedL);
      break;
    case 'B':
        Left_Reverse(speedL);
        break;
  }
  switch(statement[STEIGH]) {
    case 'F':
      Right_Forward(speedR);
      break;
    case 'B':
        Right_Reverse(speedR);
        break;
  }
}


