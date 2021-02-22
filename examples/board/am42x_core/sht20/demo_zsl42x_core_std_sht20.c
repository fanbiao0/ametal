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
 * \brief SHT20 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡSHT20�ɼ�����ʪ�ȡ�
 *
 * \note
 *    ���ڴ�ӡ��ʪ����Ϣ����Ҫ�� PIOB_11 �������� PC ���ڵ� TXD��
 *    PIOB_12 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_std_sht20.c src_std_sht20
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_std_sht20
 * \copydoc demo_zsl42x_std_sht20.c
 */

/** [src_std_sht20] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_am42x_core_entries.h"
#include "am_hwconf_sht20.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_std_sht20_entry (void)
{
    AM_DBG_INFO("demo am42x_core std sht20!\r\n");

    am_sht20_handle_t handle = am_sht20_inst_init();

    demo_std_sht20_entry(handle);
}
/** [src_std_led] */

/* end of file */
