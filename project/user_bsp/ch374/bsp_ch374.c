/**
 *******************************Copyright (c)************************************
 *
 *                   (c) Copyright 2021, CY, China, QD.
 *                           All Rights Reserved
 *
 *                           By(南京万福祥电子科技有限公司)
 *                           http://www.njwfx.com
 *
 *----------------------------------文件信息------------------------------------
 * 文件名称: bsp_ch374.c
 * 创建人员: CY
 * 创建日期: 2021-09-18
 * 文档描述:
 *
 *----------------------------------版本信息------------------------------------
 * 版本代号: V1.0
 * 版本说明:
 *          |-1.0
 * 	         |-2021-09-18
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#include "bsp_ch374.h"
#include "ch374hfm.h"

static USB_InitTypeDef husb =
{
    .error = 0,
};
//SPI收发一个字节
uint8_t SPI_TransByte(uint8_t TxData)
{
    uint8_t Rxdata;
    HAL_SPI_TransmitReceive(husb.hspi, &TxData, &Rxdata, 1, 1000);
    return Rxdata;          		    //返回收到的数据
}

//SPI开始
void Spi374Start(uint8_t addr, uint8_t cmd )  /* SPI开始 */
{
    HAL_GPIO_WritePin(husb.usb_cs_port, husb.usb_cs_pin, GPIO_PIN_RESET);    /* SPI片选有效 */
    SPI_TransByte(addr);
    SPI_TransByte(cmd);
}

//SPI结束
void Spi374Stop(void)  /* SPI结束 */
{
    HAL_GPIO_WritePin(husb.usb_cs_port, husb.usb_cs_pin, GPIO_PIN_SET); 	 /* SPI片选无效 */
}


//提供给库调用的函数
uint8_t CH374_READ_REGISTER( uint8_t mAddr )  /* 外部定义的被CH374程序库调用的子程序,从指定寄存器读取数据 */
{
    uint8_t	d;

    if(husb.error != 0) return 0;   //判断USB是否正常工作

    Spi374Start( mAddr, CMD_SPI_374READ );
    d = SPI_TransByte( 0xFF );
    Spi374Stop( );
    return( d );
}

void CH374_WRITE_REGISTER( uint8_t mAddr, uint8_t mData )           /* 外部定义的被CH374程序库调用的子程序,向指定寄存器写入数据 */
{
    Spi374Start( mAddr, CMD_SPI_374WRITE );
    SPI_TransByte( mData );
    Spi374Stop( );
}

void CH374_READ_BLOCK( uint8_t mAddr, uint8_t mLen, uint8_t* mBuf )   /* 外部定义的被CH374程序库调用的子程序,从指定起始地址读出数据块 */
{
    if(husb.error != 0) return;   //判断USB是否正常工作

    Spi374Start( mAddr, CMD_SPI_374READ );
    while ( mLen -- ) *mBuf++ = SPI_TransByte( 0xFF );
    Spi374Stop( );
}

void CH374_WRITE_BLOCK( uint8_t mAddr, uint8_t mLen, uint8_t* mBuf )  /* 外部定义的被CH374程序库调用的子程序,向指定起始地址写入数据块 */
{
    if(husb.error != 0) return;   //判断USB是否正常工作

    Spi374Start( mAddr, CMD_SPI_374WRITE );
    while ( mLen -- ) SPI_TransByte( *mBuf++ );
    Spi374Stop( );
}

uint8_t*	CH374_READ_BLOCK64( uint8_t mAddr, uint8_t* mBuf )         /* 外部定义的被CH374程序库调用的子程序,从双缓冲区读出64字节的数据块,返回当前地址 */
{
    uint8_t	i;

    if(husb.error != 0) return 0;   //判断USB是否正常工作

    Spi374Start( mAddr, CMD_SPI_374READ );
    for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) *mBuf++ = SPI_TransByte( 0xFF );
    Spi374Stop( );
    return( mBuf );
}

uint8_t*	CH374_WRITE_BLOCK64( uint8_t mAddr, uint8_t* mBuf )       /* 外部定义的被CH374程序库调用的子程序,向双缓冲区写入64字节的数据块,返回当前地址 */
{
    uint8_t	i;

    if(husb.error != 0) return 0;   //判断USB是否正常工作

    Spi374Start( mAddr, CMD_SPI_374WRITE );
    for ( i = CH374_BLOCK_SIZE; i != 0; i -- ) SPI_TransByte( *mBuf++ );
    Spi374Stop( );
    return( mBuf );
}

void CH374_WRITE_BLOCK_C( uint8_t mLen, const uint8_t* mBuf )          /* 外部定义的被CH374程序库调用的子程序,向RAM_HOST_TRAN写入常量型数据块 */
{

    if(husb.error != 0) return;   //判断USB是否正常工作

    Spi374Start( RAM_HOST_TRAN, CMD_SPI_374WRITE );
    do
    {
        SPI_TransByte( *mBuf );
        mBuf ++;
    }
    while ( -- mLen );
    Spi374Stop( );
}
//CH374接口初始化
void CH374_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* usb_cs_port, uint16_t usb_cs_pin)
{
    //注册到句柄中
    husb.hspi = hspi;
    husb.usb_cs_port = usb_cs_port;
    husb.usb_cs_pin = usb_cs_pin;

    HAL_Delay(10);

    //读写寄存器测试
    CH374_WRITE_REGISTER( REG_USB_ADDR,  0x5A ) ;

    if( CH374_READ_REGISTER( REG_USB_ADDR ) != 0x5A )
    {
        husb.error = 1;
    }
}



//-------------------//
/* 检查操作状态,如果错误则显示错误代码并停机 */
void	mStopIfError(uint8_t iError )
{
    if ( iError == ERR_SUCCESS ) return;                        /* 操作成功 */

    while ( 1 )
    {
    }
}


/********************************End of File************************************/

