/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2020 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ1�뷢��һ�������жϣ����ڲ���ӡ����ǰʱ����Ϣ��
 *   2. ��ָ��ʱ����������жϣ���ӡһ��"alarm clock int!"��ʾ��Ϣ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *    PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_rtc.c src_zsl42x_hw_rtc
 *
 * \internal
 * \par History
 * - 1.00 20-05-14  licl, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_rtc
 * \copydoc demo_zsl42x_hw_rtc.c
 */

/** [src_zsl42x_hw_rtc] */
#include "ametal.h"
#include "am_zsl42x.h"
#include "am_vdebug.h"
#include "demo_zsl42x_entries.h"
#include "am_zsl42x_inst_init.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_hw_rtc_entry (void)
{
    AM_DBG_INFO("demo am42x_core hw rtc!\r\n");

    demo_zsl42x_hw_rtc_entry((void *)ZSL42x_RTC);
}
/** [src_zsl42x_hw_rtc] */

/* end of file */
