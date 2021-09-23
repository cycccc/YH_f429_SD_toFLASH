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
 * 文件名称: W25N01GV.h
 * 创建人员: CY
 * 创建日期: 2021-02-18
 * 文档描述: 
 *
 *----------------------------------版本信息------------------------------------
 * 实验平台
 *          |--
 * 版本代号: V1.0
 * 版本说明: 
 *          |-1.0
 * 	         |-2021-02-18
 * 	          |-初始版本
 *------------------------------------------------------------------------------
 */

#ifndef __W25N01GV_H_
#define __W25N01GV_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "UserDef.h"
#include "delay.h"
#include "RA8889.h"
#include "RA8889_MCU_IF.h"

#include "main.h"

#define TRUE true
#define FALSE false




void W25N01_Write_Enable(void);
void W25N01_Write_Disable(void);
bool W25N01_Check_WEL(void);
void W25N01_Device_Reset(void);
void W25N01_Read_JEDEC_ID(unsigned char *manufacturer_id,unsigned short *device_id);
unsigned char W25N01_Read_Status_Register1(void);
unsigned char W25N01_Read_Status_Register2(void);
unsigned char W25N01_Read_Status_Register3(void);
void W25N01_Write_Status_Register1(unsigned char data);
void W25N01_Write_Status_Register2(unsigned char data);
void W25N01_Write_Status_Register3(unsigned char data);
bool W25N01_Check_Flash_Busy(void);
void W25N01_Clear_BUF(void);
void W25N01_Set_ECC(void);
//void W25N01_Factory_BBMandSetLUT(void);
unsigned short W25N01_Factory_Check_Bad_Blocks(unsigned char Buffer_Page[] );
void W25N01_Find_Bad_Block(void);
void W25N01_Read_BBM_LUT(unsigned char *LUT_list);
void W25N01_Disable_Block_Protect(void);
unsigned char W25N01_Block_Erase_128KB(unsigned short pageAddress);
unsigned char W25N01_Whole_Flash_Erase(void);
void W25N01_Load_Program_Data(unsigned short lenght,unsigned char *UpdataValue);
void W25N01_Program_Execute(unsigned short pageAddress);
void W25N01_Read_PageSize(unsigned short pageAddr);
void W25N01_Swap_Block(unsigned short BadBlockAddr, unsigned short GoodBlockAddr);

#endif

/********************************End of Head************************************/

