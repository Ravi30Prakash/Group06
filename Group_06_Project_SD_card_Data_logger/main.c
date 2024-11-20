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
uint8_t ocr[4];            // The OCR register value

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
            SD_Card_Initialisation();
            button_Send = 0;                    // To disable the flag for start SD data sending
            UART0_Println("exiting SD sent button pressed loop");
        }

    }

}

// ********************************************///////////****************************************************//

bool SD_Card_Initialisation(void){

    UART0_Println("SD_card_init... Starting...");
    UART0_Println("Initial clk pulse sequence starting...");
    SD_Initial_Clock_Pulses();
    UART0_Println("80 clk pulses send");

    UART0_Println("Sending CMD0..........");
    if(SD_Send(CMD0, Zero_Arg, dummy_CRC) == 1){

        UART0_Println("CMD0 Success!");
        UART0_Println("Sending CMD8..........");
        SysTick_Delay_1mS(10);

        if(SD_Send(CMD8, CMD8_Arg, CMD8_CRC) == 1){

            UART0_Println("CMD8 Success!");

            int i;
            for(i=0; i<4; i++){                                    //  Reading OCR register value
                ocr[i]=SPI2_Transmit(0xff);
            }

            UART0_Println("Sending CMD55..........");
            SysTick_Delay_1mS(10);

            if(SD_Send(CMD55, Zero_Arg, dummy_CRC) <= 1){

                UART0_Println("CMD55 Success!");
                UART0_Println("Sending CMD41..........");
                SysTick_Delay_1mS(100);

                response = SD_Send(CMD41, CMD41_Arg, 0x77);
                if(response == 0){

                    UART0_Println("CMD41 Success!");
                    return 1;
                }
                else {
                    UART0_Println("CMD41 failed");
                    return 0;
                }

            }
            else {
                UART0_Println("CMD55 failed");
                return 0;
            }

        }
        else {
            UART0_Println("CMD8 failed");
            return 0;
        }

    }
    else {
        UART0_Println("CMD0 failed");
        return 0;
    }

}

