/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifdef BUILD_LK
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mt-plat/mt_gpio.h>
//#include <mt-plat/upmu_common.h>
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
	#define LCM_DEBUG  printf
	#define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
	#define LCM_DEBUG  printk
	#define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define LCM_OTM1287_ID			(0x1287)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0x100   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static void lcm_init_power(void)
{
}

static void lcm_suspend_power(void)
{
}

static void lcm_resume_power(void)
{
}

static struct LCM_setting_table lcm_initialization_setting[] = {


{0xFF,3,{0x98,0x81,0x03}},
{0x01,1,{0x08}},
    {0x02,1,{0x00}},
{0x03,1,{0x73}},
{0x04,1,{0x73}},
{0x05,1,{0x14}},
{0x06,1,{0x06}},
{0x07,1,{0x02}},
{0x08,1,{0x05}},
{0x09,1,{0x00}},
{0x0a,1,{0x0c}},
{0x0b,1,{0x00}},
{0x0c,1,{0x1c}},
{0x0d,1,{0x1c}},
{0x0e,1,{0x00}},
{0x0f,1,{0x0c}},
{0x10,1,{0x0c}}, 
{0x11,1,{0x01}},
{0x12,1,{0x01}},
{0x13,1,{0x1b}},  
{0x14,1,{0x0b}},
	{0x15,1,{0x00}},
	{0x16,1,{0x00}},
	{0x17,1,{0x00}},
	{0x18,1,{0x00}},
	{0x19,1,{0x00}},
{0x1a,1,{0x00}},
{0x1b,1,{0x00}},
{0x1c,1,{0x00}},
{0x1d,1,{0x00}},   
{0x1e,1,{0xc8}},
{0x1f,1,{0x80}},  
{0x20,1,{0x02}},
{0x21,1,{0x00}},
{0x22,1,{0x02}},   
	{0x23,1,{0x00}},
	{0x24,1,{0x00}},
	{0x25,1,{0x00}},
	{0x26,1,{0x00}},
	{0x27,1,{0x00}},
{0x28,1,{0xfb}},  
{0x29,1,{0x43}},
{0x2a,1,{0x00}},
{0x2b,1,{0x00}},
{0x2c,1,{0x07}},
{0x2d,1,{0x07}},
{0x2e,1,{0xff}},
{0x2f,1,{0xff}},
{0x30,1,{0x11}},
	{0x31,1,{0x00}},
	{0x32,1,{0x00}},
	{0x33,1,{0x00}},
{0x34,1,{0x84}},
{0x35,1,{0x80}},
{0x36,1,{0x07}},
	{0x37,1,{0x00}},
{0x38,1,{0x00}},
	{0x39,1,{0x00}},
{0x3a,1,{0x00}}, 
{0x3b,1,{0x00}},
{0x3c,1,{0x00}},
{0x3d,1,{0x00}},
{0x3e,1,{0x00}},
{0x3f,1,{0x00}},
	{0x40,1,{0x00}},
{0x41, 1,{0x88}},
	{0x42,1,{0x00}},
{0x43,1,{0x80}},
{0x44,1,{0x08}},
	
	
	{0x50,1,{0x01}},
	{0x51,1,{0x23}},
	{0x52,1,{0x45}},
	{0x53,1,{0x67}},
	{0x54,1,{0x89}},
{0x55,1,{0xab}},
	{0x56,1,{0x01}},
	{0x57,1,{0x23}},
	{0x58,1,{0x45}},
	{0x59,1,{0x67}},
{0x5a,1,{0x89}},
{0x5b,1,{0xab}},
{0x5c,1,{0xcd}},
{0x5d,1,{0xef}},
	
	
{0x5e,1,{0x10}},   
{0x5f,1,{0x02}},
{0x60,1,{0x02}},
{0x61,1,{0x02}},
{0x62,1,{0x02}},
{0x63,1,{0x02}},
{0x64,1,{0x02}},
{0x65,1,{0x02}},
{0x66,1,{0x08}},
{0x67,1,{0x09}},
	{0x68,1,{0x02}},
{0x69,1,{0x10}},
{0x6a,1,{0x12}},
{0x6b,1,{0x11}},
{0x6c,1,{0x13}},
{0x6d,1,{0x0c}},
{0x6e, 1,{0x0e}},
{0x6f,1,{0x0d}},
{0x70,1,{0x0f}},
{0x71,1,{0x06}},
{0x72,1,{0x07}},
	{0x73,1,{0x02}},
	{0x74,1,{0x02}},
{0x75,1,{0x02}},
{0x76,1,{0x02}},
{0x77,1,{0x02}},
{0x78,1,{0x02}},
{0x79,1,{0x02}},
{0x7a,1,{0x02}},
{0x7b,1,{0x02}},
{0x7c,1,{0x07}},
{0x7d,1,{0x06}},
{0x7e,1,{0x02}},
{0x7f,1,{0x11}},
{0x80,1,{0x13}},
{0x81,1,{0x10}},
{0x82,1,{0x12}},
{0x83, 1,{0x0f}},
{0x84,1,{0x0d}},
{0x85,1,{0x0e}},
{0x86,1,{0x0c}},
{0x87,1,{0x09}},
{0x88,1,{0x08}},
	{0x89,1,{0x02}},
{0x8a, 1,{0x02}},
	
{0xff, 3,{0x98,0x81,0x04}},
{0x6c, 1,{0x15}},
{0x6e, 1,{0x2b}},
{0x6f, 1,{0x35}},
{0x3a, 1,{0xA4}},//
{0x8d, 1,{0x1f}},
{0x87, 1,{0xba}},
	{0x26,1,{0x76}},
{0xb2, 1,{0xd1}},
	
	
//{0x35, 1,{0x1f}},
//{0xb5, 1,{0x07}},
//{0x3b, 1,{0x9f}},
{0xff, 3,{0x98,0x81,0x01}},
{0x22, 1,{0x0a}},
{0x31, 1,{0x0b}},
{0x53, 1,{0x87}},
{0x55,1,{0x8f}},		//VCOM2
{0x50, 1,{0xaf}},
{0x51, 1,{0xaa}},
{0x60,1,{0x14}},               //SDT
    {0xA0, 1,  {0x0A}},	    //VP255	GammaP
    {0xA1, 1,  {0x15}},        //VP251
    {0xA2, 1,  {0x1f}},        //VP247
    {0xA3, 1,  {0x11}},        //VP243
    {0xA4, 1,  {0x15}},        //VP239
    {0xA5, 1,  {0x25}},        //VP231
    {0xA6, 1,  {0x1c}},        //VP219
    {0xA7, 1,  {0x1b}},        //VP203
    {0xA8, 1,  {0x72}},        //VP175
    {0xA9, 1,  {0x1d}},        //VP144
    {0xAA, 1,  {0x26}},        //VP111
    {0xAB, 1,  {0x6f}},        //VP80
    {0xAC, 1,  {0x1a}},        //VP52
    {0xAD, 1,  {0x19}},        //VP36
    {0xAE, 1,  {0x4e}},        //VP24
    {0xAF, 1,  {0x21}},        //VP16
    {0xB0, 1,  {0x28}},        //VP12
    {0xB1, 1,  {0x55}},        //VP8
    {0xB2, 1,  {0x65}},        //VP4
    {0xB3, 1,  {0x35}},        //VP0
	
    {0xC0, 1,  {0x0d}},		//VN255GAMMAN
    {0xC1, 1,  {0x21}},        //VN251
    {0xC2, 1,  {0x2d}},        //VN247
    {0xC3, 1,  {0x10}},        //VN243
    {0xC4, 1,  {0x11}},        //VN239
    {0xC5, 1,  {0x25}},        //VN231
    {0xC6, 1,  {0x17}},        //VN219
    {0xC7, 1,  {0x1b}},        //VN203
    {0xC8, 1,  {0x85}},        //VN175
    {0xC9, 1,  {0x19}},        //VN144
    {0xCA, 1,  {0x28}},        //VN111
    {0xCB, 1,  {0x7f}},        //VN80
    {0xCC, 1,  {0x1c}},        //VN52
    {0xCD, 1,  {0x19}},        //VN36
    {0xCE, 1,  {0x4d}},        //VN24
    {0xCF, 1,  {0x23}},        //VN16
    {0xD0, 1,  {0x2C}},        //VN12
    {0xD1, 1,  {0x5A}},        //VN8
    {0xD2, 1,  {0x6c}},        //VN4
	{0xD3,1,{0x39}},
	
	{0xFF,3,{0x98,0x81,0x00}},
	{0x35,1,0x00},
	{0x11,0,{}},
	{REGFLAG_DELAY, 120, {}},
	{0x29,0,{}},
{REGFLAG_END_OF_TABLE, 0x00, {}}

};
static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},

    // Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 200, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
static struct LCM_setting_table lcm_compare_id_setting[] = {
	// Display off sequence
	{0xF0,	5,	{0x55, 0xaa, 0x52,0x08,0x00}},
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd) {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
				//MDELAY(2);
       	}
    }

}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type = LCM_TYPE_DSI;

	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

	// enable tearing-free
	params->dbi.te_mode = LCM_DBI_TE_MODE_VSYNC_ONLY;
	params->dbi.te_edge_polarity = LCM_POLARITY_RISING;

	params->dsi.mode   = SYNC_PULSE_VDO_MODE; //SYNC_PULSE_VDO_MODE;//BURST_VDO_MODE;

	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM = LCM_FOUR_LANE;
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;

	params->dsi.intermediat_buffer_num = 0;	//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

	params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.word_count = 720 * 3;

    params->dsi.vertical_sync_active                = 8;// 3    2
    params->dsi.vertical_backporch                  = 16;// 20   1
    params->dsi.vertical_frontporch                 = 16;//20; // 1  12
    params->dsi.vertical_active_line                = FRAME_HEIGHT;

    params->dsi.horizontal_sync_active              = 50;//60;// 50  2
    params->dsi.horizontal_backporch                = 100;//90
    params->dsi.horizontal_frontporch               = 80;//90
    params->dsi.horizontal_active_pixel             = FRAME_WIDTH;

    params->dsi.ssc_disable                         = 1;
    params->dsi.ssc_range                         = 4;
    params->dsi.HS_TRAIL                             = 15;
    params->dsi.esd_check_enable = 1;
    params->dsi.customization_esd_check_enable = 1;
	params->dsi.noncont_clock = 1;
	params->dsi.noncont_clock_period = 2;
    params->dsi.lcm_esd_check_table[0].cmd          = 0x0a;
    params->dsi.lcm_esd_check_table[0].count        = 1;
    params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9c;
    params->dsi.PLL_CLOCK =212;
}

static void lcm_init(void)
{
  SET_RESET_PIN(1);
  MDELAY(10);
  SET_RESET_PIN(0);
  MDELAY(5);
  SET_RESET_PIN(1);
  MDELAY(120);

  push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_suspend(void)
{
  SET_RESET_PIN(1);
  MDELAY(10);
  SET_RESET_PIN(0);
  MDELAY(5);
  SET_RESET_PIN(1);
  MDELAY(20);
  push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
	lcm_init();
}

extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata);
static int adc_read_vol(void)
{
  int adc[1];
  int data[4] ={0,0,0,0};
  int sum = 0;
  int adc_vol=0;
  int num = 0;
  for(num=0;num<10;num++)
  {
    IMM_GetOneChannelValue(12, data, adc);
    sum+=(data[0]*100+data[1]);
  }
  adc_vol = sum/10;
#if defined(BUILD_LK)
  printf("sunxing adc_vol is %d\n",adc_vol);
#else
  printk("sunxing adc_vol is %d\n",adc_vol);
#endif
  return (adc_vol<90) ? 0 : 1;
}
static unsigned int lcm_compare_id(void)
{

	int array[4];
	char buffer[3];
	char id_high=0;
	char id_low=0;
	int id=0;

	SET_RESET_PIN(1);
	MDELAY(20);
	SET_RESET_PIN(0);
	MDELAY(20);
	SET_RESET_PIN(1);
	MDELAY(100);

	//{0x39, 0xFF, 5, { 0xFF,0x98,0x06,0x04,0x01}}, // Change to Page 1 CMD
	array[0] = 0x00043902;
	array[1] = 0x018198FF;
	dsi_set_cmdq(array, 2, 1);

	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x00, &buffer[0], 1);  //0x98

	id = buffer[0];

  id = id + + adc_read_vol();
	return (0x98 == id)?1:0;

}

LCM_DRIVER ili9881c_auo55_chuanma_hd_lcm_drv =
{
	.name			= "ili9881c_auo55_chuanma_hd",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
    .init_power     = lcm_init_power,
    .resume_power   = lcm_resume_power,
    .suspend_power  = lcm_suspend_power,
	//.esd_check = lcm_esd_check,
	//.esd_recover = lcm_esd_recover,
};

