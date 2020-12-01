/**
  ******************************************************************************
  * @file    powermanager.c
  * @author  ZhuSL
  * @brief   ��Դ����
  *
  ******************************************************************************
  * @attention
  *		None
  *
  ******************************************************************************
  */

#include "powermanager.h"
#include "main.h"



struct {
	FlagStatus EnterFlag;	/*�����λ��λ�������˯��*/
	volatile uint32_t Counter;	/*������*/
} PowerManager = {.EnterFlag = RESET, .Counter = 0};





/**
  * @brief  ��Դ����������ѭ������
  * @param  None
  * @retval None
  */
void PowerManager_Task(void)
{
	if(PowerManager.Counter >= POWERMANAGER_ENTER_TIMEOUT)
	{
		PowerManager.EnterFlag = SET;
	}



	if(PowerManager.EnterFlag == SET)
	{
		
	}
}




/**
  * @brief  ��Դ�������������
  * @param  None
  * @retval None
  */
void PowerManager_Tick_CallBack(void)
{
	PowerManager.Counter++;
}












