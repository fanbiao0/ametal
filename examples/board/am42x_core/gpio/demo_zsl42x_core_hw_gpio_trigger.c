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
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *    ÿ�ΰ���ʱ���ڴ�ӡ "the gpio interrupt happen!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_gpio_trigger.c src_zsl42x_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_gpio_trigger
 * \copydoc demo_zsl42x_hw_gpio_trigger.c
 */

/** [src_zsl42x_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zsl42x.h"
#include "hw/amhw_zsl42x_gpio.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_gpio_trigger_entry (void)
{

    AM_DBG_INFO("demo am217_core hw gpio trigger!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_GPIO);

    demo_zsl42x_hw_gpio_trigger_entry((void *)ZSL42x_GPIO0, PIOA_0);
}
/** [src_zsl42x_hw_gpio_trigger] */

/* end of file */
