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
 * \brief �߼���ʱ���˿ڡ����ɲ�������ν��иߵ�ƽɲ�������ɲ�����ܲ��ԣ����̣�ͨ�� HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ��Ϣ��ÿ5s���PWM�������Ϊɲ���ĸı���ı�
 *   2.demo���Կ�ʼ������ʱ5�룬��ʱ�������ߵ�ƽɲ��������PWM�����Ϊɲ�����ܱ�Ϊ�͵�ƽ��
 *                ����ʱ5�룬��ʱ�����������־��ɲ�����ý��ܣ�PWM���������
 *                ����ʱ5�룬��ʱ���������ɲ��ʹ�ܣ�PWM�����Ϊɲ�����ܱ�Ϊ�͵�ƽ��
 *                ����ʱ5�룬��ʱ���������ɲ�����ܣ�PWM�������������
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ʹ�õ�������PIOB_1����ƽ����ģ�����ţ���PIOB_11���ߵ�ƽɲ��������ţ���
 *    3. PIOA_8Ϊ��TIM4_CHA��PWM������š�
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_adtim_port_sw_brake.c src_zsl42x_hw_adtim_port_sw_brake
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-10  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_adtim_port_sw_brake
 * \copydoc demo_zsl42x_hw_adtim_port_sw_brake.c
 */

/** [src_zsl42x_hw_adtim_port_sw_brake] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zsl42x.h"
#include "hw/amhw_zsl42x_adtim.h"
#include "am_zsl42x_inst_init.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_adtim_port_sw_brake_entry (void)
{

    AM_DBG_INFO("demo am42x_core hw adtim port_sw_brake!\r\n");

    am_gpio_pin_cfg(PIOB_1, PIOB_1_GPIO | PIOB_1_OUT_PP);

    am_gpio_pin_cfg(PIOB_11, PIOB_11_GPIO | PIOB_11_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_8,  PIOA_8_TIM4_CHA | PIOA_8_OUT_PP);

    /* ��ʱ��ʱ��ʹ�� */
    am_clk_enable(CLK_TIM456);

    demo_zsl42x_hw_adtim_port_sw_brake_entry(ZSL42x_TIM4,
                                             AMHW_ZSL42x_ADTIM_CHX_A,
                                             500000 / 4,
                                             500000,
                                             PIOB_1,
                                             AMHW_ZSL42x_ADTIM_TRIG_PB11);
}
/** [src_zsl42x_hw_adtim_port_sw_brake] */

/* end of file */
