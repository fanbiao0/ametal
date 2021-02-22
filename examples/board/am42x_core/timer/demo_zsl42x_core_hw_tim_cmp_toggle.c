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
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� PIOA_2 ������ 10Hz ��Ƶ�ʽ��з�ת��
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_tim_cmp_toggle.c src_zsl42x_hw_tim_cmp_toggle
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_tim_cmp_toggle
 * \copydoc demo_zsl42x_hw_tim_cmp_toggle.c
 */

/** [src_zsl42x_hw_tim_cmp_toggle] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zsl42x.h"
#include "am_zsl42x_clk.h"
#include "am_zsl42x_inst_init.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_tim_cmp_toggle_entry (void)
{
    AM_DBG_INFO("demo am42x_core hw tim cmp toggle!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_2, PIOA_2_TIM0_CHA | PIOA_2_OUT_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM012);

    demo_zsl42x_hw_tim_cmp_toggle_entry((void *)ZSL42x_TIM0,
                                        AMHW_ZSL42x_TIM_TYPE_TIM0,
                                        ZSL42x_TIM_CH0A,
                                        am_clk_rate_get(CLK_TIM012),
                                        AMHW_ZSL42x_TIM_CLK_DIV64,
                                        INUM_TIM0);
}
/** [src_zsl42x_hw_tim_cmp_toggle] */

/* end of file */
