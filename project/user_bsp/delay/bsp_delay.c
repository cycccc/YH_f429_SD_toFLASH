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
 * �ļ�����: bsp_delay.c
 * ������Ա: CY
 * ��������: 2021-04-17
 * �ĵ�����:
 *
 *----------------------------------�汾��Ϣ------------------------------------
 * �汾����: V1.0
 * �汾˵��:
 *          |-1.0
 * 	         |-2021-04-17
 * 	          |-��ʼ�汾
 *------------------------------------------------------------------------------
 */

#include "./bsp_delay.h"
#include "../typedef/bsp_typedef.h"

//DWT���ټ�������ʱ����---------//
/**
 * dwt_delay_init
 * @brief  DWT������������ʼ����ֻ�����˼���
 * @param
 *   @arg   None
 * @data    2021-04-17
 * @retval  None
 */
void dwt_delay_init(void) {
    DEM_CR         |=  DEM_CR_TRCENA;
    DWT_CYCCNT      = 0u;
    DWT_CR         |= DWT_CR_CYCCNTENA;
}

/**
 * dwt_delay_us
 * @brief   ��1usΪ��λ��������ʱ
 * @param
 *   @arg   usec: [����] ��Ҫ��ʱ������
 * @data    2021-04-17
 * @retval  None
 */
void dwt_delay_us(uint32_t usec) {
    uint32_t startts, endts, ts;
    startts = DWT_CYCCNT;

    ts =  usec * (HAL_RCC_GetHCLKFreq() / (1000 * 1000));
    endts = startts + ts;
    if(endts > startts) {
        while(DWT_CYCCNT < endts);
    } else {
        while(DWT_CYCCNT > endts);
        while(DWT_CYCCNT < endts);
    }
}
//------------------------------//

//TIM�ⲿ��ʱ������-------------//
/**
 * HAL_Delay_us
 * @brief
 * @param
 *   @arg   at24cxx_x :[����] оƬ���ݶ�����
 *   @arg   Delay_us: [����] ��Ҫ��ʱ��ʱ��
 * @data    2021-04-17
 * @retval  None
 */
void tim_delay_us(TIM_HandleTypeDef* HTIM, uint32_t Delay_us) {
    __HAL_TIM_SET_COUNTER(HTIM, 0);           //��CNTֵ����Ϊ0

    HAL_TIM_Base_Start(HTIM);                 //������ʱ��
    while(__HAL_TIM_GET_COUNTER(HTIM) < Delay_us); //��ѯ�������ļ���ֵ�ж�
    HAL_TIM_Base_Stop(HTIM);//Ƶ������ʱ������ע�͵����
}
//------------------------------//

/********************************End of File************************************/

