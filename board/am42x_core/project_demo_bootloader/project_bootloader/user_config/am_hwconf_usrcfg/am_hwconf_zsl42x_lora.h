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
 * \brief ZSL42X LORA �û������ļ�
 * \sa am_hwconf_zsl42x_lora.h
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-15  win, first implementation.
 * - 1.01 20-09-23  yg,  adaptation zsl42x.
 * \endinternal
 */

#ifndef __AM_HWCONF_ZSL42X_LORA_H
#define __AM_HWCONF_ZSL42X_LORA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zsl42x_lora.h"
#include "am_zsl42x_lora_reg.h"
#include "am_zsl42x_lora_if_spi.h"

/**
 * \brief ZSL42X LORA ʵ����ʼ��
 */
am_zsl42x_lora_handle_t am_zsl42x_lora_inst_init (void);

/**
 * \brief ZSL42X LORA ʵ�����ʼ��
 */
void am_zsl42x_lora_inst_deinit (am_zsl42x_lora_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_ZSL42X_LORA_H */

/* end of file */
