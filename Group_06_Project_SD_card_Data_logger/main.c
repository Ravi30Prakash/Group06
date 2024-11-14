#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

// Define LED pins
#define RED_LED    (1U << 1) // PF1
#define BLUE_LED   (1U << 2) // PF2
#define GREEN_LED  (1U << 3) // PF3

// SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)

//Interrupt Handlers

void GPIO_PortF_Interrupt_Handler(void)
{
    if(GPIO_PORTF_MIS_R == 0x10){           // Interrupt from SW1
        GPIO_PORTF_DATA_R ^= GREEN_LED;     // Toggle data in PF1 (green led)
    }

    if(GPIO_PORTF_MIS_R == 0x01){           // Interrupt from SW2
        GPIO_PORTF_DATA_R ^= RED_LED;       // Toggle data in PF1 (red led)
    }

    GPIO_PORTF_ICR_R = 0x11;                // Interrupt clear, 1-clear all prior interrupts (PF7-PF0 = 00010001)
}

// Other functions

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

void GPIO_PortF_Interrupt_Initialisation(void){

     // Setting PORTF interrupt registers
     GPIO_PORTF_IS_R = 0x00;                // Interrupt sense, 1-level, 0-edge (PF7-PF0 = 00000000)
     GPIO_PORTF_IBE_R = 0x00;               // Interrupt both edge, 1-both edge, 0-single edge (PF7-PF0 = 00000000)
     GPIO_PORTF_IEV_R = 0x00;               // Interrupt event, 0-falling edge, 1-falling edge (PF7-PF0 = 00000000)
     GPIO_PORTF_ICR_R = 0xff;               // Interrupt clear, 1-clear all prior interrupts (PF7-PF0 = 11111111)
     GPIO_PORTF_IM_R = 0x11;                // Interrupt mask, 1-Enable interrupt (PF7-PF0 = 00010001)

     NVIC_PRI7_R &= 0xFF3FFFFF;             // Prioritize and enable interrupts in NVIC

     // Enable the GPIO Port F interrupt in the NVIC
     NVIC_EN0_R = 0x40000000;               // Port F is interrupt 23 in the NVIC port is in 31st position

     //__asm("    cpsie i");                // Global interrupt enable

}

void GPIO_PortA_Initialisation(void){

    // SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;// Enable clock for Port A
    GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port A
    GPIO_PORTA_CR_R = 0x3c;                 // Commit changes,1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_DEN_R = 0x3c;                // Digital function enable, 1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_DIR_R = 0x2c;                // Set output/input, 1-output (PA7-PA0 = 00101100)
    GPIO_PORTA_PUR_R = 0x0c;                // Enable pull-up resistor, 1-enable (PA7-PA0 = 00001100)
    GPIO_PORTA_DATA_R = 0x00;               // Reset the data register (PA7-PA0 = 00000000)

}

void SPI_0_Initialisation(void){

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0;  // Enable clock for SPI(0) module
    GPIO_PORTA_AFSEL_R = 0x3c;              // Alternate function,1-enable (PA7-PA0 = 00111100)
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xff0000ff) | 0x00222200; // Set PA2, PA3, PA4 and PA5 to SPI (0)
    SSI0_CR1_R = 0x00;                      // SPI control, disable fully
    SSI0_CC_R = 0x00;                       // Clock configuration - system clock
    SSI0_CPSR_R = 0x02;                     // Clock divisor pre-scalar, 2
    SSI0_CR0_R = 0x07c7;                    // SPI settings, 16 bit-all zero(reserved), 8 bit-0x07(serial clock rate 1Mbps), SPH-1, SPO-1, 2 bit-0(mode freescale), 4 bit-7(8bit data)
    SSI0_CR1_R = 0x02;                      // SPI control, 00010 - endTxInterrupt, reserved, MasterOperation, SPIEnable, LoopbackDisable

}

void main(void){

    GPIO_PortF_Initialisation();
    GPIO_PortF_Interrupt_Initialisation();
    GPIO_PortA_Initialisation();
    SPI_0_Initialisation();

    while(1){

    }

}