/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef        AdcHandle;
DMA_HandleTypeDef        HdmaCh1;
uint32_t                 gADCxConvertedData[4];
TIM_HandleTypeDef        TimHandle;
TIM_MasterConfigTypeDef  sMasterConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcConfig(void);
static void APP_TimConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{ 
  /* Reset of all peripherals, Initializes the Systick. */ 
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
   
  /* Initialize UART */
  BSP_USART_Config();

  /* Configure ADC */
  APP_AdcConfig();
  
  HAL_ADC_Start_DMA(&AdcHandle,gADCxConvertedData,4);
  
  /* TIM configuration */
  APP_TimConfig();
  
  while(1)
  {
    BSP_LED_Toggle(LED_GREEN);
    while(!__HAL_DMA_GET_FLAG(&HdmaCh1, DMA_ISR_TCIF1));                               
    
    /* Clear DMA channel 1 transmission completion flag */
    __HAL_DMA_CLEAR_FLAG(&HdmaCh1, DMA_IFCR_CTCIF1);       
    printf("Channel4: %u \r\n",(unsigned int)(gADCxConvertedData[0]));
    printf("Channel5: %u \r\n",(unsigned int)(gADCxConvertedData[1]));
    printf("Channel6: %u \r\n",(unsigned int)(gADCxConvertedData[2]));
    printf("Channel7: %u \r\n",(unsigned int)(gADCxConvertedData[3]));   
  }
}

/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
static void APP_AdcConfig()
{   
  ADC_ChannelConfTypeDef   sConfig = {0};  

  AdcHandle.Instance=ADC1;
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;             /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;            /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_ENABLE;                /* Scanning mode enable */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                        /* Single mode */
  AdcHandle.Init.NbrOfConversion       = 4;                              /* Number of conversion channels 4 */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                        /* Discontinuous mode not enabled */
  AdcHandle.Init.NbrOfDiscConversion   = 1;                              /* Discontinuous mode short sequence length is 1 */
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T15_TRGO;  /* TIM15 trigger */
  /* ADC initialization */
  HAL_ADC_Init(&AdcHandle);
   
  sConfig.Channel=ADC_CHANNEL_4;
  sConfig.Rank=ADC_REGULAR_RANK_1;
  sConfig.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;  
  /* ADC channel configuration */
  HAL_ADC_ConfigChannel(&AdcHandle,&sConfig);
  
  sConfig.Channel=ADC_CHANNEL_5;
  sConfig.Rank=ADC_REGULAR_RANK_2;  
  sConfig.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;  
  /* ADC channel configuration */
  HAL_ADC_ConfigChannel(&AdcHandle,&sConfig);
  
  sConfig.Channel=ADC_CHANNEL_6;
  sConfig.Rank=ADC_REGULAR_RANK_3;  
  sConfig.SamplingTime=ADC_SAMPLETIME_239CYCLES_5; 
  /* ADC channel configuration */
  HAL_ADC_ConfigChannel(&AdcHandle,&sConfig);
  
  sConfig.Channel=ADC_CHANNEL_7;
  sConfig.Rank=ADC_REGULAR_RANK_4; 
  sConfig.SamplingTime=ADC_SAMPLETIME_239CYCLES_5; 
  /* ADC channel configuration */
  HAL_ADC_ConfigChannel(&AdcHandle,&sConfig); 
  
  /* ADC calibration */
  if(HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
/*  if(HAL_ADCEx_Calibration_GetStatus(&AdcHandle) != HAL_ADCCALIBOK)   */
/*  {                                                                   */
/*    APP_ErrorHandler();                                               */
/*  }                                                                   */
}

/**
  * @brief  TIM Configuration Function
  * @param  None
  * @retval None
  */
static void APP_TimConfig(void)
{
  TimHandle.Instance = TIM15;                                         /* TIM15 */
  TimHandle.Init.Period            = 8000 - 1;                        /* Period = 8000-1 */
  TimHandle.Init.Prescaler         = 1000 - 1;                        /* Prescaler = 1000-1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /* Clock does not divide frequency */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /* count up */
  TimHandle.Init.RepetitionCounter = 0;                               /* no-repeat */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* Automatic reloading of registers without buffering */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                        /* Initialize TIM15 */
  {
    APP_ErrorHandler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                /* Select Update Event as Trigger Source */
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        /* Master/Slave mode has no effect */
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig);  /* Configure TIM15*/
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)                       /* TIM15 start */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  System clock configuration function.
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE; /* Select oscillator HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                          /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                          /* HSI 1 frequency division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;  /* Configure HSI clock at 8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                         /* Close HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                         /* Close LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                         /* Close LSE */
  /*RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM;*/
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_OFF;                     /* Close PLL */
  /*RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_NONE;*/
  /*RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;*/
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* Choose to configure clock HCLK, SYSCLK, PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS; /* Select HSI as the system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;     /* AHB clock 1 division */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;      /* APB clock 1 division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
