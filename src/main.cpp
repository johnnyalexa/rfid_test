//Test of cheap 13.56 Mhz RFID-RC522 module from eBay
//This code is based on Martin Olejar's MFRC522 library. Minimal changes
//Adapted for Nucleo STM32 F401RE. Should work on other Nucleos too

//Connect as follows:
//RFID pins        ->  Nucleo header CN5 (Arduino-compatible header)
//----------------------------------------
//RFID IRQ=pin5    ->   Not used. Leave open
//RFID MISO=pin4   ->   Nucleo SPI_MISO=PA_6=D12
//RFID MOSI=pin3   ->   Nucleo SPI_MOSI=PA_7=D11
//RFID SCK=pin2    ->   Nucleo SPI_SCK =PA_5=D13
//RFID SDA=pin1    ->   Nucleo SPI_CS  =PB_6=D10
//RFID RST=pin7    ->   Nucleo         =PA_9=D8
//3.3V and Gnd to the respective pins                              
                              
#include "main.h"
#include "MFRC522.h"

// Nucleo Pin for MFRC522 reset (pick another D pin if you need D8)
/*
#define MF_RESET    PB1 //D8
#define SPI_MOSI	PB3
#define SPI_MISO	PB4
#define SPI_SCK		PB5
#define SPI_CS		PB0
*/

//DigitalOut LedGreen(LED1);

//Serial connection to PC for output
//Serial pc(SERIAL_TX, SERIAL_RX);

//global object
MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);

int main(void) {
	SPI_Init();
	Init_Uart();
	
  printf("starting...\n");
USART_Transmit('0');
  // Init. RC522 Chip
  RfChip.PCD_Init();

  while (true) {
    //LedGreen = 1;

    // Look for new cards
    if ( ! RfChip.PICC_IsNewCardPresent())
    {
      _delay_ms(500);
      continue;
    }

    // Select one of the cards
    if ( ! RfChip.PICC_ReadCardSerial())
    {
      _delay_ms(500);
      continue;
    }

    //LedGreen = 0;

    // Print Card UID
    printf("Card UID: ");
    for (uint8_t i = 0; i < RfChip.uid.size; i++)
    {
      printf(" %X02", RfChip.uid.uidByte[i]);
    }
    printf("\n\r");

    // Print Card type
    uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
    printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
	
	_delay_ms(100);
	RfChip.PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A,0,,RfChip.uid.uidByte);
	
	RfChip.MIFARE_Read();
	
    _delay_ms(1000);
  }
}