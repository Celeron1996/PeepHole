/**
  ******************************************************************************
  * @file    ili9341.h
  * @author  ZhuSL
  * @brief   ili9341 driver
  *
  ******************************************************************************
  * @attention
  *		None
  *
  ******************************************************************************
  */
	
#ifndef _ILI9341_H_
#define _ILI9341_H_

#include "stm32f0xx_hal.h"


#define ILI9341_USER_16_BIT_DATA_ (0)
#define ILI9341_WIDTH		(240)
#define ILI9341_HEIGHT	(320)


typedef enum
{
	ILI9341_COLOR_WHITE		= 0xFFFF,
	ILI9341_COLOR_BLACK		= 0x0000,
	ILI9341_COLOR_BLUE		= 0x001F,  
	ILI9341_COLOR_BRED		= 0XF81F,
	ILI9341_COLOR_GRED		= 0XFFE0,
	ILI9341_COLOR_GBLUE		= 0X07FF,
	ILI9341_COLOR_RED			= 0xF800,
	ILI9341_COLOR_MAGENTA	= 0xF81F,
	ILI9341_COLOR_GREEN		= 0x07E0,
	ILI9341_COLOR_CYAN		= 0x7FFF,
	ILI9341_COLOR_YELLOW	= 0xFFE0,
	ILI9341_COLOR_BROWN		= 0XBC40,
	ILI9341_COLOR_BRRED		= 0XFC07,
	ILI9341_COLOR_GRAY		= 0X8430	
} ILI9341_COLOR_TypeDef;



#define ILI9341_RS_GPIO_PORT					GPIOB
#define ILI9341_RS_GPIO_PIN						GPIO_PIN_6
#define ILI9341_RS_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()  
#define ILI9341_RS_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()

#define ILI9341_WR_GPIO_PORT					GPIOB
#define ILI9341_WR_GPIO_PIN						GPIO_PIN_0
#define ILI9341_WR_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()  
#define ILI9341_WR_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOB_CLK_DISABLE()

#define ILI9341_RD_GPIO_PORT					GPIOF
#define ILI9341_RD_GPIO_PIN						GPIO_PIN_0
#define ILI9341_RD_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOF_CLK_ENABLE()  
#define ILI9341_RD_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOF_CLK_DISABLE()

#define ILI9341_CS_GPIO_PORT					GPIOF
#define ILI9341_CS_GPIO_PIN						GPIO_PIN_1
#define ILI9341_CS_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOF_CLK_ENABLE()  
#define ILI9341_CS_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOF_CLK_DISABLE()

#define ILI9341_REST_GPIO_PORT					GPIOA
#define ILI9341_REST_GPIO_PIN						GPIO_PIN_8
#define ILI9341_REST_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_REST_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()


#if (ILI9341_USER_16_BIT_DATA_ > 0)

#define ILI9341_DB0_GPIO_PORT					GPIOA
#define ILI9341_DB0_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB0_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB0_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB1_GPIO_PORT					GPIOA
#define ILI9341_DB1_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB1_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB1_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB2_GPIO_PORT					GPIOA
#define ILI9341_DB2_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB2_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB2_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB3_GPIO_PORT					GPIOA
#define ILI9341_DB3_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB3_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB3_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB4_GPIO_PORT					GPIOA
#define ILI9341_DB4_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB4_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB4_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB5_GPIO_PORT					GPIOA
#define ILI9341_DB5_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB5_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB5_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB6_GPIO_PORT					GPIOA
#define ILI9341_DB6_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB6_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB6_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB7_GPIO_PORT					GPIOA
#define ILI9341_DB7_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB7_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB7_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#endif

#define ILI9341_DB8_GPIO_PORT					GPIOA
#define ILI9341_DB8_GPIO_PIN						GPIO_PIN_0
#define ILI9341_DB8_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB8_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB9_GPIO_PORT					GPIOA
#define ILI9341_DB9_GPIO_PIN						GPIO_PIN_1
#define ILI9341_DB9_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB9_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB10_GPIO_PORT					GPIOA
#define ILI9341_DB10_GPIO_PIN						GPIO_PIN_2
#define ILI9341_DB10_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB10_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB11_GPIO_PORT					GPIOA
#define ILI9341_DB11_GPIO_PIN						GPIO_PIN_3
#define ILI9341_DB11_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB11_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB12_GPIO_PORT					GPIOA
#define ILI9341_DB12_GPIO_PIN						GPIO_PIN_4
#define ILI9341_DB12_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB12_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB13_GPIO_PORT					GPIOA
#define ILI9341_DB13_GPIO_PIN						GPIO_PIN_5
#define ILI9341_DB13_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB13_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB14_GPIO_PORT					GPIOA
#define ILI9341_DB14_GPIO_PIN						GPIO_PIN_6
#define ILI9341_DB14_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB14_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()

#define ILI9341_DB15_GPIO_PORT					GPIOA
#define ILI9341_DB15_GPIO_PIN						GPIO_PIN_7
#define ILI9341_DB15_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()  
#define ILI9341_DB15_GPIO_CLK_DISABLE()	__HAL_RCC_GPIOA_CLK_DISABLE()


#if (ILI9341_USER_16_BIT_DATA_ > 0)

#define ILI9341_16_BIT_DATA_WRITE(data)	do{ } while(0)

#else

//#define ILI9341_8_BIT_DATA_WRITE(data)	do{ GPIOB->ODR &= 0x00FF; GPIOB->ODR |= (((uint16_t)data) << 8);} while(0)

#define ILI9341_8_BIT_DATA_WRITE(data)	do{ \
HAL_GPIO_WritePin(ILI9341_DB8_GPIO_PORT, ILI9341_DB8_GPIO_PIN, (GPIO_PinState)(data&0x01));\
HAL_GPIO_WritePin(ILI9341_DB9_GPIO_PORT, ILI9341_DB9_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 1)));\
HAL_GPIO_WritePin(ILI9341_DB10_GPIO_PORT, ILI9341_DB10_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 2)));\
HAL_GPIO_WritePin(ILI9341_DB11_GPIO_PORT, ILI9341_DB11_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 3)));\
HAL_GPIO_WritePin(ILI9341_DB12_GPIO_PORT, ILI9341_DB12_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 4)));\
HAL_GPIO_WritePin(ILI9341_DB13_GPIO_PORT, ILI9341_DB13_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 5)));\
HAL_GPIO_WritePin(ILI9341_DB14_GPIO_PORT, ILI9341_DB14_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 6)));\
HAL_GPIO_WritePin(ILI9341_DB15_GPIO_PORT, ILI9341_DB15_GPIO_PIN, (GPIO_PinState)(data&(0x01 << 7)));\
} while(0)

#endif

#define ILI9341_RS_WRITE(PinState)					HAL_GPIO_WritePin(ILI9341_RS_GPIO_PORT, ILI9341_RS_GPIO_PIN, PinState)
#define ILI9341_WR_WRITE(PinState)					HAL_GPIO_WritePin(ILI9341_WR_GPIO_PORT, ILI9341_WR_GPIO_PIN, PinState)
#define ILI9341_RD_WRITE(PinState)					HAL_GPIO_WritePin(ILI9341_RD_GPIO_PORT, ILI9341_RD_GPIO_PIN, PinState)
#define ILI9341_CS_WRITE(PinState)					HAL_GPIO_WritePin(ILI9341_CS_GPIO_PORT, ILI9341_CS_GPIO_PIN, PinState)
#define ILI9341_REST_WRITE(PinState)				HAL_GPIO_WritePin(ILI9341_REST_GPIO_PORT, ILI9341_REST_GPIO_PIN, PinState)



void ILI9341_Board_Init(void);
void ILI9341_APP_Init(void);
void ILI9341_ClearScreen(uint16_t Color);


#endif
