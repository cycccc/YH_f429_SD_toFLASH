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
 * 文件名称: bsp__rs485.c
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

#include "bsp__rs485.h"
 

void rs485_write(UART_HandleTypeDef* huart, GPIO_TypeDef* CS_PORT, uint16_t CS_PIN, uint8_t* pData, uint16_t Size)
{
	//此板子DE线接了光耦，因此DE线逻辑是相反的
	HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_RESET);    //RS485发送
	HAL_UART_Transmit(huart, pData, Size, 0xffff);
	HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_SET);    //RS485接收
}
 
//void rs485_read(UART_HandleTypeDef* huart, GPIO_TypeDef* CS_PORT, uint16_t CS_PIN, uint8_t* pData, uint16_t Size)
//{
//	//此板子DE线接了光耦，因此DE线逻辑是相反的
//	HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_RESET);    //RS485发送
//	HAL_UART_Receive(huart, pData, Size, 0xffff);
//	HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_SET);    //RS485接收
//}
 
/********************************End of File************************************/

