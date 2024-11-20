
// SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)

// ********************************************///////////****************************************************//

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "definitions.h"

// *******************************************////////////***************************************************//

void main(void){

    SysTick_Initialisation();
    GPIO_PortF_Initialisation();
    GPIO_PortF_Interrupt_Initialisation();
    GPIO_PortA_Initialisation();
    //modify();
    SPI_0_Initialisation();

    while(1){

    }

}

// ********************************************///////////****************************************************//

void modify(void){
    GPIO_PORTA_AMSEL_R &= ~0xFC;          // disable analog functionality on PA2,3,4,5
    SSI0_CR1_R&=~SSI_CR1_SSE;             // Disable SSI while configuring it
    SSI0_CR1_R&=~SSI_CR1_MS;              // Set as Master
    SSI0_CC_R|=SSI_CC_CS_M;               // Configure clock source
    SSI0_CC_R|=SSI_CC_CS_SYSPLL;          // Configure clock source
    SSI0_CC_R|=SSI_CPSR_CPSDVSR_M;        // Configure prescale divisor
    SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+10; // must be even number
    SSI0_CR0_R |=0x0300;
    SSI0_CR0_R &= ~(SSI_CR0_SPH | SSI_CR0_SPO);
    SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
                                            // DSS = 8-bit data
    SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
    SSI0_CR1_R|=SSI_CR1_SSE;          // 3)Enable SSI
}

void SD_Card_Present(void) {

    GPIO_PORTF_DATA_R |= BLUE_LED;
    SysTick_Delay_1mS(50);

    // Pull CS low to select the SD card
    GPIO_PORTA_DATA_R &= ~SD_CS_Pin;  // Activate the chip select

    // Send CMD0 (GO_IDLE_STATE) to check for presence
    SPI_Transmit(0x40);               // CMD0 with start bit
    SPI_Transmit(0x00);               // Argument (0)
    SPI_Transmit(0x00);               // Argument (0)
    SPI_Transmit(0x00);               // Argument (0)
    SPI_Transmit(0x00);               // Argument (0)
    SPI_Transmit(0x95);               // CRC for CMD0 (valid CRC)

    // Wait for response (R1 format)
    uint8_t response = SPI_Receive();         // Read response

    // Release CS
    GPIO_PORTA_DATA_R |= SD_CS_Pin;      // Deactivate the chip select
    GPIO_PORTF_DATA_R &= ~BLUE_LED;

    // Check if the response is valid (R1 response is 0)
    if (response == 0x00) {                               // Card reset success - (0x00)
        GPIO_PORTF_DATA_R |= BLUE_LED;                    // Turn on LED if reset was successful
    } else if (response == 0x01){                         // Card reset fail - (0x01)
        GPIO_PORTF_DATA_R &= ~BLUE_LED;                   // Turn off LED if failed
    }
}
