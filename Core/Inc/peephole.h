/**
  ******************************************************************************
  * @file    peephole.h
  * @author  ZhuSL
  * @brief   �������ϣ�LCD TFT+OV����ͷ+N74LVC1G125+N74LVC1G08+N74LVC245
	*	@note
	*						#����SN74LVC1G125DBVRоƬ:��оƬ�ܹ��������ɿ��Ƶ��߼����ţ�
	*						OE��A��Y������OE��AΪ���룬YΪ��������ܱ����£�
	*						| inputs |output|
	*						|--------|------|
  *						| OE | A |   Y  |
	*						|----|---|------| H:�ߵ�ƽ
	*						| L  | L |   L  |	L:�͵�ƽ
	*						| L  | H |   H  |	X:������
	*						| H  | X |   Z  |	Z:���迹�Ͽ�״̬
	*						==================================================================
	*						#����SN74LVC245APWRоƬ:��оƬ�����ǿ����������ͷ���������ͨ��
	*						|	inputs   |  inputs/output  |
	*						|----------|-----------------|
	*						| OE | DIR |   An   |   Bn   |
	*						|----|-----|--------|--------|  H:�ߵ�ƽ
	*						| L  |  L  | A = B  | inputs |	L:�͵�ƽ
	*						| L  |  H  | inputs | B = A  |	X:������
	*						| H  |  X  |   Z    |   Z    |	Z:���迹�Ͽ�״̬
	*						ע�⣺DIR�̶���3.3V
	*						==================================================================
	*						#����SN74LVC1G08DBVRоƬ:
	*						| inputs |output|
	*						|--------|------|
  *						| A  | B |   Y  |
	*						|----|---|------| H:�ߵ�ƽ
	*						| H  | H |   H  |	L:�͵�ƽ
	*						| L  | X |   L  |	X:������
	*						| X  | L |   L  |	Z:���迹�Ͽ�״̬
	*						ע�⣺MCU��û���������оƬ���κ�����
  ******************************************************************************
  */

#ifndef _PEEPHOLE_H_
#define _PEEPHOLE_H_

#include "stm32f0xx_hal.h"


/*
SN74LVC1G125DBVR оƬ�ϵ�OE����
*/
#define SN74LV125_OE_GPIO_PORT						GPIOB
#define SN74LV125_OE_GPIO_PIN							GPIO_PIN_1
#define SN74LV125_OE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SN74LV125_OE_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define SN74LV125_OE_GPIO_WRITE(state)		(state == 0)?(SN74LV125_OE_GPIO_PORT->BRR = (uint32_t)SN74LV125_OE_GPIO_PIN):(SN74LV125_OE_GPIO_PORT->BSRR = (uint32_t)SN74LV125_OE_GPIO_PIN);




/*
SN74LVC245APWR оƬ�ϵ�OE����
*/
#define SN74LV245_OE_GPIO_PORT						GPIOB
#define SN74LV245_OE_GPIO_PIN							GPIO_PIN_7
#define SN74LV245_OE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SN74LV245_OE_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define SN74LV245_OE_GPIO_WRITE(state)		(state == 0)?(SN74LV245_OE_GPIO_PORT->BRR = (uint32_t)SN74LV245_OE_GPIO_PIN):(SN74LV245_OE_GPIO_PORT->BSRR = (uint32_t)SN74LV245_OE_GPIO_PIN);


/*
OV����ͷ��֡ͬ���ź�
*/
#define OV_VSYNC_GPIO_PORT						GPIOA
#define OV_VSYNC_GPIO_PIN							GPIO_PIN_11
#define OV_VSYNC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define OV_VSYNC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()
#define OV_VSYNC_GPIO_WRITE(state)		(state == 0)?(OV_VSYNC_GPIO_PORT->BRR = (uint32_t)OV_VSYNC_GPIO_PIN):(OV_VSYNC_GPIO_PORT->BSRR = (uint32_t)OV_VSYNC_GPIO_PIN);
#define OV_VSYNC_GPIO_IRQn						EXTI4_15_IRQn


/*
��������ͷ��LCD������74оƬ�ĵ�Դ
*/
#define POWER_GPIO_PORT						GPIOB
#define POWER_GPIO_PIN						GPIO_PIN_3
#define POWER_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define POWER_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()
#define POWER_GPIO_WRITE(state)		(state == 0)?(POWER_GPIO_PORT->BRR = (uint32_t)POWER_GPIO_PIN):(POWER_GPIO_PORT->BSRR = (uint32_t)POWER_GPIO_PIN);


/*����͹���ģʽ�ĵȴ�ʱ�䣬��λms*/
#define PEEPHOLE_SLEEP_ENTER_TIMEOUT (10000U)


void PeepHole_Init(void);
void PeepHole_LCD_WR_Control(FunctionalState State);
void PeepHole_OV_2_LCD_Control(FunctionalState State);
void PeepHole_Power_Control(FunctionalState State);
void PeepHole_EXTI_Control(FunctionalState State);
void PeepHole_OV_VSYNC_EXTI_Callback(void);
FlagStatus PeepHole_Get_FrameIntFlag(void);
void PeepHole_Reset_FrameIntFlag(void);
void PeepHole_Sleep(void);
void PeepHole_Run(void);
void PeepHole_SleepCounter_Clear(void);
void PeepHole_SleepCounter_Reload(void);
void PeepHole_Enable_Sleep(void);
void PeepHole_Enable_Run(void);
FlagStatus PeepHole_Get_RunFlag(void);
void PeepHole_Tick_Callback(void);
void PeepHole_Task(void);


#endif

