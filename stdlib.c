//========================================================================
//Standard fonctions lib for STM8
//
//by Mengsk
//
//HiFiPhile
//
//Mai.2012
//========================================================================

#include "stdlib.h"

_Pragma("optimize=none")
void delay(void)
{
    u8 count = 100;
    while(count--);
}

_Pragma("optimize=none")
void Delay_MS(u16 m)
{
    u16 i, j;
    for(i = 0; i < m; i++)
        for(j = 0; j < 125; j++);
}

_Pragma("optimize=medium")

void SPI_Int(void)
{
    /* Enable SPI clock */
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE);
    /* Configure SPI pins*/
    GPIO_Init(SPI_CS_PORT,(GPIO_Pin_TypeDef)(SPICS), GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SPI_DATA_PORT,(GPIO_Pin_TypeDef)(SPISCK | SPIDATA), GPIO_MODE_OUT_PP_LOW_FAST);
    /* Initialize SPI */
    SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_16, SPI_MODE_MASTER,
             SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_1LINE_TX,
             SPI_NSS_SOFT, 0x07);
    SPI_Cmd(ENABLE);
}

void SPI_Tx(u8 data)
{
    /*!< Send the byte */
    SPI_SendData(data);
    while ((SPI->SR & SPI_SR_TXE) == 0)
    {
        /* Wait while the byte is transmitted */
    }
}

void SPI2_Int(void)
{
    /* Configure SPI pins*/
    GPIO_Init(SPI2_CS_PORT,(GPIO_Pin_TypeDef)(SPI2CS), GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SPI2_DATA_PORT,(GPIO_Pin_TypeDef)(SPI2SCK | SPI2DATA), GPIO_MODE_OUT_PP_LOW_SLOW);
}

void SPI2_Tx(u8 data)
{
    u8 i;
    for(i = 0; i < 8; i++)
    {
        SPI2SCK_SET_0;
        if((data & 0x80) == 0x80)           // Check MSB
        {
            SPI2DATA_SET_1;
        }
        else
        {
            SPI2DATA_SET_0;
        }
        SPI2SCK_SET_1;
        data = (data << 1);                     // Shift data
    }
}

void I2C2_Int(void)
{
    /* Configure SPI pins*/
    GPIO_Init(I2C2_PORT,(GPIO_Pin_TypeDef)(I2C2SDA | I2C2SCL), GPIO_MODE_OUT_PP_HIGH_FAST );
    //GPIO_WriteLow(I2C2_PORT,I2C2SCL);
}


void I2C2_Start( void )
{
    I2C2SCL_SET_1;
    delay();
    I2C2SDA_SET_1;
    delay();
    I2C2SDA_SET_0;
    delay();
}

void I2C2_Stop( void )
{
    I2C2SDA_SET_0;
    delay();
    I2C2SCL_SET_1;
    delay();
    I2C2SDA_SET_1;
    delay();
}

void I2C2_Ack( void )
{
    I2C2SCL_SET_0;
    delay();
    I2C2SCL_SET_1;
    delay();
    I2C2SCL_SET_0;
    delay();
}

void I2C2_SAck( void )
{
    I2C2SCL_SET_0;
    delay();
    I2C2SDA_SET_0;
    delay();
    I2C2SCL_SET_1;
    delay();
    I2C2SCL_SET_0;
    delay();
    I2C2SDA_SET_1;
    delay();
}

void I2C2_Nack( void )
{
    I2C2SDA_SET_1;
    delay();
    I2C2SCL_SET_0;
    delay();
    I2C2SCL_SET_1;
    delay();
    I2C2SCL_SET_0;
    delay();
}

void I2C2_DIR_Set( u8 SDADIR )
{
    if(SDADIR == 0)
    {
        GPIO_Init(I2C2_PORT,I2C2SDA , GPIO_MODE_OUT_PP_HIGH_FAST );
    }
    else
    {
        GPIO_Init(I2C2_PORT,I2C2SDA , GPIO_MODE_IN_PU_NO_IT );
    }
}

void I2C2_Byte_Tx( u8 ByteData )
{
    unsigned char count;
    for(count=0; count<8; count++)
    {
        I2C2SCL_SET_0;
        delay();
        if(ByteData&0x80)
        {
            I2C2SDA_SET_1;
        }
        else
        {
            I2C2SDA_SET_0;
        }
        delay();
        I2C2SCL_SET_1;
        delay();
        ByteData<<=1;
    }
}

u8 I2C2_Byte_Rx( void )
{
    unsigned char count,readbyte=0;
    I2C2SCL_SET_0;
    for(count=0; count<8; count++)
    {
        readbyte=readbyte<<1;
        I2C2SCL_SET_1;
        delay();
        if(I2C2SDA_INPUT_IN)
        {
            readbyte=readbyte|0x01;
        }
        else
        {
            readbyte=readbyte&0xfe;
        }
        delay();
        I2C2SCL_SET_0;
        delay();
    }
    I2C2SCL_SET_0;
    return readbyte;
}

void I2C2_Tx( u8 SlvAddr,u8 Address,u8 Data)
{
    I2C2_Start();
    I2C2_Byte_Tx(SlvAddr << 1);
    I2C2_Ack();
    I2C2_Byte_Tx(Address);
    I2C2_Ack();
    I2C2_Byte_Tx(Data);
    I2C2_Ack();
    I2C2_Stop();
}

u8 I2C2_Rx( u8 SlvAddr,u8 Address )
{
    unsigned char readdata;
    I2C2_Start();
    I2C2_Byte_Tx(SlvAddr << 1);
    I2C2_Ack();
    I2C2_Byte_Tx(Address);
    I2C2_Ack();
    I2C2_Start();
    I2C2_Byte_Tx((SlvAddr << 1) + 1);
    I2C2_Ack();
    I2C2_Byte_Tx(Address);
    I2C2_Ack();
    readdata=I2C2_Byte_Rx();
    I2C2_Nack();
    I2C2_Stop();
    return (readdata);
}

void I2C_Int(void)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
    /* I2C configuration */
    /* I2C Peripheral Enable */
    I2C_Cmd( ENABLE);
    /* I2C configuration after enabling it */
    I2C_Init(100000, 0xAA, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
}

void EEPROM_Int(void)
{
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
}