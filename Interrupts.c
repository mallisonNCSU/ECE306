//------------------------------------------------------------------------------
//
//  Description: The file contains ISRs for various functions.
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
extern unsigned int Time_Sequence = RESET_STATE;
extern unsigned int Line_Time = RESET_STATE;
extern unsigned int Turn_Time = RESET_STATE;
extern char one_time;

extern volatile int debounce_count1 = RESET_STATE; //debounce counts for buttons 1 and 2
extern volatile int debounce_count2 = RESET_STATE;
extern volatile char debounce1_current = RESET_STATE;
extern volatile char debounce2_current = RESET_STATE;
volatile int ADC_Thumb;
volatile int ADC_Right_Detector;
volatile int ADC_Left_Detector;
extern unsigned long mtimer = RESET_STATE;
extern char calibrate;
extern int ambience;
extern int onblackR;
extern int onblackL;
extern int onwhiteR;
extern int onwhiteL;
extern unsigned int usb0_rx_ring_wr;
extern unsigned int usb0_rx_ring_rd;
extern unsigned int usb0_tx_ring_wr;
extern unsigned int usb0_tx_ring_rd;
extern unsigned int usb3_rx_ring_wr;
extern unsigned int usb3_rx_ring_rd;
extern unsigned int usb3_tx_ring_wr;
extern unsigned int usb3_tx_ring_rd;
extern char USB0_Char_Rx[SMALL_RING_SIZE] = {RESET_STATE};
extern char USB3_Char_Rx[SMALL_RING_SIZE] = {RESET_STATE};
extern int UCA3_index;
extern int UCA0_index;
extern char test_command[COMSIZE] = "HELLOOOO";
extern char baudone[DISP_COL];
extern char baudtwo[DISP_COL];
extern char cbaud;
extern char stage;
extern char command[SMALL_RING_SIZE];
extern char startup;
extern char IOT_Check = RESET_STATE;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerA0 0 Interrupt handler
  //----------------------------------------------------------------------------
  // increments Time_Sequence every 50ms
  Time_Sequence++;
  Line_Time++;
  Turn_Time++;
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
  //----------------------------------------------------------------------------
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
  //----------------------------------------------------------------------------
  //A1 handles debounces for the buttons
  switch(__even_in_range(TA0IV,TIMEOVERFLOW)){
  case RESET_STATE: break; // No interrupt
  case TIMEA1:
    if ((debounce1_current == ALWAYS)) { //if button 1 was pressed, debounce
      debounce_count1++;
      P5IE &= ~BUTTON1;
      if (debounce_count1 > DEBOUNCET) { //1 second
        debounce1_current = RESET_STATE;
        debounce_count1 = RESET_STATE;
        P5IE |= BUTTON1;
      }
    }
    if ((debounce2_current == ALWAYS)) { //if button 2 was pressed, debounce
      debounce_count2++;
      P5IE &= ~BUTTON2;
      if (debounce_count2 > DEBOUNCET) { //1 second
        debounce2_current = RESET_STATE;
        debounce_count2 = RESET_STATE;
        P5IE |= BUTTON2;
      }
    }
    TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
    break;
  case TIMEA2:
    if(mtimer >= MMAX) {
      mtimer = RESET_STATE;
    }
    else {
      if((IOT_Check > RESET_STATE) && (IOT_Check < STTHRE)) {
        mtimer++;
      }
      TA0CCR2 += TA0CCR2_INTERVAL;
    }
    break;
  case TIMEOVERFLOW: // overflow
    
    break;
  default: break;
  }
  //----------------------------------------------------------------------------
}

#pragma vector=PORT5_VECTOR
__interrupt void BUTTON_Interrupt(void) {
  //this ISR triggers whenever a button is pressed (Switches_Process checks that)
  
  // BUTTON 1
  if (P5IFG & BUTTON1) { //interrupts when button 1 is pressed
    
    startup = RESET_STATE;

    
    P5IFG &= ~BUTTON1;
    P5IE &= ~BUTTON1;
    debounce1_current = ALWAYS;
  }
  // BUTTON 2
  if (P5IFG & BUTTON2) {  //interrupts when button 2 is pressed

    P5IFG &= ~BUTTON2;
    P5IE &= ~BUTTON2;
    
    debounce2_current = ALWAYS;
  }
  TA0CCTL1 |= CCIE;
} 


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA0IV,INTINT)){
  case RESET_STATE: // Vector 0 - no interrupt
    break;
  case STTWO: // Vector 2 - RXIFG
    temp = usb0_rx_ring_wr;
    USB0_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
    // TODO uca3 outchar
    out_character3(USB0_Char_Rx[temp]);
    out_character0(USB0_Char_Rx[temp]);
    if (++usb0_rx_ring_wr >= (SMALL_RING_SIZE)){
      usb0_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case STFOUR: // Vector 4 – TXIFG
    switch(UCA0_index++){
      case RESET_STATE: //
      case ALWAYS: //
      case STTWO: //
      case STTHRE: //
      case STFOUR: //
      case STFIVE: //
      case STSIX: //
      case STSEV: //
      case STEIGH: //
        UCA0TXBUF = test_command[UCA0_index];
        break;
      case STNINE: //
        UCA0TXBUF = LF;
        break;
      case STTEN: // Vector 0 - no interrupt
        UCA0TXBUF = ENDF;
        break;
      default:
        UCA0IE &= ~UCTXIE; // Disable TX interrupt
        break;
    } break;
  default: break;
  }
}
  //------------------------------------------------------------------------------
  

#pragma vector=USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  unsigned int temp;
  unsigned int temp2;
  switch(__even_in_range(UCA3IV,INTINT)){
  case RESET_STATE: // Vector 0 - no interrupt
    break;
  case STTWO: // Vector 2 - RXIFG
    temp = usb3_rx_ring_wr;
    temp2 = UCA3RXBUF;
    if(temp2 == ENDF) {
      break;
    }
    if(temp2 == '*') { //* means there is a command to follow, look out for it
      stage += ALWAYS; //stage keeps track of how many commands need to be executed
      temp = RESET_STATE;
      usb3_rx_ring_wr = RESET_STATE;
      int i;
      for(i=RESET_STATE;i<SMALL_RING_SIZE;i++) {
        USB3_Char_Rx[i] = RESET_STATE;
      }
    }
    USB3_Char_Rx[temp] = temp2; // RX -> USB_Char_Rx character
    out_character0(USB3_Char_Rx[temp]);
    if (++usb3_rx_ring_wr >= (SMALL_RING_SIZE)){
      usb3_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case STFOUR: // Vector 4 – TXIFG
    switch(UCA3_index++){
      case RESET_STATE: //
      case ALWAYS: //
      case STTWO: //
      case STTHRE: //
      case STFOUR: //
      case STFIVE: //
      case STSIX: //
      case STSEV: //
      case STEIGH: //
      case STNINE: // 
          UCA3TXBUF = command[UCA3_index];   
        break;
      case STTEN: // Vector 0 - no interrupt
        UCA3TXBUF = LF;
        break;
      case STELEV:
        UCA3TXBUF = ENDF;
        break;
      default:
        UCA3IE &= ~UCTXIE; // Disable TX interrupt
        break;
    } break;
  default: break;
  }
}

  
#pragma vector = ADC12_B_VECTOR
  __interrupt void ADC12_ISR(void){
    switch(__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG)){
    case ADC12IV__NONE: break; // Vector 0: No interrupt
    case ADC12IV__ADC12OVIFG: break; // Vector 2: ADC12MEMx Overflow
    case ADC12IV__ADC12TOVIFG: break; // Vector 4: Conversion time overflow
    case ADC12IV__ADC12HIIFG: break; // Vector 6: ADC12BHI
    case ADC12IV__ADC12LOIFG: break; // Vector 8: ADC12BLO
    case ADC12IV__ADC12INIFG: break; // Vector 10: ADC12BIN
    case ADC12IV__ADC12IFG0: break; // Vector 12: ADC12MEM0 Interrupt
    case ADC12IV__ADC12IFG1: break; // Vector 14: ADC12MEM1 Interrupt
    case ADC12IV__ADC12IFG2: // Vector 16: ADC12MEM2 Interrupt
      ADC_Thumb = ADC12MEM0; // A02 ADC10INCH_2
      ADC_Right_Detector = ADC12MEM1; // A05 ADC10INCH_4
      ADC_Left_Detector = ADC12MEM2; // A04 ADC10INCH_5
      break;
    case ADC12IV__ADC12IFG3: break; // Vector 18: ADC12MEM3
    case ADC12IV__ADC12IFG4: break; // Vector 20: ADC12MEM4
    case ADC12IV__ADC12IFG5: break; // Vector 22: ADC12MEM5
    case ADC12IV__ADC12IFG6: break; // Vector 24: ADC12MEM6
    case ADC12IV__ADC12IFG7: break; // Vector 26: ADC12MEM7
    case ADC12IV__ADC12IFG8: break; // Vector 28: ADC12MEM8
    case ADC12IV__ADC12IFG9: break; // Vector 30: ADC12MEM9
    case ADC12IV__ADC12IFG10: break; // Vector 32: ADC12MEM10
    case ADC12IV__ADC12IFG11: break; // Vector 34: ADC12MEM11
    case ADC12IV__ADC12IFG12: break; // Vector 36: ADC12MEM12
    case ADC12IV__ADC12IFG13: break; // Vector 38: ADC12MEM13
    case ADC12IV__ADC12IFG14: break; // Vector 40: ADC12MEM14
    case ADC12IV__ADC12IFG15: break; // Vector 42: ADC12MEM15
    case ADC12IV__ADC12IFG16: break; // Vector 44: ADC12MEM16
    case ADC12IV__ADC12IFG17: break; // Vector 46: ADC12MEM17
    case ADC12IV__ADC12IFG18: break; // Vector 48: ADC12MEM18
    case ADC12IV__ADC12IFG19: break; // Vector 50: ADC12MEM19
    case ADC12IV__ADC12IFG20: break; // Vector 52: ADC12MEM20
    case ADC12IV__ADC12IFG21: break; // Vector 54: ADC12MEM21
    case ADC12IV__ADC12IFG22: break; // Vector 56: ADC12MEM22
    case ADC12IV__ADC12IFG23: break; // Vector 58: ADC12MEM23
    case ADC12IV__ADC12IFG24: break; // Vector 60: ADC12MEM24
    case ADC12IV__ADC12IFG25: break; // Vector 62: ADC12MEM25
    case ADC12IV__ADC12IFG26: break; // Vector 64: ADC12MEM26
    case ADC12IV__ADC12IFG27: break; // Vector 66: ADC12MEM27
    case ADC12IV__ADC12IFG28: break; // Vector 68: ADC12MEM28
    case ADC12IV__ADC12IFG29: break; // Vector 70: ADC12MEM29
    case ADC12IV__ADC12IFG30: break; // Vector 72: ADC12MEM30
    case ADC12IV__ADC12IFG31: break; // Vector 74: ADC12MEM31
    case ADC12IV__ADC12RDYIFG: break; // Vector 76: ADC12RDY
    default: break;
    }
  }