//red led: stuck in tx while loop
//green led: stuck in rx while loop
//bue led: sd card status and working branch indication

// SPI(0) pin connections: PA2:-SCK(0) PA3:-CS(0) PA4:-MISO(0) PA5:-MOSI(0)
// SPI(2) pin connections: PB4:-SCK(2) PB5:-CS(2) PB6:-MISO(2) PB7:-MOSI(2)

// ********************************************///////////****************************************************//

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "definitions.h"
uint8_t response;
extern bool button_Send;

// *******************************************////////////***************************************************//

void main(void){

    SysTick_Initialisation();
    GPIO_PortF_Initialisation();
    GPIO_PortF_Interrupt_Initialisation();
    GPIO_PortA_Initialisation();
    GPIO_PortB_Initialisation();
    SPI_2_Initialisation();
    UART0_Initialisation();
    UART0_Println("Hello");
    UART0_Println("Initialisation done");

    while(1){

        if(button_Send) {
            UART0_Println("SD sent button pressed");
            SD_Card_Present();
            button_Send = 0;                    // To disable the flag for start SD data sending
            UART0_Println("exiting SD sent button pressed loop");
        }

    }

}

// ********************************************///////////****************************************************//

void SD_Card_Present(void) {

    //uint8_t response;

    SD_Initial_Clock_Pulses();

    UART0_Println("**************************************Sending CMD0");

    response = SD_Send(CMD0, Zero_Arg, dummy_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x01) UART0_Println("CMD0 Success");
    else {
        UART0_Println("CMD0 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }

 /*   UART0_Println("*****************************************Sending CMD8");

    response = SD_Send(CMD8, CMD8_Arg, CMD8_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x01) UART0_Println("CMD8 Success");
    else {
        UART0_Println("CMD8 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }  */

    UART0_Println("******************************************Sending CMD0");

    response = SD_Send(CMD0, Zero_Arg, dummy_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x01) UART0_Println("CMD0 Success");
    else {
        UART0_Println("CMD0 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }

    UART0_Println("****************************************Sending CMD55");

    response = SD_Send(CMD55, Zero_Arg, dummy_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x00) UART0_Println("CMD55 Success");
    else {
        UART0_Println("CMD55 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }

    UART0_Println("****************************************Sending CMD55");

    response = SD_Send(CMD55, Zero_Arg, dummy_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x00) UART0_Println("CMD55 Success");
    else {
        UART0_Println("CMD55 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }


    UART0_Println("***************************************Sending CMD41");

    response = SD_Send(CMD41, CMD41_Arg, dummy_CRC);
    SysTick_Delay_1mS(100);

    if(response == 0x00) UART0_Println("CMD41 Success");
    else {
        UART0_Println("CMD41 fail, 5s wait");
        SysTick_Delay_1mS(5000);
    }

}

