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
 * 文件名称: delay.h
 * 创建人员: CY
 * 创建日期: 2021-02-10
 * 文档描述:
 *
 *----------------------------------版本信息------------------------------------
 * 版本代号: V1.0
 * 版本说明:
 *          |-1.0
 * 	         |-2021-02-10
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __DELAY_H_
#define __DELAY_H_

#include "main.h"

//使用SysTick的普通計數模式對延遲進行管理
//包括delay_us,delay_ms  

//2008/12/14
//V1.2
//修正了中斷中調用出現死循環的錯誤
//防止延時不准确,采用do while結构!
	 

//初始化延遲函數
void delay_ms(unsigned short Nms);
void delay_us(unsigned long Nus);
void delay_seconds(unsigned long Nns);

#endif

/********************************End of Head************************************/
