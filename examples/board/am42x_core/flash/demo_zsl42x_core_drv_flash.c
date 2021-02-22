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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ"erase error!"��
 *   2. д��������ڴ�ӡ"program error!"��
 *   3. д��ɹ������ڴ�ӡ 480������(512)�� 32bit ʮ���������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_drv_flash.c src_zsl42x_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_drv_flash
 * \copydoc demo_zsl42x_drv_flash.c
 */

/** [src_zsl42x_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zsl42x_flash.h"
#include "am_zsl42x.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

#define FLASH_SECTOR    500

/**
 * \brief �������
 */
void demo_zsl42x_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am42x_core drv flash!\r\n");

    demo_zsl42x_drv_flash_entry(ZSL42x_FLASH, FLASH_SECTOR);
}

/** [src_zsl42x_drv_flash] */

/* end of file */
