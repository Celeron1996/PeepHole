/**
  ******************************************************************************
  * @file    sccb.c
  * @author  ZhuSL
  * @brief   sccbͨѶͷ�ļ�
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sccb.h"


static void SCCB_Delay(void);
static void SCCB_SDA_IN(void);
static void SCCB_SDA_OUT(void);


/**
  * @brief  ��ʼ��SCCB
  * @param  None
  * @retval None
  */
void SCCB_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	SCCB_SCL_GPIO_CLK_ENABLE();
	SCCB_SDA_GPIO_CLK_ENABLE();
	
	/*��ʼ��SCCB_SCL����*/
	GPIO_Initure.Pin = SCCB_SCL_GPIO_PIN;				/*SCL pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;		/*��©���*/
	GPIO_Initure.Pull = GPIO_PULLUP;						/*����*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SCCB_SCL_GPIO_PORT, &GPIO_Initure);
	
	/*��ʼ��SCCB_SDA����*/
	GPIO_Initure.Pin = SCCB_SDA_GPIO_PIN;				/*SDA pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;		/*��©���*/
	GPIO_Initure.Pull = GPIO_PULLUP;						/*����*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SCCB_SDA_GPIO_PORT, &GPIO_Initure);
}


/**
  * @brief  SCCB��ʼ�ź�
	*	@note		��ʱ��Ϊ�ߵ�ʱ���������ɸߵ��ͣ�ΪSCCB��ʼ�ź�
	*					�ڼ���״̬�£�SDA��SCL��Ϊ�͵�ƽ
  * @param  None
  * @retval None
  */
void SCCB_Start(void)
{
	SCCB_SDA_GPIO_WRITE(1);	/*�����߸ߵ�ƽ*/
	SCCB_SCL_GPIO_WRITE(1);	/*��ʱ���߸ߵ�ʱ���������ɸߵ���*/
	SCCB_Delay();
	SCCB_SDA_GPIO_WRITE(0);
	SCCB_Delay();
	SCCB_SCL_GPIO_WRITE(0);	/*�����߻ָ����͵�ƽ��������������Ҫ*/
}


/**
  * @brief  SCCBֹͣ�ź�
	*	@note		��ʱ��Ϊ�ߵ�ʱ���������ɵ͵��ߣ�ΪSCCBֹͣ�ź�
	*					����״̬�£�SDA��SCL��Ϊ�ߵ�ƽ
  * @param  None
  * @retval None
  */
void SCCB_Stop(void)
{
	SCCB_SDA_GPIO_WRITE(0);
	SCCB_Delay();
	SCCB_SCL_GPIO_WRITE(1);
	SCCB_Delay();
	SCCB_SDA_GPIO_WRITE(1);
	SCCB_Delay();
}


/**
  * @brief  ����NA�ź�
  * @param  None
  * @retval None
  */
void SCCB_No_Ack(void)
{
	SCCB_Delay();
	SCCB_SDA_GPIO_WRITE(1);	
	SCCB_SCL_GPIO_WRITE(1);	
	SCCB_Delay();
	SCCB_SCL_GPIO_WRITE(0);	
	SCCB_Delay();
	SCCB_SDA_GPIO_WRITE(0);	
	SCCB_Delay();	
}


/**
  * @brief  SCCB,д��һ���ֽ�
  * @param  Data��д���λ������
  * @retval	�ɹ���ʧ��
	*		#SCCB_True���ɹ�
	*		#SCCB_False��ʧ��
  */
SCCB_BoolTypeDef SCCB_WR_Byte(uint8_t Data)
{
	uint8_t j;
	SCCB_BoolTypeDef res;
	
	for(j=0; j<8; j++)
	{
		if(Data&0x80)
		{
			SCCB_SDA_GPIO_WRITE(1);
		}
		else
		{
			SCCB_SDA_GPIO_WRITE(0);
		}
		Data<<=1;
		SCCB_Delay();
		SCCB_SCL_GPIO_WRITE(1);	
		SCCB_Delay();
		SCCB_SCL_GPIO_WRITE(0);		   
	}
	SCCB_SDA_IN();	/*����SDAΪ���� */
	SCCB_Delay();
	SCCB_SCL_GPIO_WRITE(1);	/*���յھ�λ,���ж��Ƿ��ͳɹ�*/
	SCCB_Delay();
	if(SCCB_SDA_GPIO_READ)
	{
		res = SCCB_False;
	}
	else
	{
		res = SCCB_True;
	}
	SCCB_SCL_GPIO_WRITE(0);		 
	SCCB_SDA_OUT();	/*����SDAΪ���*/
	return res;  
}


/**
  * @brief  SCCB ��ȡһ���ֽ�,��SCL��������,��������
  * @param  None
  * @retval	���ذ�λ��ȡ��������
  */
uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp = 0, j;    
	SCCB_SDA_IN();	/*����SDAΪ����*/
	for(j=8; j>0; j--)	/*ѭ��8�ν�������*/
	{		     	  
		SCCB_Delay();
		SCCB_SCL_GPIO_WRITE(1);
		temp=temp<<1;
		if(SCCB_SDA_GPIO_READ)temp++;   
		SCCB_Delay();
		SCCB_SCL_GPIO_WRITE(0);
	}
	
	SCCB_SDA_OUT();	/*����SDAΪ���*/
	
	return temp;
}


/**
  * @brief  ��ʱ
  * @param  None
  * @retval None
	*	@note		IIC��ʱ������ʵ�ʲ���ԼΪ12us
  */
static void SCCB_Delay(void)
{
	volatile uint8_t i;
	
	for(i=0;i<50;i++);	
}


static void SCCB_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	SCCB_SDA_GPIO_CLK_ENABLE();
	
	/*��ʼ��SCCB_SDA����*/
	GPIO_Initure.Pin = SCCB_SDA_GPIO_PIN;				/*SDA pin��*/
	GPIO_Initure.Mode = GPIO_MODE_INPUT;				/*����*/
	GPIO_Initure.Pull = GPIO_NOPULL;						/*����*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SCCB_SDA_GPIO_PORT, &GPIO_Initure);		
}


static void SCCB_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	SCCB_SDA_GPIO_CLK_ENABLE();
	
	/*��ʼ��SCCB_SDA����*/
	GPIO_Initure.Pin = SCCB_SDA_GPIO_PIN;				/*SDA pin��*/
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD;		/*��©���*/
	GPIO_Initure.Pull = GPIO_PULLUP;						/*����*/
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;	/*����*/
	HAL_GPIO_Init(SCCB_SDA_GPIO_PORT, &GPIO_Initure);	
}





