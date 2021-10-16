/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#define  _PRINTF_OPEN
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "sdio.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../user_bsp/w25qxx/bsp_w25qxx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//私人定义
//文件名称
#define FILE_NAME           "all.bin"
//需要写入到FLASH中的起始地址
#define FLASH_ADDRESS       0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_SDIO_SD_Init();
    MX_SPI1_Init();
    MX_FATFS_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
    /**
    **************************************************************
    * Description : 禁用WiFi模块,并拉高PA8 让FATFS认为卡已经插入
    * Argument(s) : none.
    * Return(s)   : none.
    **************************************************************
    */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

    printf("> 程序开始..\n");

    //flash 初始化
    printf("> FLASH 初始化进行中..\n");
    W25QXX_Init();

    if(W25Qxx_Type != 0)
    {
        printf("> FLASH 初始化成功！\n");

        printf("> SD卡 初始化进行中..\n");
        retSD = f_mount(&SDFatFS, SDPath, 1); //挂载SD卡

        if(retSD == FR_OK)
        {
            printf("> SD卡 挂载成功！\n");
            printf("> 程序正常运行..\n");
            printf("> 请按KEI_1按键进行程序COPY..\n");
            printf("> 请按KEI_2按键进行 FLASH 擦除..\n");
            /* USER CODE END 2 */

            /* Infinite loop */
            /* USER CODE BEGIN WHILE */
            while (1)
            {
                /* USER CODE END WHILE */

                /* USER CODE BEGIN 3 */
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) //检测按键按下
                {
                    while(1)
                    {

                        //接下来就是正常的程序
                        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)  //检测按键弹出，证明1次按下已结束
                        {
                            //以下，开始
                            //-- > FILE_NAME
                            //-- > FLASH_ADDRESS
                            uint8_t SD_TO_Flash_buf[512] = {0};
                            uint32_t read_len = 0;
                            uint32_t freq = 0;
                            uint32_t flash_address = FLASH_ADDRESS;
                            uint8_t flash_read_check = 0;
                            uint8_t check_flag = 0;

                            retSD = f_open(&SDFile, FILE_NAME, FA_READ); //打开文件  文件属性为只读属性

                            if(retSD == FR_OK)
                            {
                                printf("> 文件打开成功！开始进入写入文件阶段...\n");

                                do
                                {
                                    retSD = f_read(&SDFile, SD_TO_Flash_buf, 512, &read_len); //读取数据
                                    freq++;

                                    if(retSD == FR_OK)
                                    {
                                        if(read_len != 0)   //确保正好等于0
                                        {
                                            W25QXX_Write(SD_TO_Flash_buf, flash_address, read_len); //写入flash

                                            //写入完成后，直接进入校验
                                            for(uint32_t read_len_check = 0; read_len_check < read_len; read_len_check++)
                                            {
                                                W25QXX_Read(&flash_read_check, flash_address + read_len_check, 1); //flash读取一个字节

                                                if(flash_read_check != SD_TO_Flash_buf[read_len_check])
                                                {
                                                    check_flag = 1;
                                                    break;
                                                }
                                            }

                                            if(check_flag == 1)
                                            {
                                                printf("> 文件校验错误！错误发生在第 %d 次校验。\n", freq);
                                                break;
                                            }

                                            flash_address += read_len;
                                        }
                                    }
                                    else
                                    {
                                        printf("> 文件读取错误！错误发生在第 %d 次读取。\n", freq);
                                        break;
                                    }
                                }
                                while(read_len == 512);

                                //判断是否校验成功
                                if(check_flag == 0)
                                {
                                    printf("> 文件校验成功！本次写入结束! \n");
                                    printf("> flash 接下来的地址为：%d\n", flash_address);
                                }

                                f_close(&SDFile);  //关闭文件
                            }
                            else
                            {
                                printf("> 文件无法打开，请确认文件完好或是否存在！\n");
                            }

                            //以上结束
                            break;
                        }
                    }

                    printf("> 请按KEI_1按键进行程序COPY..\n");
                    printf("> 请按KEI_2按键进行 FLASH 擦除..\n");
                }

                if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) //检测按键按下
                {
                    while(1)
                    {
                        if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)  //检测按键弹出，证明1次按下已结束
                        {
                            printf("> 正在擦除 FLASH 中..\n");
                            W25QXX_ChipErase();
                            printf("> FLASH 擦除结束! \n");
                            break;
                        }
                    }

                    printf("> 请按KEI_1按键进行程序COPY..\n");
                    printf("> 请按KEI_2按键进行 FLASH 擦除..\n");
                }
            }
        }
        else
        {
            printf("> SD卡挂载失败，请重试！\n");
        }
    }
    else
    {
        printf("> FLASH 初始化失败，请重试！\n");
    }

    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 8;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Activate the Over-Drive mode
    */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

void copy_From_SD_TO_Flash(void)
{


}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM7)
    {
        HAL_IncTick();
    }

    /* USER CODE BEGIN Callback 1 */

    /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();

    while (1)
    {
    }

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
