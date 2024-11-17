
// Define LED pins

#define RED_LED    (1U << 1) // PF1
#define BLUE_LED   (1U << 2) // PF2
#define GREEN_LED  (1U << 3) // PF3
#define SD_CS_Pin  (1U << 3) // PA3

// all functions declaration

// Initialisation functions

void GPIO_PortA_Initialisation(void);
void GPIO_PortF_Initialisation(void);
void SPI_0_Initialisation(void);

// Interrupt related functions

void SysTick_Initialisation(void);
void GPIO_PortF_Interrupt_Initialisation(void);
void GPIO_PortF_Interrupt_Handler(void);

// Other functions

void SD_Card_Present(void);
void modify(void);
void SysTick_Delay_1mS(unsigned long delay);
void SPI_Transmit(uint8_t data);
uint8_t SPI_Receive(void);
void SD_Card_Present(void);
