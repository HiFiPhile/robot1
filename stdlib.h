//========================================================================
//Standard fonctions lib for STM8
//
//by Mengsk
//
//HiFiPhile
//
//Aug.2012
//========================================================================

#include "stm8s.h"


#define  SPICS              GPIO_PIN_4
#define  SPISCK             GPIO_PIN_5
#define  SPIDATA            GPIO_PIN_6
#define  SPI_DATA_PORT      GPIOC
#define  SPI_CS_PORT        GPIOC
#define  SPI_Stop           delay(),GPIO_WriteHigh(SPI_CS_PORT, SPICS)
#define  SPI_Start          GPIO_WriteLow(SPI_CS_PORT, SPICS)
//Software SPI
#define  SPI2CS             GPIO_PIN_0
#define  SPI2SCK            GPIO_PIN_1
#define  SPI2DATA           GPIO_PIN_2
#define  SPI2_DATA_PORT     GPIOB
#define  SPI2_CS_PORT       GPIOB
#define  SPI2SCK_SET_1      SPI2_DATA_PORT->ODR |=  SPI2SCK
#define  SPI2SCK_SET_0      SPI2_DATA_PORT->ODR &=~ SPI2SCK
#define  SPI2DATA_SET_1     SPI2_DATA_PORT->ODR |=  SPI2DATA
#define  SPI2DATA_SET_0     SPI2_DATA_PORT->ODR &=~ SPI2DATA
#define  SPI2_Stop          SPI2_CS_PORT->ODR   |=  SPI2CS ,SPI2DATA_SET_0,SPI2SCK_SET_0
#define  SPI2_Start         SPI2_CS_PORT->ODR   &=~ SPI2CS
//Software I2C
#define  I2C2SDA             GPIO_PIN_3
#define  I2C2SCL             GPIO_PIN_4
#define  I2C2_PORT           GPIOB
#define  I2C2SDA_SET_1       I2C2_PORT->ODR |=  I2C2SDA
#define  I2C2SDA_SET_0       I2C2_PORT->ODR &=~ I2C2SDA
#define  I2C2SCL_SET_1       I2C2_PORT->ODR |=  I2C2SCL
#define  I2C2SCL_SET_0       I2C2_PORT->ODR &=~ I2C2SCL
#define  I2C2SDA_INPUT_IN    I2C2_PORT->IDR  &  I2C2SDA


void SPI_Int(void);
void SPI_Tx(unsigned char data);
void SPI2_Int(void);
void SPI2_Tx(unsigned char data);
void I2C2_Int(void);
void I2C2_Start( void );
void I2C2_Stop( void );
void I2C2_Ack( void );
void I2C2_SAck( void );
void I2C2_Nack( void );
void I2C2_Byte_Tx( u8 ByteData );
u8   I2C2_Byte_Rx( void );
void I2C2_Tx( u8 SlvAddr,u8 Address,u8 Data);
u8 I2C2_Rx( u8 SlvAddr,u8 Address );
void I2C2_DIR_Set( unsigned char SDADIR );
void delay(void);
void Delay_MS(u16 m);
void I2C_Int(void);
void EEPROM_Int(void);