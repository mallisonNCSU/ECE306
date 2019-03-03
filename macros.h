//------------------------------------------------------------------------------
//
//  Description: This file contains macros.
//
//
//  Michelle Allison
//  1/31/2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1
#define INIT_PORT            (0x00) // port sel,dir,out bits 0
#define PORT_OUT             (0xFF) // set port out to high

#define DISP_ZERO               (0) //display lines 1 through 4
#define DISP_ONE                (1)
#define DISP_TWO                (2)
#define DISP_THRE               (3)
#define LOOP_TEN               (11) //ten loops  

#define THOUS_MSEC             (20) //1250 msec
#define SEVF_MSEC              (15) //750 msec
#define FHUND_MSEC             (10) //500 msec
#define TFIF_MSEC               (5) //250 msec
#define TENSEC                 (200)

#define DISP_LINES              (4) //four lines of display
#define DISP_COL               (11) //10 + 1 columns
#define DISP_RCOL              (10) //10 columns

#define BUTTON2 (0x20) // 5.5 Button 1
#define BUTTON1 (0x40) // 5.6 Button 2
//MACROS for clocks.c===========================================================
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK                (0x01) // Any incorrect password locks registers
#define THOUS (1000)
#define TOPTHOUS (9000)
#define HUND (100)
#define TOPHUND (900)
#define TENS (10)
#define TOPTENS (90)
#define ONES (1)
#define TOPONES (9)
#define ASCIIOFF (0x30)
#define CHARTHOUS       (4)
#define CHARHUND        (5)
#define CHARTENS        (6)
#define CHARONES        (7)
#define CHAREMIT (3)
#define CHARON (8)
#define OFFLINE (300)
#define LINEINT (500)
#define DEFB (1000)
#define CHARZ (48)
#define CHARO (49)
#define CHARR (82)
#define CHARL (76)
#define SPFOL (16000)
#define SPFOR (13000)
#define SPTRL (17000)
#define SPTRR (15000)
#define CIRCL (10000)
#define CIRCR (9500)
#define EITSEC (400)
#define DEFAUL (11)
#define MAXBIT (4090)
#define STTWO (2)
#define STTHRE (3)
#define STFOUR (4)
#define STFIVE (5)
#define STSIX (6)
#define STSEV (7)
#define STEIGH (8)
#define STNINE (9)
#define STTEN (10)
#define PERCENT (1.1)
#define LRLINE (1.4)
#define HALF (.5)
#define TIMETWO (30)
#define TIMETHRE (10)
#define TIMEFOU (5)
#define TIMEFIV (5)
#define TIMESEV (14)
#define TIMEEIG (14)
#define MMAX (999800)
#define SPTTRL (17000)
#define SPTTRR (15000)
#define ASCIIO (48)
#define BEGINNING (0)
#define SMALL_RING_SIZE (100)
#define BAUDRONE (1)
#define BAUDRFOUR (4)
#define COMSIZE (8)
#define ONEBRW (4)
#define FOURBRW (1)
#define ONEN (0x5551)
#define FOURN (0x4A11)
#define LF (0x0D)
#define ENDF (0x0A)
#define INTINT (0X08)
#define STELEV (11)
#define CLENGTH (11)
#define CLENTWO (22)
#define CLENTHR (33)
#define LENSAFE (28)
#define APOSTR (0x27)
#define IPLEN (16)
#define IPLENO (15)
#define IPLENT (14)
#define TENTHIR (1000)
#define TENSECO (100)
#define TEN (10)
#define EIGHSEC (160)
#define IPCLEN (19)
#define ninsper (29000)
#define ninspel (29000)
#define defaulspeedR (12000)
#define defaulspeedL (16000)
#define MHTHOUS (900000)
#define MTTHOUS (90000)
#define MTHOUS (9000)
#define MHUND (900)
#define MTEN (90)
#define TTHOUS (10000)
#define HTHOUS (100000)
#define DEFRB (1400)
#define DEFLB (1800)
#define SOCKLEN (19)
#define OHSEC (30)
#define FIVSEC (100)

//timers
#define TA0CCR0_INTERVAL (25000) // 8,000,000 / 2 / 8 / (1 / 50msec)
#define TA0CCR1_INTERVAL (25000) // 8,000,000 / 2 / 8 / (1 / 50msec)
#define TA0CCR2_INTERVAL (50)  // 8,000,000 / 2 / 8 / (1 / 1msec)
#define TIMEOVERFLOW (14)
#define TIMEA1 (2)
#define TIMEA2 (4)
#define ONESEC (20)
#define DEBOUNCET (30)
#define HALFSEC (10)
#define TWOSEC (40)
#define THRESEC (60)
#define WHEEL_PERIOD (30000)
#define WHEEL_OFF (0)
#define LEFT_REVERSE_SPEED (TB0CCR3)
#define LEFT_FORWARD_SPEED (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)

//Shapes.c/switches.c 
#define NO_SHAPE        (0)
#define CIRCLE          (1)
#define TRIANGLE        (2)
#define FIG_EIGHT       (3)
#define BUTT_OFFSET     (50)    
#define TRI_LENGTH      (1)
#define TRI_TURN        (0)
#define TRI_LENGTH_DIST (70)
#define TRI_TURN_DIST   (95)
#define TRI_TURN_NUMB   (5)
#define TIME_RESET      (99)
#define FIG_ODURATION   (4)
#define FIG_DURATION    (4)
#define FIG_TDURATION   (15)
#define C_DURATION (10)
#define C_L_DUR  (8)
#define C_L_DUR_OFF (1)
#define F_R_ON (15)
#define F_R_OFF (14)
#define F_L_ON  (17)
#define F_L_OFF (16)
#define F_R_DUR (17)
#define F_L_DUR (17)
#define F_DUR   (76)

//---

//Port 3 case statement
#define USE_L_REVERSE (0x00)
#define USE_SMCLK (0x01)

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)
// Port 1 Pins
#define RED_LED         (0x01)      // RED LED – P1_0_LED1
#define GRN_LED         (0x02)      // GREEN LED – P1_1_LED2
#define V_THUMB         (0x04)      // ADC for Thumb Wheel
#define TEST_PROBE      (0x08)      // GP I/O Pin to use to check code operation
#define V_DETECT_R      (0x10)      // ADC for Right Detector
#define V_DETECT_L      (0x20)      // ADC for Left Detector
#define SD_UCB0SIMO     (0x40)      // SPI mode - slave in/master out for SD Card
#define SD_UCB0SOMI     (0x80)      // SPI mode - slave out/master in for SD Card
// Port 2 Pins
#define BCLUART_TXD       (0x01)      // BCLUART_TXD
#define BCLUART_RXD       (0x02)      // BCLUART_RXD
#define SD_SPICLK         (0x04)      // SD_SPICLK
#define P2_3_UNUSED       (0x08)      // UNUSED
#define P2_4_UNUSED       (0x10)      // UNUSED
#define UCA1TXD           (0x20)      // UCA1TXD
#define UCA1RXD           (0x40)      // UCA1RXD
#define P2_7_UNUSED       (0x80)      // UNUSED
// Port 3 Pins
#define IOT_RESET       (0x01) // RESET
#define IOT_STA_MINIAP  (0x02) // IOT_STA_MINIAP
#define IOT_LINK        (0x04) // IOT_LINK
#define IOT_WAKEUP      (0x08) // IOT_WAKEUP
#define L_REVERSE       (0x10) // Left Reverse
#define L_FORWARD       (0x20) // Left Forward
#define R_REVERSE       (0x40) // Right Reverse
#define R_FORWARD       (0x80) // Right Forward
// Port 4 Pins
#define SD_CS        (0x01)      // SD_CS
#define J4_31        (0x02)      // J4_31
#define J4_32        (0x04)      // J4_32
#define J4_33        (0x08)      // J4_33
#define UCB1_CS_LCD  (0x10)      // UCB1_CS_LCD
#define P4_5_UNUSED  (0x20)      // UNUSED
#define P4_6_UNUSED  (0x40)      // UNUSED
#define J3_29        (0x80)      // J3_29
// Port 5 Pins
#define SPI_UCB1SIMO    (0x01) // UCB1SIMO
#define SPI_UCB1SOMI    (0x02) // UCB1SOMI
#define SPI_UCB1CLK     (0x04) // SPI mode - clock output—UCB1CLK
#define RESET_LCD       (0x08) // LCD Reset
#define P5_4_UNUSED     (0x10) // UNUSED
#define BUTTON2         (0x20) // Button 2
#define BUTTON1         (0x40) // Button 1
#define LCD_BACKLITE    (0x80) // LCD Backlite
// Port 6 Pins
#define UCA3TXD         (0x01)      // UCA3TXD
#define UCA3RXD         (0x02)      // UCA3RXD
#define J1_5            (0x04)      // J1_5
#define MAG_INT         (0x08)      // MAG_INT
#define P6_4_UNUSED     (0x10)      // UNUSED
#define P6_5_UNUSED     (0x20)      // UNUSED
#define P6_6_UNUSED     (0x40)      // UNUSED
#define P6_7_UNUSED     (0x80)      // UNUSED
// Port 7 Pins
#define I2CSDA            (0x01)      // I2CSDA
#define I2CSCL            (0x02)      // ISCSCL
#define SD_DETECT         (0x04)      // SD_DETECT
#define J4_36             (0x08)      // J4_36
#define P7_4_UNUSED       (0x10)      // UNUSED
#define P7_5_UNUSED       (0x20)      // UNUSED
#define P7_6_UNUSED       (0x40)      // UNUSED
#define P7_7_UNUSED       (0x80)      // UNUSED
// Port 8 Pins
#define IR_LED    (0x01)      // IR_LED
#define OPT_INT   (0x02)      // OPT_INT
#define TMP_INT   (0x04)      // TMP_INT
#define INT2      (0x08)      // INT2
// Port J Pins
#define PJ_0_UNUSED       (0x01)      // UNUSED
#define PJ_1_UNUSED       (0x02)      // UNUSED
#define PJ_2_UNUSED       (0x04)      // UNUSED
#define PJ_3_UNUSED       (0x08)      // UNUSED
#define LFXIN             (0x10)      // LFXIN
#define LFXOUT            (0x20)      // LFXOUT
#define HFXIN             (0x40)      // HFXIN
#define HFXOUT            (0x80)      // HFXOUT