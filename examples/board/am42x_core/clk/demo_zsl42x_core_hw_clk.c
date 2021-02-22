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
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ƶ��(HCLK:48MHz, PCLK:24MHz,)
 *   2. PIOA_1�������HCLK��8��Ƶ��Ƶ���źţ���6MHz
 *      PIOA_2�������PCLK��8��Ƶ��Ƶ���źţ���3MHz
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *       PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_clk.c src_zsl42x_hw_clk
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_clk
 * \copydoc demo_zsl42x_hw_clk.c
 */

/** [src_zsl42x_hw_clk] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zsl42x.h"
#include "hw/amhw_zsl42x_rcc.h"
#include "am_zsl42x_inst_init.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_clk_entry (void)
{
    int clk_id[] = {CLK_HCLK, CLK_PCLK};

    AM_DBG_INFO("demo am42x_core hw clk!\r\n");

    amhw_zsl42x_gpio_sup_hclk_div_set(ZSL42x_GPIO0,
                                    AMHW_ZSL42x_GPIO_SUP_CLK_DIV_8);
    amhw_zsl42x_gpio_sup_hclk_output(ZSL42x_GPIO0);
    am_gpio_pin_cfg(PIOA_1, PIOA_1_HCLK_OUT | PIOA_1_OUT_PP);

    amhw_zsl42x_gpio_sup_pclk_div_set(ZSL42x_GPIO0,
                                    AMHW_ZSL42x_GPIO_SUP_CLK_DIV_8);
    amhw_zsl42x_gpio_sup_pclk_output(ZSL42x_GPIO0);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_PCLK_OUT | PIOA_2_OUT_PP);

    demo_zsl42x_hw_clk_entry(&clk_id[0], AM_NELEMENTS(clk_id));
}
/** [src_zsl42x_hw_clk] */

/* end of file */
