
// Define LED pins

#define RED_LED    (1U << 1) // PF1
#define BLUE_LED   (1U << 2) // PF2
#define GREEN_LED  (1U << 3) // PF3
#define SD_CS_Pin  (1U << 3) // PA3

// SD Command definitions

#define CMD0   0x40  // Reset command (GO_IDLE_STATE)
#define CMD8   0x48  // Send Interface Condition command (CHECK_PATTERN)
#define CMD58  0x49 //0x7a  // Operating Conditions Register, condition about voltage and card type, 32bit replay
#define CMD55  0x77  // App command (prefix for other commands)
#define CMD41  0x69  // SD Card Initialization command (SEND_OP_COND)
#define CMD16  0x50  // Set block length (512 bytes)

// SD arguments

#define Zero_Arg  0x00
#define CMD8_Arg  0x1aa
#define CMD41_Arg 0x40000000   // SDHC/SDXC cards: 0x40000000, SDSC cards: 0x00000000
#define CMD16_Arg 0x200        // common block length 512 bytes

// SD CRC

#define CMD8_CRC  0x87
#define dummy_CRC 0x95


// all functions declaration

// Initialisation functions

void GPIO_PortA_Initialisation(void);
void GPIO_PortB_Initialisation(void);
void GPIO_PortF_Initialisation(void);
void SPI_0_Initialisation(void);
void SPI_2_Initialisation(void);
void UART0_Initialisation(void);

// Interrupt related functions

void SysTick_Initialisation(void);
void GPIO_PortF_Interrupt_Initialisation(void);
void GPIO_PortF_Interrupt_Handler(void);

// Other functions

void SD_Card_Present(void);
void modify(void);
void SysTick_Delay_1mS(unsigned long delay);
uint8_t SPI2_Transmit(uint8_t data);
uint8_t SD_Send(uint8_t command, uint32_t argument, uint8_t crc);
//uint8_t SPI_Receive(void);
void SD_Card_Present(void);
void SD_Initial_Clock_Pulses(void);
void UART0_WriteChar(char c);
void UART0_WriteString(const char* str);
void UART0_Println(const char* str);
