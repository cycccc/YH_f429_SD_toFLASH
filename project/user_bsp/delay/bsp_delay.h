/**
 *******************************Copyright (c)************************************
 *
 *                   (c) Copyright 2021, CY, China, QD.
 *                           All Rights Reserved
 *
 *                           By(�Ͼ�������ӿƼ����޹�˾)
 *                           http://www.njwfx.com
 *
 *----------------------------------�ļ���Ϣ------------------------------------
 * �ļ�����: bsp_delay.h
 * ������Ա: CY
 * ��������: 2021-04-17
 * �ĵ�����: 
 *
 *----------------------------------�汾��Ϣ------------------------------------
 * ʵ��ƽ̨
 *          |--
 * �汾����: V1.0
 * �汾˵��: 
 *          |-1.0
 * 	         |-2021-04-17
 * 	          |-��ʼ�汾
 *------------------------------------------------------------------------------
 */

#ifndef __BSP_DELAY_H_
#define __BSP_DELAY_H_

#include "main.h"

//DWT���ټ��������
#define  DWT_CR      *(volatile uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(volatile uint32_t *)0xE0001004
#define  DEM_CR      *(volatile uint32_t *)0xE000EDFC
#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)

#define delayms(msec)         delayus(msec*1000)

//DWT���ټ�������ʱ����---------//
void dwt_delay_init(void);
void dwt_delay_us(uint32_t us);
//TIM�ⲿ��ʱ������-------------//
void tim_delay_us(TIM_HandleTypeDef* HTIM,uint32_t Delay_us);
//------------------------------//
#endif

/********************************End of Head************************************/

