//------------------------------------------------------------------------------
//
//  Description: This file contains the functions that initialize all the ports.
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

void Init_Port_1(void){
  //--------------------------------------------------------------------
  // Configure PORT 1
// RED_LED         (0x01)      // RED LED – P1_0_LED1
// GRN_LED         (0x02)      // GREEN LED – P1_1_LED2
// V_THUMB         (0x04)      // ADC for Thumb Wheel
// TEST_PROBE      (0x08)      // GP I/O Pin to use to check code operation
// V_DETECT_R      (0x10)      // ADC for Right Detector
// V_DETECT_L      (0x20)      // ADC for Left Detector
// SD_UCB0SIMO     (0x40)      // SPI mode - slave in/master out for SD Card
// SD_UCB0SOMI     (0x80)      // SPI mode - slave out/master in for SD Card 
  //--------------------------------------------------------------------
  P1SEL0 = INIT_PORT; // GP I/O
  P1SEL1 = INIT_PORT; // GP I/O
  P1OUT = INIT_PORT; // set P1 output
  P1DIR = INIT_PORT; // Set P1 direction to input
  
  // P1_0
  P1SEL0 &= ~RED_LED; // RED_LED as GP I/O
  P1SEL1 &= ~RED_LED; // RED_LED as GP I/O
  P1OUT &= ~RED_LED; // Set Red LED On
  P1DIR |= RED_LED; // Set Red LED direction to output
  
  // P1_1
  P1SEL0 &= ~GRN_LED; // GRN_LED as GP I/O
  P1SEL1 &= ~GRN_LED; // GRN_LED as GP I/O
  P1OUT &= ~GRN_LED; // Set Green LED On
  P1DIR |= GRN_LED; // Set Green LED direction to output
 
  // P1_2
  P1SEL0 |= V_THUMB; // ADC input for Thumbwheel
  P1SEL1 |= V_THUMB; // ADC input for Thumbwheel
 
  // P1_3
  P1SEL0 &= ~TEST_PROBE; // TEST_PROBE as GP I/O
  P1SEL1 &= ~TEST_PROBE; // TEST_PROBE as GP I/O
  P1OUT &= ~TEST_PROBE; // Set TEST_PROBE Off
  P1DIR |= TEST_PROBE; // Set TEST_PROBE direction to output
  
  // P1_4
  P1SEL0 |= V_DETECT_R; // ADC input for Right Detector
  P1SEL1 |= V_DETECT_R; // ADC input for Right Detector
 
  // P1_5
  P1SEL0 |= V_DETECT_L; // ADC input for Left Detector
  P1SEL1 |= V_DETECT_L; // ADC input for Left Detector
 
  // P1_6
  P1SEL0 &= ~SD_UCB0SIMO; // USCI_B1 MOSI pin
  P1SEL1 |= SD_UCB0SIMO; // USCI_B1 MOSI pin

  // P1_7
  P1SEL0 &= ~SD_UCB0SOMI; // USCI_B1 MISO pin
  P1SEL1 |= SD_UCB0SOMI; // USCI_B1 MISO pin
}




void Init_Port_2(void) {
  //--------------------------------------------------------------------
  // Configure PORT 2
  // BCLUART_TXD       (0x01)      // BCLUART_TXD
  // BCLUART_RXD       (0x02)      // BCLUART_RXD
  // SD_SPICLK         (0x04)      // SD_SPICLK
  // UCA1TXD           (0x20)      // UCA1TXD
  // UCA1RXD           (0x40)      // UCA1RXD
  //--------------------------------------------------------------------
  P2SEL0 = INIT_PORT; // GP I/O
  P2SEL1 = INIT_PORT; // GP I/O
  P2DIR = INIT_PORT; // Set P2 direction to input

  //P2_0
  P2SEL0 &= ~BCLUART_TXD; // set BCLUART_TXD to function
  P2SEL1 |= BCLUART_TXD; // set BCLUART_TXD to function
  
  //P2_1
  P2SEL0 &= ~BCLUART_RXD; // set BCLUART_RXD to function
  P2SEL1 |= BCLUART_RXD; // set BCLUART_RXD to function  
  
  //P2_2
  P2SEL0 &= ~SD_SPICLK; // set SD_SPICLK to function
  P2SEL1 |= SD_SPICLK; // set SD_SPICLK to function  
  
  //P2_3
  P2SEL0 &= ~P2_3_UNUSED; // P2_3_UNUSED as GP I/O
  P2SEL1 &= ~P2_3_UNUSED; // P2_3_UNUSED as GP I/O
  P2DIR &= ~P2_3_UNUSED; // Set P2_3_UNUSED direction to input
  
  //P2_4
  P2SEL0 &= ~P2_4_UNUSED; // P2_4_UNUSED as GP I/O
  P2SEL1 &= ~P2_4_UNUSED; // P2_4_UNUSED as GP I/O
  P2DIR &= ~P2_4_UNUSED; // Set P2_4_UNUSED direction to input
  
  //P2_5
  P2SEL0 &= ~UCA1TXD; // set UCA1TXD to function
  P2SEL1 |= UCA1TXD; // set UCA1TXD to function   
  
  //P2_6
  P2SEL0 &= ~UCA1RXD; // set UCA1RXD to function
  P2SEL1 |= UCA1RXD; // set UCA1RXD to function   
  
  //P2_7
  P2SEL0 &= ~P2_7_UNUSED; // P2_7_UNUSED as GP I/O
  P2SEL1 &= ~P2_7_UNUSED; // P2_7_UNUSED as GP I/O
  P2DIR &= ~P2_7_UNUSED; // Set P2_7_UNUSED direction to input 
}



void Init_Port_3(int version) {
  //--------------------------------------------------------------------
  // Configure PORT 3
  // IOT_RESET       (0x01) // RESET
  // IOT_STA_MINIAP  (0x02) // IOT_STA_MINIAP
  // IOT_LINK        (0x04) // IOT_LINK
  // IOT_WAKEUP      (0x08) // IOT_WAKEUP
  // L_REVERSE       (0x10) // Left Reverse
  // L_FORWARD       (0x20) // Left Forward
  // R_REVERSE       (0x40) // Right Reverse
  // R_FORWARD       (0x80) // Right Forward  
  //--------------------------------------------------------------------
P3SEL0 = INIT_PORT; // GP I/O
P3SEL1 = INIT_PORT; // GP I/O
P3DIR = PORT_OUT; // Set P3 direction to output
P3OUT = INIT_PORT; // P3 set Low

  //P3_0
P3SEL0 &= ~IOT_RESET; // Set to GP I/O
P3SEL1 &= ~IOT_RESET; // Set to GP I/O
P3OUT &= ~IOT_RESET; // Set out value Low [active]
P3DIR |= IOT_RESET; // Set direction to output

  //P3_1
P3SEL0 &= ~IOT_STA_MINIAP; // Set to GP I/O
P3SEL1 &= ~IOT_STA_MINIAP; // Set to GP I/O
P3OUT |= IOT_STA_MINIAP; // Set out value no Mini AP
P3DIR |= IOT_STA_MINIAP; // Set direction to output

  //P3_2
P3SEL0 &= ~IOT_LINK; // Set to GP I/O
P3SEL1 &= ~IOT_LINK; // Set to GP I/O
P3OUT &= ~IOT_LINK; // Set out value Low [off]
P3DIR |= IOT_LINK; // Set direction to output

  //P3_3
P3SEL0 &= ~IOT_WAKEUP; // Set to GP I/O
P3SEL1 &= ~IOT_WAKEUP; // Set to GP I/O
P3OUT |= IOT_WAKEUP; // Set out value Low [off]
P3DIR |= IOT_WAKEUP; // Set direction to output

  //P3_4
switch(version) {
  case USE_SMCLK:
    P3SEL0 &= ~L_REVERSE; // Set to SMCLK
    P3SEL1 |= L_REVERSE; // 
    P3DIR |= L_REVERSE; // Set direction to output
    break;
    
  default: //default to motor
    P3SEL0 |= L_REVERSE; // Set to GP I/O
    P3SEL1 &= ~L_REVERSE; // Set to GP I/O
    P3DIR |= L_REVERSE; // Set direction to output
  
}

  //P3_5
    P3SEL0 |= L_FORWARD; // Set to GP I/O
    P3SEL1 &= ~L_FORWARD; // Set to GP I/O
    P3DIR |= L_FORWARD; // Set direction to output

      //P3_6
    P3SEL0 |= R_REVERSE; // Set to GP I/O
    P3SEL1 &= ~R_REVERSE; // Set to GP I/O
    P3DIR |= R_REVERSE; // Set direction to output

      //P3_7
    P3SEL0 |= R_FORWARD; // Set to GP I/O
    P3SEL1 &= ~R_FORWARD; // Set to GP I/O
    P3DIR |= R_FORWARD; // Set direction to output
}




void Init_Port_4(void) {
  //--------------------------------------------------------------------
  // Configure PORT 4
  // SD_CS        (0x01)      // SD_CS
  // J4_31        (0x02)      // J4_31
  // J4_32        (0x04)      // J4_32
  // J4_33        (0x08)      // J4_33
  // UCB1_CS_LCD  (0x10)      // UCB1_CS_LCD
  // J3_29        (0x80)      // J3_29  
  //--------------------------------------------------------------------
  P4SEL0 = INIT_PORT; // GP I/O
  P4SEL1 = INIT_PORT; // GP I/O
  P4DIR = INIT_PORT; //set P4 direction
  P4OUT = INIT_PORT; //low or high for output
  
  //P4_0
  P4SEL0 &= ~SD_CS; // Set GP I/O for SD_CS
  P4SEL1 &= ~SD_CS; // Set GP I/O for SD_CS
  P4DIR &= ~SD_CS; // Set SD_CS direction to input  
  
  //P4_1
  P4SEL0 &= ~J4_31; // Set GP I/O for J4_31
  P4SEL1 &= ~J4_31; // Set GP I/O for J4_31
  P4DIR &= ~J4_31; // Set J4_31 direction to input 
  
  //P4_2
  P4SEL0 &= ~J4_32; // Set GP I/O for J4_32
  P4SEL1 &= ~J4_32; // Set GP I/O for J4_32
  P4DIR &= ~J4_32; // Set J4_32 direction to input  
  
  //P4_3
  P4SEL0 &= ~J4_33; // Set GP I/O for J4_33
  P4SEL1 &= ~J4_33; // Set GP I/O for J4_33
  P4DIR &= ~J4_33; // Set J4_33 direction to input  
  
  //P4_4
  P4SEL0 &= ~UCB1_CS_LCD; // Set GP I/O for UCB1_CS_LCD
  P4SEL1 &= ~UCB1_CS_LCD; // Set GP I/O for UCB1_CS_LCD
  P4OUT &= ~UCB1_CS_LCD; // Set UCB1_CS_LCD to low
  P4DIR |= UCB1_CS_LCD; // Set UCB1_CS_LCD direction to output 
  
  //P4_5
  P4SEL0 &= ~P4_5_UNUSED; // Set GP I/O for P4_5_UNUSED
  P4SEL1 &= ~P4_5_UNUSED; // Set GP I/O for P4_5_UNUSED
  P4DIR &= ~P4_5_UNUSED; // Set P4_5_UNUSED direction to input  
  
  //P4_6
  P4SEL0 &= ~P4_6_UNUSED; // Set GP I/O for P4_6_UNUSED
  P4SEL1 &= ~P4_6_UNUSED; // Set GP I/O for P4_6_UNUSED
  P4DIR &= ~P4_6_UNUSED; // Set P4_6_UNUSED direction to input  
  
  //P4_7
  P4SEL0 &= ~J3_29; // Set GP I/O for J3_29
  P4SEL1 &= ~J3_29; // Set GP I/O for J3_29
  P4DIR &= ~J3_29; // Set J3_29 direction to input  
  
} 




void Init_Port_5(void){
//--------------------------------------------------------------------
  // Configure PORT 5
  // SPI_UCB1SIMO (0x01)        // UCB1SIMO
  // SPI_UCB1SOMI (0x02)        // UCB1SOMI
  // SPI_UCB1CLK (0x04)         // SPI mode - clock output—UCB1CLK
  // RESET_LCD (0x08)           // LCD Reset
  // BUTTON2 (0x20)             // Button 2
  // BUTTON1 (0x40)             // Button 1
  // LCD_BACKLITE (0x80)        // LCD Backlight
//--------------------------------------------------------------------
  P5SEL0 = INIT_PORT; // GP I/O
  P5SEL1 = INIT_PORT; // GP I/O
  P5DIR = PORT_OUT; // Set P3 direction to output
  P5OUT = INIT_PORT; // P3 set Low
  P5REN = INIT_PORT; //enable pullup resistor
  P5IES = INIT_PORT;
  P5IFG = INIT_PORT;
  P5IE = INIT_PORT;
  
  //P5_0
  P5SEL0 |= SPI_UCB1SIMO; // USCI_B1 SIMO pin
  P5SEL1 &= ~SPI_UCB1SIMO; // USCI_B1 SIMO pin
 
  //P5_1
  P5SEL0 |= SPI_UCB1SOMI; // USCI_B1 SOMI pin
  P5SEL1 &= ~SPI_UCB1SOMI; // USCI_B1 SOMI pin
 
  //P5_2
  P5SEL0 |= SPI_UCB1CLK; // USCI_B1 SCLK pin
  P5SEL1 &= ~SPI_UCB1CLK; // USCI_B1 SCLK pin
    
  //P5_3
  P5SEL0 &= ~RESET_LCD; // Set GP I/O for RESET_LCD
  P5SEL1 &= ~RESET_LCD; // Set GP I/O for RESET_LCD
  P5OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  P5DIR |= RESET_LCD; // Set RESET_LCD direction to output

  //P5_4
  P5SEL0 &= ~P5_4_UNUSED; // Set GP I/O for P5_4_UNUSED
  P5SEL1 &= ~P5_4_UNUSED; // Set GP I/O for P5_4_UNUSED
  P5DIR &= ~P5_4_UNUSED; // Set P5_4_UNUSED direction to input
  
  //P5_5
  P5SEL0 &= ~BUTTON2; // Set GP I/O for BUTTON2
  P5SEL1 &= ~BUTTON2; // Set GP I/O for BUTTON2
  P5OUT |= BUTTON2; // Configure pullup resistor
  P5DIR &= ~BUTTON2; // Direction = input
  P5REN |= BUTTON2; // Enable pullup resistor
  
  //P5_6
  P5SEL0 &= ~BUTTON1; // Set GP I/O for BUTTON1
  P5SEL1 &= ~BUTTON1; // Set GP I/O for BUTTON1
  P5OUT |= BUTTON1; // Configure pullup resistor
  P5DIR &= ~BUTTON1; // Direction = input
  P5REN |= BUTTON1; // Enable pullup resistor
 
  //P5_7
  P5SEL0 &= ~LCD_BACKLITE; // Set GP I/O for LCD_BACKLITE
  P5SEL1 &= ~LCD_BACKLITE; // Set GP I/O for LCD_BACKLITE
  P5OUT |= LCD_BACKLITE; // Set LCD_BACKLITE Off
  P5DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output
  //--------------------------------------------------------------------
}



void Init_Port_6(void) {
  //--------------------------------------------------------------------
  // Configure PORT 6
  // UCA3TXD         (0x01)      // UCA3TXD
  // UCA3RXD         (0x02)      // UCA3RXD
  // J1_5            (0x04)      // J1_5
  // MAG_INT         (0x08)      // MAG_INT
  //--------------------------------------------------------------------
  P6SEL0 = INIT_PORT; // GP I/O
  P6SEL1 = INIT_PORT; // GP I/O
  P6DIR = INIT_PORT; // Set P6 direction to input

  
  //P6_0
  P6SEL0 |= UCA3TXD; // UCA3TXD as GP I/O
  P6SEL1 &= ~UCA3TXD; // UCA3TXD as GP I/O
 // P6DIR &= ~UCA3TXD; // Set UCA3TXD direction to input  
  
  //P6_1
  P6SEL0 |= UCA3RXD; // UCA3RXD as GP I/O
  P6SEL1 &= ~UCA3RXD; // UCA3RXD as GP I/O
  //P6DIR &= ~UCA3RXD; // Set UCA3RXD direction to input 
  
  //P6_2
  P6SEL0 &= ~J1_5; // J1_5 as GP I/O
  P6SEL1 &= ~J1_5; // J1_5 as GP I/O
  P6DIR &= ~J1_5; // Set J1_5 direction to input  
  
  //P6_3
  P6SEL0 &= ~MAG_INT; // MAG_INT as GP I/O
  P6SEL1 &= ~MAG_INT; // MAG_INT as GP I/O
  P6DIR &= ~MAG_INT; // Set MAG_INT direction to input   
  
  //P6_4
  P6SEL0 &= ~P6_4_UNUSED; // P6_4_UNUSED as GP I/O
  P6SEL1 &= ~P6_4_UNUSED; // P6_4_UNUSED as GP I/O
  P6DIR &= ~P6_4_UNUSED; // Set P6_4_UNUSED direction to input  
  
  //P6_5
  P6SEL0 &= ~P6_5_UNUSED; // P6_5_UNUSED as GP I/O
  P6SEL1 &= ~P6_5_UNUSED; // P6_5_UNUSED as GP I/O
  P6DIR &= ~P6_5_UNUSED; // Set P6_5_UNUSED direction to input  
  
  //P6_6
  P6SEL0 &= ~P6_6_UNUSED; // P6_6_UNUSED as GP I/O
  P6SEL1 &= ~P6_6_UNUSED; // P6_6_UNUSED as GP I/O
  P6DIR &= ~P6_6_UNUSED; // Set P6_6_UNUSED direction to input  
  
  //P6_7
  P6SEL0 &= ~P6_7_UNUSED; // P6_7_UNUSED as GP I/O
  P6SEL1 &= ~P6_7_UNUSED; // P6_7_UNUSED as GP I/O
  P6DIR &= ~P6_7_UNUSED; // Set P6_7_UNUSED direction to input  
  
}



void Init_Port_7(void) {
  //--------------------------------------------------------------------
  // Configure PORT 7
  // I2CSDA            (0x01)      // I2CSDA
  // I2CSCL            (0x02)      // ISCSCL
  // SD_DETECT         (0x04)      // SD_DETECT
  // J4_36             (0x08)      // J4_36
  //--------------------------------------------------------------------
  P7SEL0 = INIT_PORT; // GP I/O
  P7SEL1 = INIT_PORT; // GP I/O
  P7DIR = INIT_PORT; // set P7 direction
  
  //P7_0
  P7SEL0 &= ~I2CSDA; // I2CSDA as GP I/O
  P7SEL1 &= ~I2CSDA; // I2CSDA as GP I/O
  P7DIR &= ~I2CSDA; // Set I2CSDA direction to input  
  
  //P7_1
  P7SEL0 &= ~I2CSCL; // I2CSCL as GP I/O
  P7SEL1 &= ~I2CSCL; // I2CSCL as GP I/O
  P7DIR &= ~I2CSCL; // Set I2CSCL direction to input  
  
  //P7_2
  P7SEL0 &= ~SD_DETECT; // SD_DETECT as GP I/O
  P7SEL1 &= ~SD_DETECT; // SD_DETECT as GP I/O
  P7DIR &= ~SD_DETECT; // Set SD_DETECT direction to input  
  
  //P7_3
  P7SEL0 &= ~J4_36; // J4_36 as GP I/O
  P7SEL1 &= ~J4_36; // J4_36 as GP I/O
  P7DIR &= ~J4_36; // Set J4_36 direction to input  
  
  //P7_4
  P7SEL0 &= ~P7_4_UNUSED; // P7_4_UNUSED as GP I/O
  P7SEL1 &= ~P7_4_UNUSED; // P7_4_UNUSED as GP I/O
  P7DIR &= ~P7_4_UNUSED; // Set P7_4_UNUSED direction to input  
  
  //P7_5
  P7SEL0 &= ~P7_5_UNUSED; // P7_5_UNUSED as GP I/O
  P7SEL1 &= ~P7_5_UNUSED; // P7_5_UNUSED as GP I/O
  P7DIR &= ~P7_5_UNUSED; // Set P7_5_UNUSED direction to input 
  
  //P7_6
  P7SEL0 &= ~P7_6_UNUSED; // P7_6_UNUSED as GP I/O
  P7SEL1 &= ~P7_6_UNUSED; // P7_6_UNUSED as GP I/O
  P7DIR &= ~P7_6_UNUSED; // Set P7_6_UNUSED direction to input  
  
  //P7_7
  P7SEL0 &= ~P7_7_UNUSED; // P7_7_UNUSED as GP I/O
  P7SEL1 &= ~P7_7_UNUSED; // P7_7_UNUSED as GP I/O
  P7DIR &= ~P7_7_UNUSED; // Set P7_7_UNUSED direction to input  
  
}



void Init_Port_8(void) {
  //--------------------------------------------------------------------
  // Configure PORT 8
  // IR_LED    (0x01)      // IR_LED
  // OPT_INT   (0x02)      // OPT_INT
  // TMP_INT   (0x04)      // TMP_INT
  // INT2      (0x08)      // INT2  
  //--------------------------------------------------------------------
  P8SEL0 = INIT_PORT; // GP I/O
  P8SEL1 = INIT_PORT; // GP I/O
  P8OUT = INIT_PORT;
  P8DIR = INIT_PORT; // Set P8 direction to input
  
  //P8_0
  P8SEL0 &= ~IR_LED; // IR_LED as GP I/O
  P8SEL1 &= ~IR_LED; // IR_LED as GP I/O
  P8DIR |= IR_LED; // Set IR_LED direction to output
  P8OUT &= ~IR_LED; // Set out value Low [off]
  
  //P8_1
  P8SEL0 &= ~OPT_INT; // OPT_INT as GP I/O
  P8SEL1 &= ~OPT_INT; // OPT_INT as GP I/O
  P8DIR &= ~OPT_INT; // Set OPT_INT direction to input 
   
  //P8_2
  P8SEL0 &= ~TMP_INT; // TMP_INT as GP I/O
  P8SEL1 &= ~TMP_INT; // TMP_INT as GP I/O
  P8DIR &= ~TMP_INT; // Set TMP_INT direction to input   
  
  //P8_3
  P8SEL0 &= ~INT2; // INT2 as GP I/O
  P8SEL1 &= ~INT2; // INT2 as GP I/O
  P8DIR &= ~INT2; // Set INT2 direction to input 
  
}



void Init_Port_J(void) {
  //--------------------------------------------------------------------
  // Configure PORT J
  //   LFXIN             (0x10)      // LFXIN
  //   LFXOUT            (0x20)      // LFXOUT
  //   HFXIN             (0x40)      // HFXIN
  //   HFXOUT            (0x80)      // HFXOUT
  //--------------------------------------------------------------------
  PJSEL0 = INIT_PORT; // GP I/O
  PJSEL1 = INIT_PORT; // GP I/O
  PJDIR = INIT_PORT; // Set PJ direction to input
  
  //PJ_0
  PJSEL0 &= ~PJ_0_UNUSED; // PJ_0_UNUSED as GP I/O
  PJSEL1 &= ~PJ_0_UNUSED; // PJ_0_UNUSED as GP I/O
  PJDIR &= ~PJ_0_UNUSED; // Set PJ_0_UNUSED direction to input 
  
  //PJ_1
  PJSEL0 &= ~PJ_1_UNUSED; // PJ_1_UNUSED as GP I/O
  PJSEL1 &= ~PJ_1_UNUSED; // PJ_1_UNUSED as GP I/O
  PJDIR &= ~PJ_1_UNUSED; // Set PJ_1_UNUSED direction to input
  
  //PJ_2
  PJSEL0 &= ~PJ_2_UNUSED; // PJ_2_UNUSED as GP I/O
  PJSEL1 &= ~PJ_2_UNUSED; // PJ_2_UNUSED as GP I/O
  PJDIR &= ~PJ_2_UNUSED; // Set PJ_2_UNUSED direction to input  
  
  //PJ_3
  PJSEL0 &= ~PJ_3_UNUSED; // PJ_3_UNUSED as GP I/O
  PJSEL1 &= ~PJ_3_UNUSED; // PJ_3_UNUSED as GP I/O
  PJDIR &= ~PJ_3_UNUSED; // Set PJ_3_UNUSED direction to input  
  
  //PJ_4
  PJSEL0 |= LFXIN; // Set LFXIN to crystal mode
  PJSEL1 &= ~LFXIN; // 
  PJDIR &= ~LFXIN; // Set LFXIN direction to input  
  
  //PJ_5
  PJSEL0 &= ~LFXOUT; // LFXOUT as GP I/O
  PJSEL1 &= ~LFXOUT; // LFXOUT as GP I/O
  PJDIR &= ~LFXOUT; // Set LFXOUT direction to input 
  
  //PJ_6
  PJSEL0 &= ~HFXIN; // HFXIN as GP I/O
  PJSEL1 &= ~HFXIN; // HFXIN as GP I/O
  PJDIR &= ~HFXIN; // Set HFXIN direction to input  
  
  //PJ_7
  PJSEL0 &= ~HFXOUT; // HFXOUT as GP I/O
  PJSEL1 &= ~HFXOUT; // HFXOUT as GP I/O
  PJDIR &= ~HFXOUT; // Set HFXOUT direction to input  
  
}

void Init_Ports(void){
// runs all the initalize functions so every port is initialized
  Init_Port_1();
  Init_Port_2();
  Init_Port_3(USE_L_REVERSE);
  //Init_Port_3(USE_L_REVERSE);
  Init_Port_4();
  Init_Port_5();
  Init_Port_6();
  Init_Port_7();
  Init_Port_8();
  Init_Port_J();
}

void Init_Buttons(void) {
  P5IES |= BUTTON2; // P4.0 Hi/Lo edge interrupt
  P5IFG &= ~BUTTON2; // Clear all P5.5 interrupt flags
  P5IE |= BUTTON2; // P5.5 interrupt enabled
  
  P5IES |= BUTTON1; // P4.0 Hi/Lo edge interrupt
  P5IFG &= ~BUTTON1; // Clear all P5.6 interrupt flags
  P5IE |= BUTTON1; // P5.6 interrupt enabled
}

