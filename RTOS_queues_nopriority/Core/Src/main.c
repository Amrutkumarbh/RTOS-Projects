/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Definitions for SendTask */
osThreadId_t SendTaskHandle;
const osThreadAttr_t SendTask_attributes = {
  .name = "SendTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ReceiveTasks */
osThreadId_t ReceiveTasksHandle;
const osThreadAttr_t ReceiveTasks_attributes = {
  .name = "ReceiveTasks",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SendTask02 */
osThreadId_t SendTask02Handle;
const osThreadAttr_t SendTask02_attributes = {
  .name = "SendTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ReceiveTask02 */
osThreadId_t ReceiveTask02Handle;
const osThreadAttr_t ReceiveTask02_attributes = {
  .name = "ReceiveTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};
/* Definitions for myQueue02 */
osMessageQueueId_t myQueue02Handle;
const osMessageQueueAttr_t myQueue02_attributes = {
  .name = "myQueue02"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartSendTask(void *argument);
void StartReceiveTask(void *argument);
void StartSend02(void *argument);
void StartReceive02(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file,char *ptr, int len)
{
	int i = 0;
	for(i=0;i<len;i++)
	{
		ITM_SendChar((*ptr++));
	}
	return len;
}
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (5, sizeof(uint16_t), &myQueue01_attributes);

  /* creation of myQueue02 */
  myQueue02Handle = osMessageQueueNew (16, sizeof(uint16_t), &myQueue02_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of SendTask */
  SendTaskHandle = osThreadNew(StartSendTask, NULL, &SendTask_attributes);

  /* creation of ReceiveTasks */
  ReceiveTasksHandle = osThreadNew(StartReceiveTask, NULL, &ReceiveTasks_attributes);

  /* creation of SendTask02 */
  SendTask02Handle = osThreadNew(StartSend02, NULL, &SendTask02_attributes);

  /* creation of ReceiveTask02 */
  ReceiveTask02Handle = osThreadNew(StartReceive02, NULL, &ReceiveTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartSendTask */
/**
  * @brief  Function implementing the SendTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartSendTask */
void StartSendTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	uint16_t value = 0;
  for(;;)
  {
	  printf("Send Task is Active\r\n");
	  osMessageQueuePut(myQueue01Handle, &value, 0, 200);
	  value = value + 100;

    osDelay(500);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartReceiveTask */
/**
* @brief Function implementing the ReceiveTasks thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReceiveTask */
void StartReceiveTask(void *argument)
{
  /* USER CODE BEGIN StartReceiveTask */
  /* Infinite loop */
	uint16_t rxdata;
  for(;;)
  {
	  printf("Receive Task is Active\r\n");
	  osMessageQueueGet(myQueue01Handle, &rxdata, NULL, 200);
	  printf("Data Accessed : %d\r\n",rxdata);

    osDelay(2000);
  }
  /* USER CODE END StartReceiveTask */
}

/* USER CODE BEGIN Header_StartSend02 */
/**
* @brief Function implementing the SendTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSend02 */
void StartSend02(void *argument)
{
  /* USER CODE BEGIN StartSend02 */
  /* Infinite loop */
	uint16_t val2 = 0;
  for(;;)
  {
	  printf("Send Task is Active\r\n");
	  	  osMessageQueuePut(myQueue02Handle, &val2, 0, 200);
	  	  val2 = val2 + 100;

	      osDelay(500);
    osDelay(1);
  }
  /* USER CODE END StartSend02 */
}

/* USER CODE BEGIN Header_StartReceive02 */
/**
* @brief Function implementing the ReceiveTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReceive02 */
void StartReceive02(void *argument)
{
  /* USER CODE BEGIN StartReceive02 */
  /* Infinite loop */
	uint16_t rxdata2;
  for(;;)
  {
	  printf("Receive Task is Active\r\n");
	 	  osMessageQueueGet(myQueue02Handle, &rxdata2, NULL, 200);
	 	  printf("Data Accessed : %d\r\n",rxdata2);

	     osDelay(2000);
    osDelay(1);
  }
  /* USER CODE END StartReceive02 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
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
