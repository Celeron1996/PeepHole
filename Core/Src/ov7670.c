/**
  ******************************************************************************
  * @file    ov7670.c
  * @author  ZhuSL
  * @brief   OV7670摄像头驱动
  *
  ******************************************************************************
  */

#include "ov7670.h"
#include "sccb.h"


static void OV7670_DelayMs(uint16_t Ms);
//static void OV7670_Delay(void);

static const uint8_t OV7670_REG_INIT_TABLE[][2] =
{
	/*  {0x12, 0x46},*/
	{0x3a, 0x04},
	{0x40, 0xd0},
	{0x12, 0x14},
	{0x32, 0x80},
	{0x17, 0x16},
	{0x18, 0x04},
	{0x19, 0x02},
	{0x1a, 0x7b},//0x7a,
	{0x03, 0x06},//0x0a,
	{0x0c, 0x00},
	{0x3e, 0x00},//
	{0x70, 0x00},
	{0x71, 0x00},
	{0x72, 0x11},
	{0x73, 0x00},//
	{0xa2, 0x02},
	{0x11, 0x01},
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},
	{0x7d, 0x3c},
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},
	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},
	{0x87, 0xc4},
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	{0x00, 0x00},//AGC
	{0x10, 0x00},
	{0x0d, 0x00},
	{0x14, 0x20},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},
	{0x24, 0x75},
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},
	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},
	{0xaa, 0x94},
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
	{0x1e, 0x37},//0x07,
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
	{0x35, 0x0b},
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},//
	{0x3c, 0x78},
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x0c},///////////////////////
	{0x6b, 0x60},//PLL
	{0x74, 0x19},
	{0x8d, 0x4f},
	{0x8e, 0x00},
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
	{0xb3, 0x82},
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
	{0x5b, 0x44},
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},
	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},
	{0x6e, 0x11},
	{0x6f, 0x9f},//0x9e for advance AWB
	{0x6a, 0x40},
	{0x01, 0x40},
	{0x02, 0x40},
	{0x13, 0xe7},
	{0x15, 0x00},
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
	{0x58, 0x9e},	
	{0x41, 0x08},
	{0x3f, 0x00},
	{0x75, 0x05},
	{0x76, 0xe1},
	{0x4c, 0x00},
	{0x77, 0x01},
	{0x3d, 0xc2},	//0xc0,
	{0x4b, 0x09},
	{0xc9, 0x60},
	{0x41, 0x38},
	{0x56, 0x40},//0x40,  change according to Jim's request	
	{0x34, 0x11},
	{0x3b, 0x02},//0x00,//0x02,
	{0xa4, 0x89},//0x88,
	{0x96, 0x00},
	{0x97, 0x30},
	{0x98, 0x20},
	{0x99, 0x30},
	{0x9a, 0x84},
	{0x9b, 0x29},
	{0x9c, 0x03},
	{0x9d, 0x4c},
	{0x9e, 0x3f},
	{0x78, 0x04},	
	{0x79, 0x01},
	{0xc8, 0xf0},
	{0x79, 0x0f},
	{0xc8, 0x00},
	{0x79, 0x10},
	{0xc8, 0x7e},
	{0x79, 0x0a},
	{0xc8, 0x80},
	{0x79, 0x0b},
	{0xc8, 0x01},
	{0x79, 0x0c},
	{0xc8, 0x0f},
	{0x79, 0x0d},
	{0xc8, 0x20},
	{0x79, 0x09},
	{0xc8, 0x80},
	{0x79, 0x02},
	{0xc8, 0xc0},
	{0x79, 0x03},
	{0xc8, 0x40},
	{0x79, 0x05},
	{0xc8, 0x30},
	{0x79, 0x26},
	{0x09, 0x03},
	{0x55, 0x00},
	{0x56, 0x40},	
	{0x3b, 0x42},//0x82,//0xc0,//0xc2,	//night mode
};


/**
  * @brief  初始化OV7670
  * @param  None
  * @retval	返回成功或失败
	*		#OV7670_False：失败
	*		#OV7670_True：成功
  */
OV7670_BoolTypeDef OV7670_Init(void)
{
	uint16_t i;
	
	SCCB_Init();
	
	if(OV7670_WR_Reg(0x12, 0x80) == OV7670_False)
	{
		return OV7670_False;
	}
	
	OV7670_DelayMs(10);
	
	for(i = 0; i < sizeof(OV7670_REG_INIT_TABLE)/sizeof(OV7670_REG_INIT_TABLE[0]); i++)
	{
		if(OV7670_WR_Reg(OV7670_REG_INIT_TABLE[i][0], OV7670_REG_INIT_TABLE[i][1]) == OV7670_False)
			return OV7670_False;
	}
	
	return OV7670_True;
}


/**
  * @brief  OV7670寄存器
  * @param  RegAddr：寄存器地址
	*	@param	RegData：寄存器数据
  * @retval	返回成功或失败
	*		#OV7670_False：失败
	*		#OV7670_True：成功
  */
OV7670_BoolTypeDef OV7670_WR_Reg(uint8_t RegAddr, uint8_t RegData)
{
	SCCB_Start();
	if(SCCB_WR_Byte(OV7670_SCCB_ADDRESS) == SCCB_False)
	{
		SCCB_Stop();
		return OV7670_False;
	}
	//OV7670_Delay();
	if(SCCB_WR_Byte(RegAddr) == SCCB_False)
	{
		SCCB_Stop();
		return OV7670_False;
	}
	//OV7670_Delay();
	if(SCCB_WR_Byte(RegData) == SCCB_False)
	{
		SCCB_Stop();
		return OV7670_False;
	}
	SCCB_Stop();
	return OV7670_True;
}


/**
  * @brief  OV7670的毫秒延时
  * @param  Ms：延时参数
  * @retval None
  */
static void OV7670_DelayMs(uint16_t Ms)
{
	HAL_Delay(Ms);
}


///**
//  * @brief  延时
//  * @param  None
//  * @retval None
//	*	@note		IIC延时函数，实际测试约为6us
//  */
//static void OV7670_Delay(void)
//{
//	volatile uint16_t i;
//	
//	for(i=0;i<500;i++);	
//}

