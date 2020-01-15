/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_mm32l373_hw_adc_int.c src_mm32l373_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-28  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mm32l373_hw_adc_int
 * \copydoc demo_mm32l373_hw_adc_int.c
 */

/** [src_mm32l373_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mm32l373.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_mm32_entries.h"
#include "demo_mm32l373_core_entries.h"

/**
 * \brief �������
 */
void demo_mm32l373_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo mm32l373_core hw adc int!\r\n");

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN);
    am_clk_enable(CLK_ADC1);

    demo_mm32_hw_adc_int_entry(MM32L373_ADC1,
                              INUM_ADC1_2,
                              AMHW_MM32_ADC_CHANNEL4,
                              3300);
}
/** [src_mm32l373_hw_adc_int] */

/* end of file */