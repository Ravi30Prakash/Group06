#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "definitions.h"

void SysTick_Delay_1mS(unsigned long delay){ // no of 1 mS
  unsigned long i;
  for(i=0; i<delay; i++){
      while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
      }
  }
}

void SPI_Transmit(uint8_t data) {

    while ((SSI0_SR_R & SSI_SR_TNF) == 0) GPIO_PORTF_DATA_R |= RED_LED;   // Wait until there's space in FIFO
    SSI0_DR_R = data;                       // Send data
    GPIO_PORTF_DATA_R &= ~RED_LED;
}

uint8_t SPI_Receive(void) {

    while ((SSI0_SR_R & SSI_SR_RNE) == 0) GPIO_PORTF_DATA_R |= GREEN_LED;  // Wait until there's data to read
    GPIO_PORTF_DATA_R &= ~GREEN_LED;
    return SSI0_DR_R;                       // Read and return data

}
