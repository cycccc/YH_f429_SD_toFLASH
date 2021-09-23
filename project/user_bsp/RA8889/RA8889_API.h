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
 * 文件名称: RA8889_API.h
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

#ifndef __RA8889__API_H_
#define __RA8889__API_H_

/*************** RAIO Technology Inc. ***************
* file		: RA8889_API.h
* author		: RAIO Application Team ^v^
* version		: V1.0
* date		: 2020/04/21
* brief		:
* RAIO copyright
****************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "delay.h"
#include "UserDef.h"
#include "RA8889_MCU_IF.h"
#include "RA8889.h"


#include "W25N01GV.h"

#include "main.h"


//#define nand_buff    13824000
//#define shadow_buff  6912000


//------color----------------
/*
	LCD 颜色代码，CL_是Color的简写
	16Bit由高位至低位， RRRR RGGG GGGB BBBB

	下面的RGB 宏将24位的RGB值转换为16位格式。
	启动windows的画笔程序，点击编辑颜色，选择自定义颜色，可以获得的RGB值。

	推荐使用迷你取色器软件获得你看到的界面颜色。
*/
/*这里把B和R的数据线交换了*/
//RGB565_模式------------------------------------
#define RGB_565(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	/* 将8位R,G,B转化为 16位RGB565格式 */
#define RGB565_R(x)  ((x >> 8) & 0xF8)
#define RGB565_G(x)  ((x >> 3) & 0xFC)
#define RGB565_B(x)  ((x << 3) & 0xF8)
//RGB888_模式------------------------------------
#define RGB_888(R,G,B)	((R << 16) | (G << 8) | B)

enum
{
    CL_WHITE_888          = RGB_888(255,255,255),	/* 白色 */
    CL_BLACK_888          = RGB_888(  0,  0,  0),	/* 黑色 */
    CL_RED_888            = RGB_888(255,	0,  0),	/* 红色 */
    CL_GREEN_888          = RGB_888(  0,255,  0),	/* 绿色 */
    CL_BLUE_888           = RGB_888(  0,	0,255),	/* 蓝色 */
    CL_YELLOW_888         = RGB_888(255,255,  0),	/* 黄色 */

    CL_GREY_888           = RGB_888( 98, 98, 98), 	  /* 深灰色 */
    CL_GREY1_888		      = RGB_888( 150, 150, 150), 	/* 浅灰色 */
    CL_GREY2_888		      = RGB_888( 180, 180, 180), 	/* 浅灰色 */
    CL_GREY3_888		      = RGB_888( 200, 200, 200), 	/* 最浅灰色 */
    CL_GREY4_888		      = RGB_888( 230, 230, 230), 	/* 最浅灰色 */

    CL_BUTTON_GREY_888	  = RGB_888( 220, 220, 220), /* WINDOWS 按钮表面灰色 */

    CL_MAGENTA_888        = RGB_888( 255, 110, 219),	/* 红紫色，洋红色 */
    CL_CYAN_888           = RGB_888( 140, 255, 251),	/* 蓝绿色，青色 */

    CL_BLUE1_888          = RGB_888(  0,  0, 240),		/* 深蓝色 */
    CL_BLUE2_888          = RGB_888(  0,  0, 128),		/* 深蓝色 */
    CL_BLUE3_888          = RGB_888(  68, 68, 255),		/* 浅蓝色1 */
    CL_BLUE4_888          = RGB_888(  0, 64, 128),		/* 浅蓝色1 */

    /* UI 界面 Windows控件常用色 */
    CL_BTN_FACE_888		    = RGB_888(236, 233, 216),	/* 按钮表面颜色(灰) */
    CL_BOX_BORDER1_888	  = RGB_888(172, 168,153),	/* 分组框主线颜色 */
    CL_BOX_BORDER2_888	  = RGB_888(255, 255,255),	/* 分组框阴影线颜色 */  
    
    //-----------------------------------------------------------------------//
    
    CL_WHITE_565          = RGB_565(255,255,255),	/* 白色 */
    CL_BLACK_565          = RGB_565(  0,  0,  0),	/* 黑色 */
    CL_RED_565            = RGB_565(255,	0,  0),	/* 红色 */
    CL_GREEN_565          = RGB_565(  0,255,  0),	/* 绿色 */
    CL_BLUE_565           = RGB_565(  0,	0,255),	/* 蓝色 */
    CL_YELLOW_565         = RGB_565(255,255,  0),	/* 黄色 */

    CL_GREY_565           = RGB_565( 98, 98, 98), 	  /* 深灰色 */
    CL_GREY1_565		      = RGB_565( 150, 150, 150), 	/* 浅灰色 */
    CL_GREY2_565		      = RGB_565( 180, 180, 180), 	/* 浅灰色 */
    CL_GREY3_565		      = RGB_565( 200, 200, 200), 	/* 最浅灰色 */
    CL_GREY4_565		      = RGB_565( 230, 230, 230), 	/* 最浅灰色 */

    CL_BUTTON_GREY_565	  = RGB_565( 220, 220, 220), /* WINDOWS 按钮表面灰色 */

    CL_MAGENTA_565        = RGB_565( 255, 110, 219),	/* 红紫色，洋红色 */
    CL_CYAN_565           = RGB_565( 140, 255, 251),	/* 蓝绿色，青色 */

    CL_BLUE1_565          = RGB_565(  0,  0, 240),		/* 深蓝色 */
    CL_BLUE2_565          = RGB_565(  0,  0, 128),		/* 深蓝色 */
    CL_BLUE3_565          = RGB_565(  68, 68, 255),		/* 浅蓝色1 */
    CL_BLUE4_565          = RGB_565(  0, 64, 128),		/* 浅蓝色1 */

    /* UI 界面 Windows控件常用色 */
    CL_BTN_FACE_565		    = RGB_565(236, 233, 216),	/* 按钮表面颜色(灰) */
    CL_BOX_BORDER1_565	  = RGB_565(172, 168,153),	/* 分组框主线颜色 */
    CL_BOX_BORDER2_565	  = RGB_565(255, 255,255),	/* 分组框阴影线颜色 */


    CL_MASK		= 0x9999	/* 颜色掩码，用于文字背景透明 */
};

//---------------------------

void MPU8_8bpp_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned char *data);
void MPU8_16bpp_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned char *data);
void MPU8_24bpp_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned char *data);
void MPU16_16bpp_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned short *data);
void MPU16_24bpp_Mode1_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned short *data);
void MPU16_24bpp_Mode2_Memory_Write (unsigned short x,unsigned short y,unsigned short w,unsigned short h,const unsigned short *data);


void PIP(unsigned char On_Off, unsigned char Select_PIP,unsigned long PAddr,unsigned short XP,unsigned short YP,unsigned long ImageWidth,unsigned short X_Dis,unsigned short Y_Dis,unsigned short X_W,unsigned short Y_H);

void Print_Internal_Font_Hexvariable(unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,  unsigned int tmp2);
void Print_Internal_Font_Decimalvariable(unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,unsigned int tmp2);
void Print_Internal_Font_String(unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor, char tmp2[]);
void Print_BIG5String(unsigned char Clk,unsigned char BUS,unsigned char SCS,unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,char *tmp2);
void Print_GB2312String(unsigned char Clk,unsigned char BUS,unsigned char SCS,unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,char *tmp2);
void Print_GB12345String(unsigned char Clk,unsigned char BUS,unsigned char SCS,unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,char tmp2[]);
void Print_UnicodeString(unsigned char Clk,unsigned char BUS,unsigned char SCS,unsigned short x,unsigned short y,unsigned short X_W,unsigned short Y_H,unsigned long FontColor,unsigned long BackGroundColor,unsigned short *tmp2);
void Select_Font_Height_WxN_HxN_ChromaKey_Alignment(unsigned char Font_Height,unsigned char XxN,unsigned char YxN,unsigned char ChromaKey,unsigned char Alignment);
void Show_String(char *str);


void Draw_Line(unsigned long LineColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2);
void Draw_Triangle(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2,unsigned short X3,unsigned short Y3);
void Draw_Triangle_Fill(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2,unsigned short X3,unsigned short Y3);
void Draw_Circle(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short R);
void Draw_Circle_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short R);
void Draw_Ellipse(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Ellipse_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Left_Up_Curve(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Left_Up_Curve_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Right_Down_Curve(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Right_Down_Curve_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Right_Up_Curve(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Right_Up_Curve_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Left_Down_Curve(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Left_Down_Curve_Fill(unsigned long ForegroundColor,unsigned short XCenter,unsigned short YCenter,unsigned short X_R,unsigned short Y_R);
void Draw_Square(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2);
void Draw_Square_Fill(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2);
void Draw_Circle_Square(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2,unsigned short R,unsigned short Y_R);
void Draw_Circle_Square_Fill(unsigned long ForegroundColor,unsigned short X1,unsigned short Y1,unsigned short X2,unsigned short Y2,unsigned short R,unsigned short Y_R);


void BTE_Memory_Copy(unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned int ROP_Code,unsigned short X_W,unsigned short Y_H);
void BTE_Memory_Copy_Chroma_key(unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned long Background_color,unsigned short X_W,unsigned short Y_H);
void BTE_MCU_Write_MCU_8bit(unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned int ROP_Code,unsigned short X_W,unsigned short Y_H,const unsigned char *data);
void BTE_MCU_Write_MCU_16bit(unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned int ROP_Code,unsigned short X_W,unsigned short Y_H,const unsigned short *data);
void BTE_MCU_Write_Chroma_key_MCU_8bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned long Background_color,unsigned short X_W,unsigned short Y_H,const unsigned char *data);
void BTE_MCU_Write_Chroma_key_MCU_16bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned long Background_color,unsigned short X_W,unsigned short Y_H,const unsigned short *data);
void BTE_Memory_Copy_ColorExpansion(unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color,unsigned long Background_color);
void BTE_Memory_Copy_ColorExpansion_Chroma_key(unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color);
void BTE_MCU_Write_ColorExpansion_MCU_8bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color,unsigned long Background_color,const unsigned char *data);
void BTE_MCU_Write_ColorExpansion_MCU_16bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color,unsigned long Background_color,const unsigned short *data);
void BTE_MCU_Write_ColorExpansion_Chroma_key_MCU_8bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color,const unsigned char *data);
void BTE_MCU_Write_ColorExpansion_Chroma_key_MCU_16bit(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned long Foreground_color,const unsigned short *data);
void BTE_Pattern_Fill(unsigned char P_8x8_or_16x16, unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned int ROP_Code,unsigned short X_W,unsigned short Y_H);
void BTE_Pattern_Fill_With_Chroma_key(unsigned char P_8x8_or_16x16,unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned int ROP_Code,unsigned long Background_color,unsigned short X_W,unsigned short Y_H);
void BTE_Solid_Fill(unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned long Foreground_color,unsigned short X_W,unsigned short Y_H);
void BTE_Alpha_Blending_Picture_Mode(unsigned long S0_Addr,unsigned short S0_W,unsigned short XS0,unsigned short YS0,unsigned long S1_Addr,unsigned short S1_W,unsigned short XS1,unsigned short YS1,unsigned long Des_Addr,unsigned short Des_W, unsigned short XDes,unsigned short YDes,unsigned short X_W,unsigned short Y_H,unsigned char alpha);



void PWM0(unsigned char on_off, unsigned char Clock_Divided, unsigned char Prescalar, unsigned short Count_Buffer,unsigned short Compare_Buffer);
void PWM1(unsigned char on_off, unsigned char Clock_Divided, unsigned char Prescalar, unsigned short Count_Buffer,unsigned short Compare_Buffer);

void Print_Hex(unsigned char buf);


void putPixel(unsigned short x,unsigned short y,unsigned long color);
void lcdPutChar8x12(unsigned short x,unsigned short y,unsigned long fgcolor,unsigned long bgcolor, unsigned char bg_transparent,unsigned char code);
void lcdPutString8x12(unsigned short x,unsigned short y, unsigned long fgcolor, unsigned long bgcolor,unsigned char bg_transparent,char *ptr);
void lcdPutChar16x24(unsigned short x,unsigned short y,unsigned long fgcolor,unsigned long bgcolor,unsigned char bg_transparent,unsigned char code);
void lcdPutString16x24(unsigned short x,unsigned short y, unsigned long fgcolor, unsigned long bgcolor,unsigned char bg_transparent,char *ptr);
void lcdPutChar32x48(unsigned short x,unsigned short y,unsigned long fgcolor,unsigned long bgcolor,unsigned char bg_transparent,unsigned char code);
void lcdPutString32x48(unsigned short x,unsigned short y, unsigned long fgcolor, unsigned long bgcolor,unsigned char bg_transparent,char *ptr);



void SPI_NAND_initial_DMA (unsigned char SCS, unsigned char BUS);
void SPI_NAND_initial_JPG_AVI (unsigned char BUS,unsigned char SCS,unsigned char SCK_Divide);
void AVI_NAND(unsigned long addr,unsigned long videosize,unsigned long shadow_buffer_addr, unsigned long PIP_buffer_addr,unsigned long x,unsigned long y,unsigned long height,unsigned long width,unsigned long PIP_canvas_Width);
void JPG_NAND (unsigned long addr,unsigned long JPGsize,unsigned long IDEC_canvas_width, unsigned short x,unsigned short y);
void SPI_NAND_DMA_png (unsigned long dma_page_addr,unsigned long pic_buffer_Layer,unsigned long Show_pic_Layer,unsigned int picture_Width,unsigned int picture_Height);
void SPI_NAND_DMA (unsigned long dma_page_addr,unsigned long X_coordinate,unsigned long Y_coordinate,unsigned long des_canvas_width,unsigned int picture_Width,unsigned int picture_Height,unsigned long pic_buffer_Layer,unsigned long Show_pic_Layer,unsigned char chorma,unsigned long Background_color);

void DMA_24bit(unsigned char Clk,unsigned short X1,unsigned short Y1,unsigned short X_W,unsigned short Y_H,unsigned short P_W,unsigned long Addr);
void DMA_32bit(unsigned char Clk,unsigned short X1,unsigned short Y1,unsigned short X_W,unsigned short Y_H,unsigned short P_W,unsigned long Addr);
void switch_24bits_to_32bits(unsigned char BUS,unsigned char SCS);

void SPI_NOR_Flash_switch_QUAD_MODE(unsigned char BUS,unsigned char SCS,unsigned char flash);
void SPI_NOR_initial_DMA (unsigned char mode,unsigned char BUS,unsigned char SCS,unsigned char flash,unsigned char addr_24b_32b);
void SPI_NOR_initial_JPG_AVI (unsigned char flash,unsigned char addr_24b_32b,unsigned char BUS,unsigned char SCS,unsigned char SCK_Divide);
void SPI_NOR_DMA_png (unsigned long dma_page_addr,unsigned long pic_buffer_Layer,unsigned long Show_pic_Layer,unsigned int picture_Width,unsigned int picture_Height);

void JPG_NOR (unsigned long addr,unsigned long JPGsize,unsigned long IDEC_canvas_width,unsigned short x,unsigned short y);
void AVI_NOR(unsigned long addr,unsigned long videosize,unsigned long shadow_buffer_addr,unsigned long PIP_buffer_addr,unsigned long x,unsigned long y,unsigned long height,unsigned long width,unsigned long PIP_width);

void BTE_alpha_blending_32bit_Pixel_mode(unsigned int picture_Width,unsigned int BTE_X,unsigned int BTE_Y,unsigned long S0X,unsigned long S0Y,unsigned long S0_Start_Addr,unsigned long S0_canvas_width,unsigned long desX,unsigned long desY,unsigned long DES_Start_Addr,unsigned long DES_canvas_width,unsigned long pic_buffer_Layer);

void AVI_window(unsigned char ON_OFF);

#endif

/********************************End of Head************************************/
