
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

