#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "definitions.h"
uint8_t replay;

void SysTick_Delay_1mS(unsigned long delay){ // no of 1 mS
  unsigned long i;
  for(i=0; i<delay; i++){
      while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
      }
  }
}

// Transmitting 8 bit data and receiving 8 bit data

uint8_t SPI2_Transmit(uint8_t data) {

    UART0_Println("Inside SPI2_Transmit");
    UART0_Println("Waiting for FIFO empty");

    while ((SSI2_SR_R & SSI_SR_TNF) == 0) UART0_Println(".");   // Wait until there's space in FIFO
    SSI2_DR_R = data;                       // Send data

    UART0_Println("Waiting for FIFO data");

    while ((SSI2_SR_R & SSI_SR_RNE) == 0) UART0_Println(".");  // Wait until there's data to read

    UART0_Println("Exiting SPI2_Transmit");

    return SSI2_DR_R;                       // Read and return data

}


uint8_t SD_Send(uint8_t command, uint32_t argument, uint8_t crc){

    UART0_Println("Inside SD sent, cmd sending");

    //uint8_t replay;
    UART0_Println("Sending cmd");
    SPI2_Transmit(command | 0x40);          // 0x40 OR operation to ensure that first 2 bit (MSB) is 01
    UART0_Println("Sending arg1");
    SPI2_Transmit((argument >> 24)& 0xff);  // right shift and bit wise AND operation to ensure result is lower 8 bit
    UART0_Println("Sending arg2");
    SPI2_Transmit((argument >> 16)& 0xff);
    UART0_Println("Sending arg3");
    SPI2_Transmit((argument >> 8)& 0xff);
    UART0_Println("Sending arg4");
    SPI2_Transmit(argument & 0xff);
    UART0_Println("Sending crc");
    SPI2_Transmit(crc | 0x01);              // 0x01 OR  operation is to ensure that last bit (LSB) is 1
    UART0_Println("waiting rply, sending ff");
    replay = SPI2_Transmit(0xff);

    UART0_Println("listening");

    while(replay == 0xff) {
        UART0_Println("inside sd send rply while loop, sending ff");
        replay = SPI2_Transmit(0xff);
        UART0_Println(".");
    }

    UART0_Println("Exiting SD sent, cmd send finished");

    return replay;

}

// It is sending the starting 75 pulses to ensure that SD card is set to SPI mode
void SD_Initial_Clock_Pulses(void) {

    volatile int ii;
    int i;
    for (ii = 0; ii < 100000; ii++);                      // Power on delay (optional, can help with SD card stability)
    for (i = 0; i < 10; i++) {                            // Send 80 clock pulses to wake up the card (idle state)
      SPI2_Transmit(0xff);                                // Dummy byte to generate clock pulses
    }

}

////// ********************************************////////**************************************************************//////

// Functions for serial print using UART0

// Function to send a single character over UART0
void UART0_WriteChar(char c) {
    // Wait until the TX FIFO is not full
    while ((UART0_FR_R & UART_FR_TXFF) != 0) {}
    UART0_DR_R = c;  // Write character to the UART0 data register
}

// Function to send a string over UART0
void UART0_WriteString(const char* str) {
    while (*str) {
        UART0_WriteChar(*str);
        str++;
    }
}

// Function to send a string with a newline (simulating println)
void UART0_Println(const char* str) {
    UART0_WriteString(str);
    UART0_WriteString("\r\n");
}





/*// Receiving 8 bit data by sending 0xff value

uint8_t SPI_Receive(void) {

    while ((SSI2_SR_R & SSI_SR_TNF) == 0) GPIO_PORTF_DATA_R |= RED_LED;   // Wait until there's space in FIFO
    SSI2_DR_R = 0xff;                       // Send data
    GPIO_PORTF_DATA_R &= ~RED_LED;

    while ((SSI2_SR_R & SSI_SR_RNE) == 0) GPIO_PORTF_DATA_R |= GREEN_LED;  // Wait until there's data to read
    GPIO_PORTF_DATA_R &= ~GREEN_LED;
    return SSI2_DR_R;                       // Read and return data

}-*/
