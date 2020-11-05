/**
  ******************************************************************************
  * @file    peephole.c
  * @author  ZhuSL
  * @brief   �������ϣ�LCD TFT+OV����ͷ+N74LVC1G125+N74LVC1G08+N74LVC245
  *
  ******************************************************************************
  */
	
#include "peephole.h"
#include "ili9341.h"


/**
  * @brief  ��ʼ��PeepHole GPIO
  * @param  None
  * @retval None
  */
void PeepHole_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	SN74LV125_OE_GPIO_CLK_ENABLE();
	SN74LV245_OE_GPIO_CLK_ENABLE();
	OV_VSYNC_GPIO_CLK_ENABLE();
	POWER_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = SN74LV125_OE_GPIO_PIN;				/*pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;		/*�������*/
	GPIO_Initure.Pull = GPIO_NOPULL;						/*��������*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SN74LV125_OE_GPIO_PORT, &GPIO_Initure);
	
	GPIO_Initure.Pin = SN74LV245_OE_GPIO_PIN;				/*pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;		/*�������*/
	GPIO_Initure.Pull = GPIO_NOPULL;						/*��������*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SN74LV245_OE_GPIO_PORT, &GPIO_Initure);

	GPIO_Initure.Pin = POWER_GPIO_PIN;				/*pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;		/*�������*/
	GPIO_Initure.Pull = GPIO_NOPULL;						/*��������*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(POWER_GPIO_PORT, &GPIO_Initure);
	
	GPIO_Initure.Pin = OV_VSYNC_GPIO_PIN;				/*pin��*/
	GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;		/*�ⲿ�ж�*/
	GPIO_Initure.Pull = GPIO_PULLUP;						/*����*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(OV_VSYNC_GPIO_PORT, &GPIO_Initure);
	
  HAL_NVIC_SetPriority(OV_VSYNC_GPIO_IRQn, 2, 0);
  HAL_NVIC_DisableIRQ(OV_VSYNC_GPIO_IRQn);

	PeepHole_EXTI_Control(DISABLE);
	PeepHole_OV_2_LCD_Control(DISABLE);
	PeepHole_LCD_WR_Control(DISABLE);
	PeepHole_Power_Control(DISABLE);
}


/**
  * @brief  ����PeepHole
  * @param  None
  * @retval None
  */
void PeepHole_Run(void)
{
	
}


/**
  * @brief  ֹͣPeepHole
  * @param  None
  * @retval None
  */
void PeepHole_Stop(void)
{
	
}


/**
  * @brief  SN74LVC1G125DBVR оƬ�ϵ�OE����
  * @param  State:������ر�
	*		#ENABLE:ʹ��
	*		#DISABLE:ʧ��
	*	@note		�����ŵ͵�ƽ��Ч�����͵�ƽʱ��125оƬ��Y���ȡ����A�����ߵ�ƽʱ��YΪ���迹�Ͽ�
  * @retval None
  */
void PeepHole_LCD_WR_Control(FunctionalState State)
{	
	switch(State)
	{
		case ENABLE:
			SN74LV125_OE_GPIO_WRITE(GPIO_PIN_RESET);
			break;
		case DISABLE:
			SN74LV125_OE_GPIO_WRITE(GPIO_PIN_SET);
			break;
		default:
			break;
	}
}


/**
  * @brief  SN74LVC245APWR оƬ�ϵ�OE����
  * @param  State:������ر�
	*		#ENABLE:ʹ��
	*		#DISABLE:ʧ��
	*	@note		�����ŵ͵�ƽ��Ч�����͵�ƽʱ��LCD��data������Դ��OV�����ߵ�ƽʱ��LCD��OV�Ͽ���ֻ��MCU����
  * @retval None
  */
void PeepHole_OV_2_LCD_Control(FunctionalState State)
{	
	switch(State)
	{
		case ENABLE:
			SN74LV245_OE_GPIO_WRITE(GPIO_PIN_RESET);
			break;
		case DISABLE:
			SN74LV245_OE_GPIO_WRITE(GPIO_PIN_SET);
			break;
		default:
			break;
	}
}


/**
  * @brief  ��������ͷ��LCD������74оƬ�ĵ�Դ
  * @param  State:������ر�
	*		#ENABLE:ʹ��
	*		#DISABLE:ʧ��
  * @retval None
  */
void PeepHole_Power_Control(FunctionalState State)
{	
	switch(State)
	{
		case ENABLE:
			POWER_GPIO_WRITE(GPIO_PIN_RESET);
			break;
		case DISABLE:
			POWER_GPIO_WRITE(GPIO_PIN_SET);
			break;
		default:
			break;
	}
}


/**
  * @brief  ������ر��ж�
  * @param  State
	*		#DISABLE
	*		#ENABLE
  * @retval None
  */
void PeepHole_EXTI_Control(FunctionalState State)
{
	if(State == DISABLE)
	{
		HAL_NVIC_DisableIRQ(OV_VSYNC_GPIO_IRQn);
	}
	else
	{
		HAL_NVIC_EnableIRQ(OV_VSYNC_GPIO_IRQn);
	}
}


/**
  * @brief  OV����ͷ֡ͬ���ź��жϻص�
  * @param  None
  * @retval None
  */
void PeepHole_OV_VSYNC_EXTI_Callback(void)
{
	PeepHole_EXTI_Control(DISABLE);
	
	SN74LV125_OE_GPIO_WRITE(GPIO_PIN_SET);
	SN74LV245_OE_GPIO_WRITE(GPIO_PIN_SET);
	
	ILI9341_Address_Set(0, 0, ILI9341_WIDTH-1, ILI9341_HEIGHT-1);
	
	ILI9341_RS_WRITE(GPIO_PIN_SET);
	ILI9341_WR_WRITE(GPIO_PIN_RESET);
	
	SN74LV125_OE_GPIO_WRITE(GPIO_PIN_RESET);
	SN74LV245_OE_GPIO_WRITE(GPIO_PIN_RESET);
	
	PeepHole_EXTI_Control(ENABLE);
}


