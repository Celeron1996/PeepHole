/**
  ******************************************************************************
  * @file    ov7670.h
  * @author  ZhuSL
  * @brief   OV7670����ͷ����
  *
  ******************************************************************************
  */

#ifndef _OV7670_H_
#define _OV7670_H_

#include "stm32f0xx_hal.h"


#define OV7670_SCCB_ADDRESS	(0x42)	/*OV7670 SCCB ��ַ*/


typedef enum
{
	OV7670_False = 0U,
	OV7670_True = !OV7670_False
} OV7670_BoolTypeDef;


typedef enum
{
	OV7670Reg_AGC = 0x00,
	OV7670Reg_BLUE = 0x01,
	OV7670Reg_RED = 0x02,
	OV7670Reg_VREF = 0x03,
	OV7670Reg_COM1 = 0x04,
	OV7670Reg_BAVE = 0x05,
	OV7670Reg_GbAVE = 0x06,
	OV7670Reg_AECHH = 0x07,
	OV7670Reg_RAVE = 0x08,
	OV7670Reg_COM2 = 0x09,
	OV7670Reg_PID = 0x0A,
	OV7670Reg_VER = 0x0B,
	OV7670Reg_COM3 = 0x0C,
	OV7670Reg_COM4 = 0x0D,
	OV7670Reg_COM5 = 0x0E,
	OV7670Reg_COM6 = 0x0F,
	OV7670Reg_AECH = 0x10,
	OV7670Reg_CLKRC = 0x11,
	OV7670Reg_COM7 = 0x12,
	OV7670Reg_COM8 = 0x13,
	OV7670Reg_COM9 = 0x14,
	OV7670Reg_COM10 = 0x15,
	OV7670Reg_RSVD0 = 0x16,
	OV7670Reg_HSTART = 0x17,
	OV7670Reg_HSTOP = 0x18,
	OV7670Reg_VSTRT = 0x19,
	OV7670Reg_VSTOP = 0x1A,
	OV7670Reg_PSHFT = 0x1B,
	OV7670Reg_MIDH = 0x1C,
	OV7670Reg_MIDL = 0x1D,
	OV7670Reg_MVFP = 0x1E,
	OV7670Reg_LAEC = 0x1F,
	OV7670Reg_ADCCTR0 = 0x20,
	OV7670Reg_ADCCTR1 = 0x21,
	OV7670Reg_ADCCTR2 = 0x22,
	OV7670Reg_ADCCTR3 = 0x23,
	OV7670Reg_AEW = 0x24,
	OV7670Reg_AEB = 0x25,
	OV7670Reg_VPT = 0x26,
	OV7670Reg_BBIAS = 0x27,
	OV7670Reg_GbBIAS = 0x28,
	OV7670Reg_RSVD1 = 0x29,
	OV7670Reg_EXHCH = 0x2A,
	OV7670Reg_EXHCL = 0x2B,
	OV7670Reg_RBIAS = 0x2C,
	OV7670Reg_ADVFL = 0x2D,
	OV7670Reg_ADVFH = 0x2E,
	OV7670Reg_YAVE = 0x2F,
	OV7670Reg_HSYST = 0x30,
	OV7670Reg_HSYEN = 0x31,
	OV7670Reg_HREF = 0x32,
	OV7670Reg_CHLF = 0x33,
	OV7670Reg_ARBLM = 0x34,
	OV7670Reg_RSVD33 = 0x35,
	OV7670Reg_RSVD34 = 0x36,
	OV7670Reg_ADC = 0x37,
	OV7670Reg_ACOM = 0x38,
	OV7670Reg_OFON = 0x39,
	OV7670Reg_TSLB = 0x3A,
	OV7670Reg_COM11 = 0x3B,
	OV7670Reg_COM12 = 0x3C,
	OV7670Reg_COM13 = 0x3D,
	OV7670Reg_COM14 = 0x3E,
	OV7670Reg_EDGE = 0x3F,
	OV7670Reg_COM15 = 0x40,
	OV7670Reg_COM16 = 0x41,
	OV7670Reg_COM17 = 0x42,
	OV7670Reg_AWBC1 = 0x43,
	OV7670Reg_AWBC2 = 0x44,
	OV7670Reg_AWBC3 = 0x45,
	OV7670Reg_AWBC4 = 0x46,
	OV7670Reg_AWBC5 = 0x47,
	OV7670Reg_AWBC6 = 0x48,
	OV7670Reg_RSVD2 = 0x49,
	OV7670Reg_RSVD3 = 0x4A,
	OV7670Reg_REG4B = 0x4B,
	OV7670Reg_DNSTH = 0x4C,
	OV7670Reg_RSVD4 = 0x4D,
	OV7670Reg_RSVD5 = 0x4E,
	OV7670Reg_MTX1 = 0x4F,
	OV7670Reg_MTX2 = 0x50,
	OV7670Reg_MTX3 = 0x51,
	OV7670Reg_MTX4 = 0x52,
	OV7670Reg_MTX5 = 0x53,
	OV7670Reg_MTX6 = 0x54,
	OV7670Reg_BRIGHT = 0x55,
	OV7670Reg_CONTRAS = 0x56,
	OV7670Reg_CONTRAS_CENTER = 0x57,
	OV7670Reg_MTXS = 0x58,
	OV7670Reg_RSVD6 = 0x59,
	OV7670Reg_RSVD7 = 0x5A,
	OV7670Reg_RSVD8 = 0x5B,
	OV7670Reg_RSVD9 = 0x5C,
	OV7670Reg_RSVDA = 0x5D,
	OV7670Reg_RSVDB = 0x5E,
	OV7670Reg_RSVDC = 0x5F,
	OV7670Reg_RSVDD = 0x60,
	OV7670Reg_RSVDE = 0x61,
	OV7670Reg_LCC1 = 0x62,
	OV7670Reg_LCC2 = 0x63,
	OV7670Reg_LCC3 = 0x64,
	OV7670Reg_LCC4 = 0x65,
	OV7670Reg_LCC5 = 0x66,
	OV7670Reg_MANU = 0x67,
	OV7670Reg_MANV = 0x68,
	OV7670Reg_GFIX = 0x69,
	OV7670Reg_GGAIN = 0x6A,
	OV7670Reg_DBLV = 0x6B,
	OV7670Reg_AWBCTR3 = 0x6C,
	OV7670Reg_AWBCTR2 = 0x6D,
	OV7670Reg_AWBCTR1 = 0x6E,
	OV7670Reg_AWBCTR0 = 0x6F,
	OV7670Reg_SCALING_XSC = 0x70,
	OV7670Reg_SCALING_YSC = 0x71,
	OV7670Reg_SCALING_DCWCTR = 0x72,
	OV7670Reg_SCALING_PC = 0x73,
	OV7670Reg_REG74 = 0x74,
	OV7670Reg_REG75 = 0x75,
	OV7670Reg_REG76 = 0x76,
	OV7670Reg_REG77 = 0x77,
	OV7670Reg_RSVDF = 0x78,
	OV7670Reg_RSVD10 = 0x79,
	OV7670Reg_SLOP = 0x7A,
	OV7670Reg_GAM1 = 0x7B,
	OV7670Reg_GAM2 = 0x7C,
	OV7670Reg_GAM3 = 0x7D,
	OV7670Reg_GAM4 = 0x7E,
	OV7670Reg_GAM5 = 0x7F,
	OV7670Reg_GAM6 = 0x80,
	OV7670Reg_GAM7 = 0x81,
	OV7670Reg_GAM8 = 0x82,
	OV7670Reg_GAM9 = 0x83,
	OV7670Reg_GAM10 = 0x84,
	OV7670Reg_GAM11 = 0x85,
	OV7670Reg_GAM12 = 0x86,
	OV7670Reg_GAM13 = 0x87,
	OV7670Reg_GAM14 = 0x88,
	OV7670Reg_GAM15 = 0x89,
	OV7670Reg_RSVD11 = 0x8A,
	OV7670Reg_RSVD12 = 0x8B,
	OV7670Reg_RGB444 = 0x8C,
	OV7670Reg_RSVD13 = 0x8D,
	OV7670Reg_RSVD14 = 0x8E,
	OV7670Reg_RSVD15 = 0x8F,
	OV7670Reg_RSVD16 = 0x90,
	OV7670Reg_RSVD17 = 0x91,
	OV7670Reg_DM_LNL = 0x92,
	OV7670Reg_DM_LNH = 0x93,
	OV7670Reg_LCC6 = 0x94,
	OV7670Reg_LCC7 = 0x95,
	OV7670Reg_RSVD18 = 0x96,
	OV7670Reg_RSVD19 = 0x97,
	OV7670Reg_RSVD1A = 0x98,
	OV7670Reg_RSVD1B = 0x99,
	OV7670Reg_RSVD1C = 0x9A,
	OV7670Reg_RSVD1D = 0x9B,
	OV7670Reg_RSVD1E = 0x9C,
	OV7670Reg_BD50ST = 0x9D,
	OV7670Reg_BD60ST = 0x9E,
	OV7670Reg_HAECC1 = 0x9F,
	OV7670Reg_HAECC2 = 0xA0,
	OV7670Reg_RSVD1F = 0xA1,
	OV7670Reg_SCALING_PCLK_DELAY = 0xA2,
	OV7670Reg_RSVD20 = 0xA3,
	OV7670Reg_NT_CTRL = 0xA4,
	OV7670Reg_BD50MAX = 0xA5,
	OV7670Reg_HAECC3 = 0xA6,
	OV7670Reg_HAECC4 = 0xA7,
	OV7670Reg_HAECC5 = 0xA8,
	OV7670Reg_HAECC6 = 0xA9,
	OV7670Reg_HAECC7 = 0xAA,
	OV7670Reg_BD60MAX = 0xAB,
	OV7670Reg_STR_OPT = 0xAC,
	OV7670Reg_STR_R = 0xAD,
	OV7670Reg_STR_G = 0xAE,
	OV7670Reg_STR_B = 0xAF,
	OV7670Reg_RSVD21 = 0xB0,
	OV7670Reg_ABLC1 = 0xB1,
	OV7670Reg_RSVD22 = 0xB2,
	OV7670Reg_THL_DLT0 = 0xB3,
	OV7670Reg_RSVD23 = 0xB4,
	OV7670Reg_THL_DLT1 = 0xB5,
	OV7670Reg_RSVD24 = 0xB6,
	OV7670Reg_RSVD25 = 0xB7,
	OV7670Reg_RSVD26 = 0xB8,
	OV7670Reg_RSVD27 = 0xB9,
	OV7670Reg_RSVD28 = 0xBA,
	OV7670Reg_RSVD29 = 0xBB,
	OV7670Reg_RSVD2A = 0xBC,
	OV7670Reg_RSVD2B = 0xBD,
	OV7670Reg_AD_CHB = 0xBE,
	OV7670Reg_AD_CHR = 0xBF,
	OV7670Reg_AD_CHGb = 0xC0,
	OV7670Reg_AD_CHGr = 0xC1,
	OV7670Reg_RSVD2C = 0xC2,
	OV7670Reg_RSVD2D = 0xC3,
	OV7670Reg_RSVD2E = 0xC4,
	OV7670Reg_RSVD2F = 0xC5,
	OV7670Reg_RSVD30 = 0xC6,
	OV7670Reg_RSVD31 = 0xC7,
	OV7670Reg_RSVD32 = 0xC8,
	OV7670Reg_SATCTR = 0xC9
} OV7670_RegAddrTypeDef;



OV7670_BoolTypeDef OV7670_Init(void);
OV7670_BoolTypeDef OV7670_WR_Reg(uint8_t RegAddr, uint8_t RegData);


#endif
