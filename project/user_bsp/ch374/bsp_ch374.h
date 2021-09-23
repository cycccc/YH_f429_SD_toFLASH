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
 * 文件名称: bsp_ch374.h
 * 创建人员: CY
 * 创建日期: 2021-09-18
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-09-18
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_CH374_H_
#define __BSP_CH374_H_

#include "main.h"


//USB硬件结构体
typedef struct 
{
	SPI_HandleTypeDef* hspi;   //usb连接SPI的句柄
	GPIO_TypeDef* usb_cs_port;  //usb 片选的端口
	uint16_t usb_cs_pin;       //usb 片选的引脚
	uint8_t error;             //usb 错误指示  正常 = 0，错误 = 1；
	
} USB_InitTypeDef;




void CH374_Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* usb_cs_port, uint16_t usb_cs_pin);
void	mStopIfError(uint8_t iError );

#endif

/********************************End of Head************************************/

