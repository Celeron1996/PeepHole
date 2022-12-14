/**
  ******************************************************************************
  * @file    peephole.h
  * @author  ZhuSL
  * @brief   功能整合：LCD TFT+OV摄像头+N74LVC1G125+N74LVC1G08+N74LVC245
	*	@note
	*						#关于SN74LVC1G125DBVR芯片:此芯片总共有三个可控制的逻辑引脚：
	*						OE、A、Y，其中OE和A为输入，Y为输出，功能表如下：
	*						| inputs |output|
	*						|--------|------|
  *						| OE | A |   Y  |
	*						|----|---|------| H:高电平
	*						| L  | L |   L  |	L:低电平
	*						| L  | H |   H  |	X:不关心
	*						| H  | X |   Z  |	Z:高阻抗断开状态
	*						==================================================================
	*						#关于SN74LVC245APWR芯片:该芯片作用是控制数据输送方向及其数据通断
	*						|	inputs   |  inputs/output  |
	*						|----------|-----------------|
	*						| OE | DIR |   An   |   Bn   |
	*						|----|-----|--------|--------|  H:高电平
	*						| L  |  L  | A = B  | inputs |	L:低电平
	*						| L  |  H  | inputs | B = A  |	X:不关心
	*						| H  |  X  |   Z    |   Z    |	Z:高阻抗断开状态
	*						注意：DIR固定接3.3V
	*						==================================================================
	*						#关于SN74LVC1G08DBVR芯片:
	*						| inputs |output|
	*						|--------|------|
  *						| A  | B |   Y  |
	*						|----|---|------| H:高电平
	*						| H  | H |   H  |	L:低电平
	*						| L  | X |   L  |	X:不关心
	*						| X  | L |   L  |	Z:高阻抗断开状态
	*						注意：MCU并没有连接这个芯片的任何引脚
  ******************************************************************************
  */

#ifndef _PEEPHOLE_H_
#define _PEEPHOLE_H_

#include "stm32f0xx_hal.h"


/*
SN74LVC1G125DBVR 芯片上的OE引脚
*/
#define SN74LV125_OE_GPIO_PORT						GPIOB
#define SN74LV125_OE_GPIO_PIN							GPIO_PIN_1
#define SN74LV125_OE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SN74LV125_OE_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define SN74LV125_OE_GPIO_WRITE(state)		(state == 0)?(SN74LV125_OE_GPIO_PORT->BRR = (uint32_t)SN74LV125_OE_GPIO_PIN):(SN74LV125_OE_GPIO_PORT->BSRR = (uint32_t)SN74LV125_OE_GPIO_PIN);




/*
SN74LVC245APWR 芯片上的OE引脚
*/
#define SN74LV245_OE_GPIO_PORT						GPIOB
#define SN74LV245_OE_GPIO_PIN							GPIO_PIN_7
#define SN74LV245_OE_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define SN74LV245_OE_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define SN74LV245_OE_GPIO_WRITE(state)		(state == 0)?(SN74LV245_OE_GPIO_PORT->BRR = (uint32_t)SN74LV245_OE_GPIO_PIN):(SN74LV245_OE_GPIO_PORT->BSRR = (uint32_t)SN74LV245_OE_GPIO_PIN);


/*
OV摄像头的帧同步信号
*/
#define OV_VSYNC_GPIO_PORT						GPIOA
#define OV_VSYNC_GPIO_PIN							GPIO_PIN_11
#define OV_VSYNC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define OV_VSYNC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()
#define OV_VSYNC_GPIO_WRITE(state)		(state == 0)?(OV_VSYNC_GPIO_PORT->BRR = (uint32_t)OV_VSYNC_GPIO_PIN):(OV_VSYNC_GPIO_PORT->BSRR = (uint32_t)OV_VSYNC_GPIO_PIN);
#define OV_VSYNC_GPIO_IRQn						EXTI4_15_IRQn


/*
控制摄像头、LCD、三个74芯片的电源
*/
#define POWER_GPIO_PORT						GPIOB
#define POWER_GPIO_PIN						GPIO_PIN_3
#define POWER_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define POWER_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()
#define POWER_GPIO_WRITE(state)		(state == 0)?(POWER_GPIO_PORT->BRR = (uint32_t)POWER_GPIO_PIN):(POWER_GPIO_PORT->BSRR = (uint32_t)POWER_GPIO_PIN);


/*进入低功耗模式的等待时间，单位ms*/
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

