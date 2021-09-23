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
 * �ļ�����: bsp_at24cxx.c
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

#include "./bsp_at24cxx.h"

AT24CXX_HandleTypedef at24cxx_1 = {
    .EEPROM_ID = 1,
    .ready = 0,
    .Type = AT24C256,
    .address = 1 << 7 | 1 << 5,
    .HIIC = &hi2c1,
};


#if (!SOFTWARE_IIC)       ///>ʹ��Ӳ��IIC
/**
  * @brief  I2C ����(EEPROM)��ʼ��
  * @param
  *   @arg at24cxx_x :[����] оƬ���ݶ�����
  * @retval ��
  */
void I2C_EE_Init(AT24CXX_HandleTypedef* at24cxx_x) {
    at24cxx_x->ready = 1;
}

/**
  * @brief   ��EEPROM��һ��дѭ���п���д����ֽڣ���һ��д����ֽ���
  *          ���ܳ���EEPROMҳ�Ĵ�С��AT24C02ÿҳ��8���ֽ�
  * @param
  *   @arg at24cxx_x :[����] оƬ���ݶ�����
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ
  *   @arg NumByteToWrite:д���ֽ���
  * @retval  д���״̬
  */
uint32_t I2C_EE_PageWrite(AT24CXX_HandleTypedef* at24cxx_x, uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite) {
    HAL_StatusTypeDef status = HAL_ERROR;
    uint32_t MemAdd_size;
    if(at24cxx_x->ready) {
        switch(at24cxx_x->Type) {
            case AT24C128:
            case AT24C256:
                MemAdd_size = I2C_MEMADD_SIZE_16BIT;
                break;
            default:
                MemAdd_size = I2C_MEMADD_SIZE_8BIT;
                break;
        }

        /* Write EEPROM_PAGESIZE */
        status = HAL_I2C_Mem_Write(at24cxx_x->HIIC, at24cxx_x->address, WriteAddr, MemAdd_size, (uint8_t*)(pBuffer), NumByteToWrite, I2CT_FLAG_TIMEOUT);

        while (HAL_I2C_GetState(at24cxx_x->HIIC) != HAL_I2C_STATE_READY) {
        }

        /* Check if the EEPROM is ready for a new operation */
        while (HAL_I2C_IsDeviceReady(at24cxx_x->HIIC, at24cxx_x->address, EEPROM_MAX_TRIALS, I2Cx_TIMEOUT_MAX) == HAL_TIMEOUT);

        /* Wait for the end of the transfer */
        while (HAL_I2C_GetState(at24cxx_x->HIIC) != HAL_I2C_STATE_READY) {
        }
    }
    return status;
}



/**
  * @brief   ���������е�����д��I2C EEPROM��
  * @param
  *   @arg at24cxx_x :[����] оƬ���ݶ�����
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ
  *   @arg NumByteToWrite:д���ֽ���
  * @retval  д���״̬
  */
uint32_t I2C_EE_BufferWrite(AT24CXX_HandleTypedef* at24cxx_x, uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, EEpromPageSize = 0;
    uint32_t status = HAL_ERROR;

    if(at24cxx_x->ready) {
        switch(at24cxx_x->Type) {
            case AT24C01:  /* AT24C01/02ÿҳ��8���ֽ� */
            case AT24C02:
                EEpromPageSize = 8;
                break;
            case AT24C04:  /* AT24C04/08/16ÿҳ��16���ֽ� */
            case AT24C08:
            case AT24C16:
                EEpromPageSize = 16;
                break;
            case AT24C32:  /* AT24C32/64ÿҳ��32���ֽ� */
            case AT24C64:
                EEpromPageSize = 16;
                break;
            case AT24C128: /* AT24C128/256ÿҳ��64���ֽ� */
            case AT24C256:
                EEpromPageSize = 16;
                break;
            default:       /* ����û�е� Ĭ��ÿҳ��8���ֽ� */
                EEpromPageSize = 8;
                break;
        }

        Addr = WriteAddr % EEpromPageSize;
        count = EEpromPageSize - Addr;
        NumOfPage =  NumByteToWrite / EEpromPageSize;
        NumOfSingle = NumByteToWrite % EEpromPageSize;

        /* If WriteAddr is I2C_PageSize aligned  */
        if(Addr == 0) {
            /* If NumByteToWrite < I2C_PageSize */
            if(NumOfPage == 0) {
                status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, NumOfSingle);
            }
            /* If NumByteToWrite > I2C_PageSize */
            else {
                while(NumOfPage--) {
                    status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, EEpromPageSize);
                    WriteAddr +=  EEpromPageSize;
                    pBuffer += EEpromPageSize;
                }

                if(NumOfSingle != 0) {
                    status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, NumOfSingle);
                }
            }
        }
        /* If WriteAddr is not I2C_PageSize aligned  */
        else {
            /* If NumByteToWrite < I2C_PageSize */
            if(NumOfPage == 0) {
                status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, NumOfSingle);
            }
            /* If NumByteToWrite > I2C_PageSize */
            else {
                NumByteToWrite -= count;
                NumOfPage =  NumByteToWrite / EEpromPageSize;
                NumOfSingle = NumByteToWrite % EEpromPageSize;

                if(count != 0) {
                    status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, count);
                    WriteAddr += count;
                    pBuffer += count;
                }

                while(NumOfPage--) {
                    status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, EEpromPageSize);
                    WriteAddr +=  EEpromPageSize;
                    pBuffer += EEpromPageSize;
                }
                if(NumOfSingle != 0) {
                    status = I2C_EE_PageWrite(at24cxx_x, pBuffer, WriteAddr, NumOfSingle);
                }
            }
        }
    }
    return status;
}

/**
  * @brief   ��EEPROM�����ȡһ������
  * @param
  *   @arg at24cxx_x :[����] оƬ���ݶ�����
  *		@arg pBuffer:��Ŵ�EEPROM��ȡ�����ݵĻ�����ָ��
  *		@arg WriteAddr:�������ݵ�EEPROM�ĵ�ַ
  *     @arg NumByteToWrite:Ҫ��EEPROM��ȡ���ֽ���
  * @retval  ��ȡ��״̬
  */
uint32_t I2C_EE_BufferRead(AT24CXX_HandleTypedef* at24cxx_x, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead) {
    HAL_StatusTypeDef status = HAL_ERROR;
    uint32_t MemAdd_size;

    if(at24cxx_x->ready) {
        switch(at24cxx_x->Type) {
            case AT24C128:
            case AT24C256:
                MemAdd_size = I2C_MEMADD_SIZE_16BIT;
                break;
            default:
                MemAdd_size = I2C_MEMADD_SIZE_8BIT;
                break;
        }
        status = HAL_I2C_Mem_Read(at24cxx_x->HIIC, at24cxx_x->address | 1, ReadAddr, MemAdd_size, (uint8_t *)pBuffer, NumByteToRead, I2CT_FLAG_TIMEOUT);
    }
    return status;
}
#else      ///>ʹ�����IIC

#endif
/********************************End of File************************************/

