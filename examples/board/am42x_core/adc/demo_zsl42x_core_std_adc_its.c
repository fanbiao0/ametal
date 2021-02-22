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
 * \brief ADC �ڲ��¶ȴ��������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *  am_hwconf_zsl42x_adc.c�ļ��޸��豸��Ϣ�У�
 *   1. �ο���ѹѡ�� AMHW_ZSL42x_ADC_REFVOL_INSIDE_1500MV �� AMHW_ZSL42x_ADC_REFVOL_INSIDE_2500MV��
 *   2. �ο���ѹ(mv)�� 1500 �� 2500��
 *   3. ʹ��ADCͨ��28�ڲ��¶ȴ�����.(1��ʹ�ܣ�0������)
 *
 *
 * - ʵ������
 *   1. ��������¶Ȳ���ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *       PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_std_adc_its.c src_std_adc_its
 *
 * \internal
 * \par Modification History
 * - 1.00 19-12-09  fzb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_std_adc_its
 * \copydoc demo_zsl42x_std_adc_its.c
 */

/** [src_std_adc_its] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zsl42x_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_std_adc_its_entry (void)
{
    AM_DBG_INFO("demo am42x_core std adc its!\r\n");

    demo_std_adc_its_entry(am_zsl42x_adc_inst_init(), 28);

}
/** [src_std_adc_its] */

/* end of file */
