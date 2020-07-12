/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "lcd_config.h"
#include "GUI.h"
#include "touch.h"
#include "string.h"
#include "cJSON.h"
#include "usart.h"
#include "ButtonDLG.h"
#include "rtc.h"
//#include "GUIDemo.h"
//#include "MainTask.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern _m_tp_dev tp_dev;

extern char TX_Data[];
extern char Data[];
extern char Recive[5];
extern char Recive2[5];
extern uint8_t aRxBuffer2;			//接收中断缓冲2

extern uint8_t Uart2_Rx_Cnt;		//接收缓冲计数

extern cJSON *json;
extern cJSON *Array_obj1;
extern cJSON *Array_obj2;
extern cJSON *Array_obj3;
extern cJSON *Array_obj4;
extern cJSON *Array;
extern uint8_t my_re_buf[];
extern uint16_t pt;

extern void FreeRTOS_command(char Command_AT[]);
extern void FreeROTS_ESP8266_Init(void);

extern WM_HWIN	Frame0_hChild;
extern WM_HWIN	CLOCK_hChild;
WM_HWIN hItem;
char Temper[30];
char Temper1[30];
char Timer[30];
extern RTC_DateTypeDef GetData;  //获取日期结构体

extern RTC_TimeTypeDef GetTime;   //获取时间结构体
extern char botton;
extern char WeatherFlag;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId emWinGUI_taskHandle;
osThreadId touch_TaskHandle;
osThreadId ESP_TaskHandle;
osThreadId Touch_Task04Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void emWinGUI_Task(void const * argument);
void Start_LCD_Task(void const * argument);
void ESP8266_Task(void const * argument);
void TouchTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of emWinGUI_task */
  osThreadDef(emWinGUI_task, emWinGUI_Task, osPriorityNormal, 0, 512);
  emWinGUI_taskHandle = osThreadCreate(osThread(emWinGUI_task), NULL);

  /* definition and creation of touch_Task */
  osThreadDef(touch_Task, Start_LCD_Task, osPriorityIdle, 0, 512);
  touch_TaskHandle = osThreadCreate(osThread(touch_Task), NULL);

  /* definition and creation of ESP_Task */
  osThreadDef(ESP_Task, ESP8266_Task, osPriorityIdle, 0, 800);
  ESP_TaskHandle = osThreadCreate(osThread(ESP_Task), NULL);

  /* definition and creation of Touch_Task04 */
  osThreadDef(Touch_Task04, TouchTask, osPriorityIdle, 0, 512);
  Touch_Task04Handle = osThreadCreate(osThread(Touch_Task04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_emWinGUI_Task */
/**
  * @brief  Function implementing the emWinGUI_task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_emWinGUI_Task */
void emWinGUI_Task(void const * argument)
{   

  /* USER CODE BEGIN emWinGUI_Task */
	cJSON_Hooks hooks;
	hooks.malloc_fn = pvPortMalloc;
	hooks.free_fn = vPortFree;
	cJSON_InitHooks(&hooks); 
	GUI_Init();
  /* Infinite loop */
  for(;;)
  {
		MainTask();
    osDelay(10);
  }
  /* USER CODE END emWinGUI_Task */
}

/* USER CODE BEGIN Header_Start_LCD_Task */
/**
* @brief Function implementing the LCD_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LCD_Task */
void Start_LCD_Task(void const * argument)
{
  /* USER CODE BEGIN Start_LCD_Task */
  /* Infinite loop */
	//u32 x = 20, y = 20;
//	LCD_Clear(GREEN);//清屏
//	TP_Adjust();  //屏幕校准 
//	TP_Save_Adjdata();
  for(;;)
  {
//		LCD_Fill(100,100,200,200,RED);
		//TP_Scan(1);
//		GUI_DispBinAt(tp_dev.sta,0,10,8);
//		GUI_DispDecAt(tp_dev.x[0],0,20,5);
//		GUI_DispDecAt(tp_dev.y[0],0,30,5);
//		CreateMyWin();
//		while(1){
//			GUI_Delay(1);
//		GUI_TOUCH_Exec();
//			osDelay(10);
//		}
	  HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
		sprintf(Timer,"%02d:%02d:%02d",GetTime.Hours, GetTime.Minutes, GetTime.Seconds);
		
		if(botton==1)	
			TEXT_SetText(CLOCK_hChild,Timer);
		osDelay(1000);
  }
  /* USER CODE END Start_LCD_Task */
}

/* USER CODE BEGIN Header_ESP8266_Task */
/**
* @brief Function implementing the ESP_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ESP8266_Task */
void ESP8266_Task(void const * argument)
{
  /* USER CODE BEGIN ESP8266_Task */
  /* Infinite loop */
  for(;;)
  {
		if(WeatherFlag==1)
		{	
			FreeROTS_ESP8266_Init();

			FreeRTOS_command(TX_Data);		//发送指令
			osDelay(10000);
			
			json = cJSON_Parse((const char *) my_re_buf );
			Array_obj1=cJSON_GetObjectItem(json,"results");
			
			int size=cJSON_GetArraySize(Array_obj1);
	//		printf("\n%d",size);
			
			if(json == NULL)
				printf("\njson fmt error\n");
			else
			{
				Array=cJSON_GetArrayItem(Array_obj1,0);
				Array_obj2=cJSON_GetObjectItem(Array,"now");
				Array_obj3=cJSON_GetObjectItem(Array_obj2,"code");
				osDelay(1000);
				Array_obj4=cJSON_GetObjectItem(Array_obj2,"temperature");
				printf("n\r%s\n\r",Array_obj3->valuestring);
				printf("n\r%s\n\r",Array_obj4->valuestring);
				strcpy(Recive,Array_obj3->valuestring);
				strcpy(Recive2,Array_obj4->valuestring);
				cJSON_Delete(json);
				sprintf(Temper,"Today's Temperature: %s",Recive2);
				hItem = WM_GetDialogItem(Frame0_hChild, GUI_ID_USER + 0x0b);
				TEXT_SetText(hItem,Temper);
				
				memset(Recive2,0x00,sizeof(Recive2)); //清空数组
				
				if(Recive[0]==1&&(Recive[1]=='3'||Recive[1]=='4'||Recive[1]=='5'))
				{
					printf("\n天气：雨\n");
					sprintf(Temper1,"Today's Weather: RAIN");
					hItem = WM_GetDialogItem(Frame0_hChild, GUI_ID_USER + 0x0a);
					TEXT_SetText(hItem,"Today's Weather: RAIN");
				}
				
				else if(Recive[0]=='0'||Recive[0]=='1')
				{	
					printf("\n天气：晴\n");
					sprintf(Temper1,"Today's Weather: SUN");
					hItem = WM_GetDialogItem(Frame0_hChild, GUI_ID_USER + 0x0a);
					TEXT_SetText(hItem,"Today's Weather: SUN");

				}
				else if(Recive[0]=='4'||Recive[0]=='5'||Recive[0]=='6')
				{	
					printf("\n天气：多云\n");
					sprintf(Temper1,"Today's Weather: CLOUDY");
					hItem = WM_GetDialogItem(Frame0_hChild, GUI_ID_USER + 0x0a);
					TEXT_SetText(hItem,"Today's Weather: CLOUDY");

				}
				else if(Recive[0]=='9')
				{
					printf("\n天气：阴\n");
					hItem = WM_GetDialogItem(Frame0_hChild, GUI_ID_USER + 0x0a);
					sprintf(Temper1,"Today's Weather: YIN");
					TEXT_SetText(hItem,"Today's Weather: YIN");
				}
				Recive[0]='x';
				Recive[1]='x';
				WeatherFlag=0;
			}
			
			memset(my_re_buf,0x00,500);
			pt=0;
		}

//		cJSON_free(my_re_buf);

		osDelay(3500);
  }
  /* USER CODE END ESP8266_Task */
}

/* USER CODE BEGIN Header_TouchTask */
/**
* @brief Function implementing the Touch_Task04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TouchTask */
void TouchTask(void const * argument)
{
  /* USER CODE BEGIN TouchTask */
  /* Infinite loop */
  for(;;)
  {
		GUI_TOUCH_Exec();
		osDelay(10);
  }
  /* USER CODE END TouchTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
