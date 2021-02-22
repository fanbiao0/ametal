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
 * \brief hc32f460 bootloader�����õ�Ӧ�ù���
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 20-11-20  xjy, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_hc32f460.h"
#include "demo_std_entries.h"
#include "am_hc32f460_inst_init.h"
#include "demo_hc32f460_core_entries.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
    /* demo������� */
    //demo_hc32f460_core_single_bootloader_uart_entry();
    
    demo_hc32f460_core_double_bootloader_uart_entry();
    
    while (1) {

    }
}

/* end of file */
