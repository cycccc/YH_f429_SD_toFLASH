
/*************** RAIO Technology Inc. ***************
* file		: RA8889_MCU_IF.h
* author		: RAIO Application Team
* version		: V1.0
* date		: 2014/03/17
* brief		:
****************************************************/


#ifndef __RA8889_MCU_IF_H
#define __RA8889_MCU_IF_H

#include <stdlib.h>

#include "UserDef.h"
#include "main.h"



#define Set_D0    GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define Set_D1    GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define Set_D2    GPIO_SetBits(GPIOD, GPIO_Pin_0)
#define Set_D3    GPIO_SetBits(GPIOD, GPIO_Pin_1)
#define Set_D4    GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define Set_D5    GPIO_SetBits(GPIOE, GPIO_Pin_8)
#define Set_D6    GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define Set_D7    GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define Set_D8    GPIO_SetBits(GPIOE, GPIO_Pin_11)
#define Set_D9    GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define Set_D10   GPIO_SetBits(GPIOE, GPIO_Pin_13)
#define Set_D11   GPIO_SetBits(GPIOE, GPIO_Pin_14)
#define Set_D12   GPIO_SetBits(GPIOE, GPIO_Pin_15)
#define Set_D13   GPIO_SetBits(GPIOD, GPIO_Pin_8)
#define Set_D14   GPIO_SetBits(GPIOD, GPIO_Pin_9)
#define Set_D15   GPIO_SetBits(GPIOD, GPIO_Pin_10)



#define Reset_D0    GPIO_ResetBits(GPIOD, GPIO_Pin_14)
#define Reset_D1    GPIO_ResetBits(GPIOD, GPIO_Pin_15)
#define Reset_D2    GPIO_ResetBits(GPIOD, GPIO_Pin_0)
#define Reset_D3    GPIO_ResetBits(GPIOD, GPIO_Pin_1)
#define Reset_D4    GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define Reset_D5    GPIO_ResetBits(GPIOE, GPIO_Pin_8)
#define Reset_D6    GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define Reset_D7    GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define Reset_D8    GPIO_ResetBits(GPIOE, GPIO_Pin_11)
#define Reset_D9    GPIO_ResetBits(GPIOE, GPIO_Pin_12)
#define Reset_D10   GPIO_ResetBits(GPIOE, GPIO_Pin_13)
#define Reset_D11   GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define Reset_D12   GPIO_ResetBits(GPIOE, GPIO_Pin_15)
#define Reset_D13   GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define Reset_D14   GPIO_ResetBits(GPIOD, GPIO_Pin_9)
#define Reset_D15   GPIO_ResetBits(GPIOD, GPIO_Pin_10)



#define Read_D0		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)
#define Read_D1		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)
#define Read_D2		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)
#define Read_D3		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)
#define Read_D4		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define Read_D5		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#define Read_D6		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)
#define Read_D7		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define Read_D8		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)
#define Read_D9		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define Read_D10	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define Read_D11	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)
#define Read_D12	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)
#define Read_D13	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)
#define Read_D14	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)
#define Read_D15	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)


//8080
#ifdef Parallel_8080
/*
要使FSMC_A16地址线为高电平,实质是访问内部HADDR地址的第(16+1)位为1即可,使用0x6000 0000-0X63FF FFFF内的任意地址,作如下运算:
使FSMC A16地址线为高电平: 0X6000 0000 |= (1<<(16+1))=0x6002 0000
*/
#define LCD_BASE0        ((u32)0x60000000UL)//RA8889
/*
要使FSMC_A16地址线为低电平,实质是访问内部HADDR地址的第(16+1)位为0即可,使用0X6000 000-0X63FF FFFF内的任意地址,作如下运算:
使FSMC A16地址线为低电平: 0X6000 0000 &= ~(1<<(16+1)) = 0x6000 0000
*/
#define LCD_BASE1        ((u32)0x60020000UL)//RA8889 

#define LCD_CmdWrite(cmd)	  *(vu16*) (LCD_BASE0)= (cmd);
#define LCD_DataWrite(data)   *(vu16*) (LCD_BASE1)= (data);
#define	LCD_StatusRead()	 *(vu16*) (LCD_BASE0) //if use read  Mcu interface DB0~DB15 needs increase pull high 
#define	LCD_DataRead()   	 *(vu16*) (LCD_BASE1) //if use read  Mcu interface DB0~DB15 needs increase pull high 
#endif

//6800
#ifdef Parallel_6800
#define Set_68RS  GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define	Set_68RW  GPIO_SetBits(GPIOD,GPIO_Pin_5)
#define	Set_68EN  GPIO_SetBits(GPIOD,GPIO_Pin_4)
#define Set_68CS  GPIO_SetBits(GPIOD,GPIO_Pin_7)
#define Reset_68RS	GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define	Reset_68RW	GPIO_ResetBits(GPIOD,GPIO_Pin_5)
#define	Reset_68EN	GPIO_ResetBits(GPIOD,GPIO_Pin_4)
#define Reset_68CS	GPIO_ResetBits(GPIOD,GPIO_Pin_7)
#endif

//SPI3
#ifdef Serial_3
#define Set_SPI3_ZCS      GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define Set_SPI3_SDO   	  GPIO_SetBits(GPIOE, GPIO_Pin_8)
#define Set_SPI3_SCL      GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define Reset_SPI3_ZCS    GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define Reset_SPI3_SDO    GPIO_ResetBits(GPIOE, GPIO_Pin_8)
#define Reset_SPI3_SCL    GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define Read_SPI3_SDO	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#endif


//SPI4
#ifdef Serial_4
#ifdef software_spi
#define Set_SPI4_ZCS 	      GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define Set_SPI4_SDO   	    GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define Set_SPI4_SDA	      GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define Set_SPI4_SCL   	    GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define Reset_SPI4_ZCS      GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define Reset_SPI4_SDO      GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define Reset_SPI4_SDA	    GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define Reset_SPI4_SCL      GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define Read_SPI4_SDO	      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define Read_SPI4_SDA	      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#else

//使用硬件SPI的句柄
typedef struct
{
	SPI_HandleTypeDef hspi;   //使用的spi句柄
	GPIO_TypeDef* cs_port;    //spi片选引脚端口
	uint16_t cs_pin;          //spi片选引脚号
	GPIO_TypeDef* cmdORdata_port;  //spi命令/数据选择引脚端口
	uint16_t cmdORdata_pin;   //spi命令/数据选择引脚号
} RA8889_SPI4_typedef;
#endif   //software_spi
#endif   //Serial_4

//I2C
#ifdef Serial_I2C
#define Set_I2CA0	    GPIO_SetBits(GPIOD, GPIO_Pin_14)	//I2C I/F: IIC Slave Address A0.
#define Set_I2CA1	    GPIO_SetBits(GPIOD, GPIO_Pin_15)	//I2C I/F: IIC Slave Address A1.
#define Set_I2CA2	    GPIO_SetBits(GPIOD, GPIO_Pin_0)		//I2C I/F: IIC Slave Address A2.
#define Set_I2CA3	    GPIO_SetBits(GPIOD, GPIO_Pin_1)		//I2C I/F: IIC Slave Address A3.
#define Set_I2CA4	    GPIO_SetBits(GPIOE, GPIO_Pin_7)		//I2C I/F: IIC Slave Address A4.
#define Set_I2CA5	    GPIO_SetBits(GPIOE, GPIO_Pin_8)		//I2C I/F: IIC Slave Address A5.
#define Set_I2CSDA 	 	   GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define Set_I2CSCL	 	   GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define Reset_I2CA0	    GPIO_ResetBits(GPIOD, GPIO_Pin_14)	//I2C I/F: IIC Slave Address A0.
#define Reset_I2CA1	    GPIO_ResetBits(GPIOD, GPIO_Pin_15)	//I2C I/F: IIC Slave Address A1.
#define Reset_I2CA2	    GPIO_ResetBits(GPIOD, GPIO_Pin_0)	//I2C I/F: IIC Slave Address A2.
#define Reset_I2CA3	    GPIO_ResetBits(GPIOD, GPIO_Pin_1)	//I2C I/F: IIC Slave Address A3.
#define Reset_I2CA4	    GPIO_ResetBits(GPIOE, GPIO_Pin_7)	//I2C I/F: IIC Slave Address A4.
#define Reset_I2CA5	    GPIO_ResetBits(GPIOE, GPIO_Pin_8)	//I2C I/F: IIC Slave Address A5.
#define Reset_I2CSDA 	    GPIO_ResetBits(GPIOE, GPIO_Pin_9)
#define Reset_I2CSCL	    GPIO_ResetBits(GPIOE, GPIO_Pin_10)
#define Read_I2CSDA  	    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)

#endif





//6800
#ifdef Parallel_6800
void Parallel_6800_ini(void);
void LCD_CmdWrite(unsigned int Command);
unsigned int LCD_StatusRead(void);
void LCD_DataWrite(unsigned int Data);
unsigned int LCD_DataRead(void);
#endif

//Serial_3
#ifdef Serial_3
void LCD_CmdWrite(unsigned char Command);
unsigned char LCD_StatusRead(void);
void LCD_DataWrite(unsigned char Data);
unsigned char LCD_DataRead(void);
void SPI3_Delay(void);
void SPI3_Init(void);
void SPI3_Write(unsigned char dat);
unsigned char SPI3_Read();
#endif

//Serial_4
#ifdef Serial_4
#ifdef software_spi
void SPI4_Delay(void);
void SPI4_Init(void);
void SPI4_Write(unsigned char dat);
unsigned char SPI4_Read(void);
void LCD_CmdWrite(unsigned char Command);
unsigned char LCD_StatusRead(void);
void LCD_DataWrite(unsigned char Data);
unsigned char LCD_DataRead(void);
#else
void SPI4_Init_hardware(SPI_HandleTypeDef hspi, GPIO_TypeDef* cs_port, uint16_t cs_pin, GPIO_TypeDef* cmdORdata_port, uint16_t cmdORdata_pin);
void SPI4_Write(uint8_t dat);
uint8_t SPI4_Read(void);
void LCD_CmdWrite(uint8_t Command);
uint8_t LCD_StatusRead(void);
void LCD_DataWrite(uint8_t Data);
uint8_t LCD_DataRead(void);
#endif //software_spi
#endif


// I2C
#ifdef Serial_I2C
void I2C_Stop(void);
void I2C_PutAck(unsigned char ack);
unsigned char I2C_GetAck(void);
unsigned char I2C_Read(void);
void I2C_Write(unsigned char dat);
void I2C_Start(void);
void I2C_Initial(void);
void I2C_Delay(void);
void LCD_CmdWrite(unsigned char Command);
unsigned char LCD_StatusRead(void);
void LCD_DataWrite(unsigned char Data);
unsigned char LCD_DataRead(void);
#endif

void GPIO_Configuration_8080(void);
void GPIO_Configuration_6800_SP3_SP4_I2C(void);




#endif /*__RA8889_MCU_IF_H*/
