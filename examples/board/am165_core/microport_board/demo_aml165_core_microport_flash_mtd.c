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
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ�֡�
 *
 * ���� MX25L1606 �ǵ��͵� FLASH �洢�ڼ䣬��˿���ʹ�� MTD �ӿڶ�д��
 * ʹ֮����������޹أ�ʵ�ֿ�ƽ̨���á�
 *
 * - �������裺
 *   1. �� MicroPort FLASH ������ӵ� aml165-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ����д���ݵ� FLASH��
 *   2. ������ FLASH ��ȡ���ݣ���ͨ�����ڴ�ӡ������
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOB_3 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_microport_flash_mtd.c src_aml165_core_microport_flash_mtd
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_microport_flash_mtd
 * \copydoc demo_aml165_core_microport_flash_mtd.c
 */

/** [src_aml165_core_microport_flash_mtd] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_components_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_microport_flash_mtd_entry (void)
{
    AM_DBG_INFO("demo aml165_core microport flash mtd!\r\n");

    demo_mtd_entry(am_microport_flash_mtd_inst_init(), 8);
}
/** [src_aml165_core_microport_flash_mtd] */

/* end of file */