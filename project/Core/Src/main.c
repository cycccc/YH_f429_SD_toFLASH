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
//˽�˶���
//�ļ�����
#define FILE_NAME           "all.bin"
//��Ҫд�뵽FLASH�е���ʼ��ַ
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
    * Description : ����WiFiģ��,������PA8 ��FATFS��Ϊ���Ѿ�����
    * Argument(s) : none.
    * Return(s)   : none.
    **************************************************************
    */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

    printf("> ����ʼ..\n");

    //flash ��ʼ��
    printf("> FLASH ��ʼ��������..\n");
    W25QXX_Init();

    if(W25Qxx_Type != 0)
    {
        printf("> FLASH ��ʼ���ɹ���\n");

        printf("> SD�� ��ʼ��������..\n");
        retSD = f_mount(&SDFatFS, SDPath, 1); //����SD��

        if(retSD == FR_OK)
        {
            printf("> SD�� ���سɹ���\n");
            printf("> ������������..\n");
            printf("> �밴KEI_1�������г���COPY..\n");
            printf("> �밴KEI_2�������� FLASH ����..\n");
            /* USER CODE END 2 */

            /* Infinite loop */
            /* USER CODE BEGIN WHILE */
            while (1)
            {
                /* USER CODE END WHILE */

                /* USER CODE BEGIN 3 */
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) //��ⰴ������
                {
                    while(1)
                    {

                        //���������������ĳ���
                        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)  //��ⰴ��������֤��1�ΰ����ѽ���
                        {
                            //���£���ʼ
                            //-- > FILE_NAME
                            //-- > FLASH_ADDRESS
                            uint8_t SD_TO_Flash_buf[512] = {0};
                            uint32_t read_len = 0;
                            uint32_t freq = 0;
                            uint32_t flash_address = FLASH_ADDRESS;
                            uint8_t flash_read_check = 0;
                            uint8_t check_flag = 0;

                            retSD = f_open(&SDFile, FILE_NAME, FA_READ); //���ļ�  �ļ�����Ϊֻ������

                            if(retSD == FR_OK)
                            {
                                printf("> �ļ��򿪳ɹ�����ʼ����д���ļ��׶�...\n");

                                do
                                {
                                    retSD = f_read(&SDFile, SD_TO_Flash_buf, 512, &read_len); //��ȡ����
                                    freq++;

                                    if(retSD == FR_OK)
                                    {
                                        if(read_len != 0)   //ȷ�����õ���0
                                        {
                                            W25QXX_Write(SD_TO_Flash_buf, flash_address, read_len); //д��flash

                                            //д����ɺ�ֱ�ӽ���У��
                                            for(uint32_t read_len_check = 0; read_len_check < read_len; read_len_check++)
                                            {
                                                W25QXX_Read(&flash_read_check, flash_address + read_len_check, 1); //flash��ȡһ���ֽ�

                                                if(flash_read_check != SD_TO_Flash_buf[read_len_check])
                                                {
                                                    check_flag = 1;
                                                    break;
                                                }
                                            }

                                            if(check_flag == 1)
                                            {
                                                printf("> �ļ�У����󣡴������ڵ� %d ��У�顣\n", freq);
                                                break;
                                            }

                                            flash_address += read_len;
                                        }
                                    }
                                    else
                                    {
                                        printf("> �ļ���ȡ���󣡴������ڵ� %d �ζ�ȡ��\n", freq);
                                        break;
                                    }
                                }
                                while(read_len == 512);

                                //�ж��Ƿ�У��ɹ�
                                if(check_flag == 0)
                                {
                                    printf("> �ļ�У��ɹ�������д�����! \n");
                                    printf("> flash �������ĵ�ַΪ��%d\n", flash_address);
                                }

                                f_close(&SDFile);  //�ر��ļ�
                            }
                            else
                            {
                                printf("> �ļ��޷��򿪣���ȷ���ļ���û��Ƿ���ڣ�\n");
                            }

                            //���Ͻ���
                            break;
                        }
                    }

                    printf("> �밴KEI_1�������г���COPY..\n");
                    printf("> �밴KEI_2�������� FLASH ����..\n");
                }

                if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) //��ⰴ������
                {
                    while(1)
                    {
                        if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)  //��ⰴ��������֤��1�ΰ����ѽ���
                        {
                            printf("> ���ڲ��� FLASH ��..\n");
                            W25QXX_ChipErase();
                            printf("> FLASH ��������! \n");
                            break;
                        }
                    }

                    printf("> �밴KEI_1�������г���COPY..\n");
                    printf("> �밴KEI_2�������� FLASH ����..\n");
                }
            }
        }
        else
        {
            printf("> SD������ʧ�ܣ������ԣ�\n");
        }
    }
    else
    {
        printf("> FLASH ��ʼ��ʧ�ܣ������ԣ�\n");
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
