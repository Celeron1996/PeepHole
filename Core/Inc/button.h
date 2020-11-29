/**
  ******************************************************************************
  * @file    button.h
  * @author  ZhuSL
  * @brief   ����Ӧ��
  *
  ******************************************************************************
  * @attention
  *		None
  *
  ******************************************************************************
  */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "stm32f0xx_hal.h"


#define BUTTON_USER_GPIO_PORT						GPIOB
#define BUTTON_USER_GPIO_PIN						GPIO_PIN_4
#define BUTTON_USER_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()  
#define BUTTON_USER_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()
#define BUTTON_USER_GPIO_IRQn						EXTI4_15_IRQn

#define BUTTON_MCU_GPIO_PORT						GPIOB
#define BUTTON_MCU_GPIO_PIN							GPIO_PIN_5
#define BUTTON_MCU_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()  
#define BUTTON_MCU_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define BUTTON_MCU_GPIO_IRQn						EXTI4_15_IRQn

/*�������ڣ���λms*/
#define BUTTON_TICK_PERIOD_VALUE	(20u)
/*����ɨ��ʱ��������ֵ���������ʱ��Ϊ�̰�����λΪBUTTON_TICK_PERIOD_VALUE*/
#define BUTTON_PRESS_MAX_VALUE		(25u)
/*����ɨ��ʱ��������ֵ�������ʱ��Ϊ��������λΪBUTTON_TICK_PERIOD_VALUE*/
#define BUTTON_PRESS_HOLD_MIN_VALUE		(50u)



/*������������*/
typedef enum
{
	Button_Null,					/*��*/
	Button_Press,					/*�̰�*/
	Button_Press_Hold			/*����*/
} ButtonStatus_TypeDef;


/*�������*/
typedef struct
{
	volatile ButtonStatus_TypeDef Status;	/*������״̬*/
	volatile FlagStatus ScanFlag;					/*�Ƿ�ɨ���־λ*/
	volatile uint16_t Counter;
} ButtonHandler_TypeDef;









void Button_Init(void);
void Button_Tick_CallBack(void);
void Button_EXTI_Callback(uint16_t GPIO_Pin);
void Button_Scan_CallBack(void);
ButtonStatus_TypeDef Button_GetStatus(void);
void Button_Task(void);




#endif

