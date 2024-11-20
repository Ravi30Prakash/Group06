#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "definitions.h"

void GPIO_PortA_Initialisation(void){

    //volatile unsigned long delay;
    // SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;// Enable clock for Port A
    //SYSCTL_RCGC2_R |= 0x00000001;         // activate clock for Port A
    //delay = SYSCTL_RCGC2_R;               // allow time for clock to stabilize
    GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port A
    GPIO_PORTA_CR_R = 0x3c;                 // Commit changes,1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_DEN_R = 0x3c;                // Digital function enable, 1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_DIR_R = 0x2c;                // Set output/input, 1-output (PA7-PA0 = 00101100)
    GPIO_PORTA_PUR_R = 0x0c;                // Enable pull-up resistor, 1-enable (PA7-PA0 = 00001100)
    GPIO_PORTA_DATA_R = 0x00;               // Reset the data register (PA7-PA0 = 00000000)

}

void GPIO_PortB_Initialisation(void){

    //volatile unsigned long delay;
    // SPI(2) pin connections: PB4:-SCK(2) PB5:-CS(2) PB6:-MISO(2) PB7:-MOSI(2)

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;// Enable clock for Port B
    //SYSCTL_RCGC2_R |= 0x00000010;         // activate clock for Port B
    //delay = SYSCTL_RCGC2_R;               // allow time for clock to stabilize
    GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port B
    GPIO_PORTB_CR_R = 0xf0;                 // Commit changes,1-enable (PB7-PB0 = 11110000)
    GPIO_PORTB_DEN_R = 0xf0;                // Digital function enable, 1-enable (PB7-PB0 =11110000)
    GPIO_PORTB_DIR_R = 0xb0;                // Set output/input, 1-output (PB7-PB0 = 10110000)
    GPIO_PORTB_PUR_R = 0x30;                // Enable pull-up resistor, 1-enable (PB7-PB0 = 00110000)
    GPIO_PORTB_DATA_R = 0x00;               // Reset the data register (PB7-PB0 = 00000000)

}

void GPIO_PortF_Initialisation(void){

    // PORTF, PF7-PF0, PF4-SW1, PF3-green, PF2-blue, PF1-red, PF0-SW2

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;// Enable clock for Port F
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port F
    GPIO_PORTF_CR_R = 0x1f;                 // Commit changes,1-enable (PF7-PF0 = 00011111)
    GPIO_PORTF_DEN_R = 0x1f;                // Digital function enable, 1-enable (PF7-PF0 = 00011111)
    GPIO_PORTF_DIR_R = 0x0e;                // Set output/input, 1-output (PF7-PF0 = 00001110)
    GPIO_PORTF_PUR_R = 0x11;                // Enable pull-up resistor, 1-enable (PF7-PF0 = 00010001)
    GPIO_PORTF_DATA_R = 0x00;               // Reset the data register (PF7-PF0 = 00000000)

}

// SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)

void SPI_0_Initialisation(void){

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0;  // Enable clock for SPI(0) module
    GPIO_PORTA_AFSEL_R = 0x3c;              // Alternate function,1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xff0000ff) | 0x00222200; // Set PA2, PA3, PA4 and PA5 to SPI (0)
    SSI0_CR1_R = 0x00;                      // SPI control, disable fully
    SSI0_CC_R = 0x00;                       // Clock configuration - system clock
    SSI0_CPSR_R = 0x02;                     // Clock divisor pre-scalar, 2
    SSI0_CR0_R = (0x07 << 8) | (0x02 << 6); // 8-bit data, Freescale mode
    //SSI0_CR0_R = 0x07c7;                    // SPI settings, 16 bit-all zero(reserved), 8 bit-0x07(serial clock rate 1Mbps), SPH-1, SPO-1, 2 bit-0(mode freescale), 4 bit-7(8bit data)
    SSI0_CR1_R = 0x02;                      // SPI control, 00010 - endTxInterrupt, reserved, MasterOperation, SPIEnable, LoopbackDisable
    //modify();

}

// SPI(2) pin connections: PB4:-SCK(2) PB5:-CS(2) PB6:-MISO(2) PB7:-MOSI(2)

void SPI_2_Initialisation(void){

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R2;  // Enable clock for SPI(2) module
    GPIO_PORTB_AFSEL_R = 0xf0;              // Alternate function,1-enable (PB7-PB0 = 11110000)
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0000ffff) | 0x22220000; // Set PB4, PB5, PB6 and PB7 to SPI (2)
    SSI2_CR1_R = 0x00;                      // SPI control, disable fully
    SSI2_CC_R = 0x00;                       // Clock configuration - system clock
    SSI2_CPSR_R = 0x02;                     // Clock divisor pre-scalar, 2
    SSI2_CR0_R = (0x07 << 8) | (0x02 << 6); // 8-bit data, Freescale mode
    //SSI2_CR0_R = 0x07c7;                   // SPI settings, 16 bit-all zero(reserved), 8 bit-0x07(serial clock rate 1Mbps), SPH-1, SPO-1, 2 bit-0(mode freescale), 4 bit-7(8bit data)
    SSI2_CR1_R = 0x02;                      // SPI control, 00010 - endTxInterrupt, reserved, MasterOperation, SPIEnable, LoopbackDisable
    //modify();

}

