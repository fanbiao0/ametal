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
 * \brief PCA 16bit PWM���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. PCAͨ��0��PB4�������1KHz PWM��ռ�ձ�Ϊ60%��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zsl42x_drv_pca_16bit_pwm.c src_zsl42x_drv_pca_16bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 19-11-22  RZ, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_drv_pca_16bit_pwm
 * \copydoc demo_zsl42x_drv_pca_16bit_pwm.c
 */

/** [src_zsl42x_drv_pca_16bit_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_zsl42x_pca.h"
#include "am_zsl42x_inst_init.h"
#include "demo_am42x_core_entries.h"

/**
 * \brief �������
 */
void demo_zsl42x_core_drv_pca_16bit_pwm_entry (void)
{
    am_zsl42x_pca_handle_t handle;

    AM_DBG_INFO("demo am42x_core pca 16bit pwm entry!\r\n");

    handle = am_zsl42x_pca1_inst_init();

    am_zsl42x_pca_pwm_set(handle, 0, 0, ZSL42x_PCA_PWM_16, 1500, 600);

    am_zsl42x_pca_start(handle);

    while(1) {

    }
}
/** [src_zsl42x_drv_pca_16bit_pwm] */

/* end of file */
