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
//#include "ili9486.h"
#include "main.h"
#include "ov7670.h"

/*֡�жϱ�־λ������ͷÿ֡ͼ����������ǰ�˱�����λ*/
static volatile FlagStatus PEEPHOLE_FRAME_INTERRUPT_FLAG = RESET;
/*����������*/
volatile uint32_t u32PEEPHOLE_SLEEP_TICK_COUNTER = 0;
/*è�����б�־λ*/
static FlagStatus PEEPHOLE_RUN_FLAG = RESET;
/*è������ʹ�ܣ����˱�־��λ����ִ��һ��PeepHole_Run����λ*/
static volatile FunctionalState PEEPHOLE_RUN_ENABLE = DISABLE;
/*è��˯��ʹ�ܣ����˱�־��λ����ִ��һ��PeepHole_Sleep����λ*/
static volatile FunctionalState PEEPHOLE_SLEEP_ENABLE = DISABLE;


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
  HAL_NVIC_EnableIRQ(OV_VSYNC_GPIO_IRQn);

	PeepHole_EXTI_Control(DISABLE);
	PeepHole_OV_2_LCD_Control(DISABLE);
	PeepHole_LCD_WR_Control(DISABLE);
	PeepHole_Power_Control(DISABLE);
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
	static GPIO_InitTypeDef GPIO_Initure = {.Pull = GPIO_PULLUP, .Speed = GPIO_SPEED_FREQ_HIGH, .Pin = OV_VSYNC_GPIO_PIN};
	
	if(State == DISABLE)
	{
		GPIO_Initure.Mode = GPIO_MODE_INPUT;				/*����*/
	}
	else
	{
		GPIO_Initure.Mode = GPIO_MODE_IT_FALLING;		/*�ⲿ�ж�*/
	}

	HAL_GPIO_Init(OV_VSYNC_GPIO_PORT, &GPIO_Initure);		
}


/**
  * @brief  OV����ͷ֡ͬ���ź��жϻص�
  * @param  None
  * @retval None
  */
void PeepHole_OV_VSYNC_EXTI_Callback(void)
{
	PEEPHOLE_FRAME_INTERRUPT_FLAG = SET;
}



/**
  * @brief  ��������
  * @param  None
  * @retval None
  */
void PeepHole_Tick_Callback(void)
{
	if(u32PEEPHOLE_SLEEP_TICK_COUNTER)
	{
		u32PEEPHOLE_SLEEP_TICK_COUNTER--;
		if(!u32PEEPHOLE_SLEEP_TICK_COUNTER)
		{
			PEEPHOLE_SLEEP_ENABLE = ENABLE;
		}
	}
}


/**
  * @brief  ��ȡ֡�жϱ�־�Ƿ���λ
  * @param  None
  * @retval �Ƿ���λ
  *		#RESET:δ��λ
  *		#SET:��λ
  */
FlagStatus PeepHole_Get_FrameIntFlag(void)
{
	static FlagStatus temp = RESET;

	temp = PEEPHOLE_FRAME_INTERRUPT_FLAG;

	return temp;
}



/**
  * @brief  ��λ֡�жϱ�־λ
  * @param  None
  * @retval None
  */
void PeepHole_Reset_FrameIntFlag(void)
{
	PEEPHOLE_FRAME_INTERRUPT_FLAG = RESET;
}




/**
  * @brief  ��ȡ˯�߱�־
  * @param  None
  * @retval SET/RESET
  *		#SET
  *		#RESET
  */
FlagStatus PeepHole_Get_RunFlag(void)
{
	return PEEPHOLE_RUN_FLAG;
}



/**
  * @brief  ʹ�����б�־λ
  * @param  None
  * @retval None
  */
void PeepHole_Enable_Run(void)
{
	PEEPHOLE_RUN_ENABLE = ENABLE;
}


/**
  * @brief  ʹ��˯�߱�־λ
  * @param  None
  * @retval None
  */
void PeepHole_Enable_Sleep(void)
{
	PEEPHOLE_SLEEP_ENABLE = ENABLE;
}


/**
  * @brief  ����˯�߼�����
  * @param  None
  * @retval None
  */
void PeepHole_SleepCounter_Reload(void)
{
	u32PEEPHOLE_SLEEP_TICK_COUNTER = PEEPHOLE_SLEEP_ENTER_TIMEOUT;
}


/**
  * @brief  ���˯�߼���������������˯��
  * @param  None
  * @retval None
  */
void PeepHole_SleepCounter_Clear(void)
{
	u32PEEPHOLE_SLEEP_TICK_COUNTER = 0;
}

/**
  * @brief  ��è��
  * @param  None
  * @retval None
  */
void PeepHole_Run(void)
{
	PeepHole_Init();
	PeepHole_Power_Control(ENABLE);

	ILI9341_Board_Init();
	ILI9341_APP_Init();
	ILI9341_ClearScreen(ILI9341_COLOR_WHITE);		
	ILI9341_DataPort_IN();

	OV7670_Init();

	PeepHole_OV_2_LCD_Control(ENABLE);
	PeepHole_LCD_WR_Control(ENABLE);	
	PeepHole_EXTI_Control(ENABLE);			

	PEEPHOLE_RUN_FLAG = SET;
	u32PEEPHOLE_SLEEP_TICK_COUNTER = PEEPHOLE_SLEEP_ENTER_TIMEOUT;
}





/**
  * @brief  peephole sleep
  * @param  None
  * @retval None
  */
void PeepHole_Sleep(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	PeepHole_EXTI_Control(DISABLE);				
	PeepHole_LCD_WR_Control(DISABLE);	
	PeepHole_OV_2_LCD_Control(DISABLE);
	PeepHole_Power_Control(DISABLE);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = ~(GPIO_PIN_13 | GPIO_PIN_14);
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);		

	PEEPHOLE_RUN_FLAG = RESET;
	u32PEEPHOLE_SLEEP_TICK_COUNTER = 0;

	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	SystemClock_Config();

	/*��ֹ��������ȴû����Ч��ֵ���룬��ʱ˯��*/
	u32PEEPHOLE_SLEEP_TICK_COUNTER = PEEPHOLE_SLEEP_ENTER_TIMEOUT;
}




/**
  * @brief  è��Ӧ��������ѭ������
  * @param  None
  * @retval None
  */
void PeepHole_Task(void)
{
	if(PeepHole_Get_FrameIntFlag() == SET)
	{
		PeepHole_EXTI_Control(DISABLE);
		
		ILI9341_DataPort_OUT();
		
		PeepHole_LCD_WR_Control(DISABLE);
		PeepHole_OV_2_LCD_Control(DISABLE);
		
		ILI9341_Address_Set(0, 0, ILI9341_HEIGHT-1, ILI9341_WIDTH-1);
		
		ILI9341_RS_WRITE(GPIO_PIN_SET);
		ILI9341_WR_WRITE(GPIO_PIN_RESET);
		
		PeepHole_LCD_WR_Control(ENABLE);
		PeepHole_OV_2_LCD_Control(ENABLE);
		
		ILI9341_DataPort_IN();
		
		PeepHole_EXTI_Control(ENABLE);	

		PeepHole_Reset_FrameIntFlag();
	}
	if(PEEPHOLE_SLEEP_ENABLE == ENABLE)
	{
		PEEPHOLE_SLEEP_ENABLE = DISABLE;
		PeepHole_Sleep();
	}
	if(PEEPHOLE_RUN_ENABLE == ENABLE)
	{
		PEEPHOLE_RUN_ENABLE = DISABLE;
		PeepHole_Run();
	}
}





