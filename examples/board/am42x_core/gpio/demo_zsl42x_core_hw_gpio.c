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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *    PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_gpio.c src_zsl42x_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-20 zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_gpio
 * \copydoc demo_zsl42x_hw_gpio.c
 */

/** [src_zsl42x_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_zsl42x.h"
#include "am_vdebug.h"
#include "hw/amhw_zsl42x_gpio.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

#define INPUT_PIN  PIOA_0  /**< \brief �������� */
#define OUTPUT_PIN PIOA_10 /**< \brief ������� */

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_gpio_entry (void)
{

    AM_DBG_INFO("demo am42x_core hw gpio!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_GPIO);

    /* ����ϵͳ���õ�ʱ�� */
    am_clk_enable(CLK_GPIO);

    demo_zsl42x_hw_gpio_entry((void *)ZSL42x_GPIO0, INPUT_PIN, OUTPUT_PIN);
}
/** [src_zsl42x_hw_gpio] */

/* end of file */
