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
 * \brief ��ʪ�ȴ�����SHT20 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 20-07-03  yrz, first implementation.
 * \endinternal
 */

#include "zsl42x_pin.h"
#include "am_hwconf_sht20.h"
#include "am_zsl42x_inst_init.h"

/** \breif ��ʪ�ȴ�����SHT20 �豸�ṹ�嶨�� */
am_local am_sht20_dev_t __g_sht20_dev;

/** \brief ��ʪ�ȴ�����SHT20 �豸ʵ���� */
am_sht20_handle_t am_sht20_inst_init (void)
{
    return am_sht20_init (&__g_sht20_dev,
                           am_zsl42x_i2c0_inst_init());
}

/** \brief ��ʪ�ȴ�����SHT20 ʵ�����ʼ�� */
void am_sht20_inst_deinit (am_sht20_handle_t handle)
{
    am_sht20_deinit(handle);
}

/* end of file */
