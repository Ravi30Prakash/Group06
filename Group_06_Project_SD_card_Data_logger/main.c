
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

bool switchEnable = 0;
int option = 0;

<<<<<<< HEAD

uint8_t response;
extern bool button_Send;
uint8_t ocr[4];            // The OCR register value
=======
>>>>>>> 3263ac3bf4287ef386ed86c55f6296dfd5466fac

// *******************************************////////////***************************************************//

void main(void){

    SysTick_Initialisation();
    GPIO_PortF_Initialisation();
    GPIO_PortF_Interrupt_Initialisation();
    GPIO_PortA_Initialisation();
    //modify();
    GPIO_PortB_Initialisation();
    SPI_2_Initialisation();
    UART0_Initialisation();
    UART0_Println("Hello");
    UART0_Println("Hardware Initialisation done");
    intia_Status = SD_Card_Initialisation();
    if(intia_Status == 1 && SD_Card_OCR_data()){
        SD_Read_Sector(0);
        UART0_Println("SD initialisation done");
    }
    else UART0_Println("SD initialisation failed");


        while(1){

        if(switch_1){

            SysTick_Delay_1mS(100);
            option = option + 1;
            if(option > 3) option = 0;
            switch_1 = 0;
            switch_2 = 0;
        }

        // Showing LED indication for the menu
        switch(option){
        case 1:

            GPIO_PORTF_DATA_R |= BLUE_LED;
            GPIO_PORTF_DATA_R &= ~GREEN_LED;
            GPIO_PORTF_DATA_R &= ~RED_LED;
            break;
        case 2:

            GPIO_PORTF_DATA_R |= GREEN_LED;
            GPIO_PORTF_DATA_R &= ~BLUE_LED;
            GPIO_PORTF_DATA_R &= ~RED_LED;
            break;
        case 3:

            GPIO_PORTF_DATA_R |= RED_LED;
            GPIO_PORTF_DATA_R &= ~GREEN_LED;
            GPIO_PORTF_DATA_R &= ~BLUE_LED;
            break;

        default:

            GPIO_PORTF_DATA_R &= ~RED_LED;
            GPIO_PORTF_DATA_R &= ~GREEN_LED;
            GPIO_PORTF_DATA_R &= ~BLUE_LED;
            break;
        }

        if (switch_2){

            SysTick_Delay_1mS(100);
            switchEnable = 1;
            switch_2 = 0;
            switch_1 = 0;
        }

        if(switchEnable){

            switch(option){
            case 1:

                UART0_Println("Entering into SD Sector Read section.....................................");
                SD_Read_Sector(10);
                option = 0;
                switchEnable = 0;
                switch_2 = 0;
                switch_1 = 0;
                break;

            case 2:

                UART0_Println("Entering into SD Sector Write section....................................");
                SD_Write_Block(10, 0);                   // sector number and clear flag value (0- write data, 1- clear data)
                option = 0;
                switchEnable = 0;
                switch_2 = 0;
                switch_1 = 0;
                break;

            case 3:

                UART0_Println("Entering into SD clear section...........................................");
                SD_Write_Block(10, 1);                   // sector number and clear flag value (0- write data, 1- clear data)
                option = 0;
                switchEnable = 0;
                switch_2 = 0;
                switch_1 = 0;
                break;

            default:
                break;

            }
        }

    }

}

// ********************************************///////////****************************************************//

<<<<<<< HEAD
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

=======
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
>>>>>>> 3263ac3bf4287ef386ed86c55f6296dfd5466fac
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
