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
 * \brief ZSL42x оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZSL42x_H
#define __AM_ZSL42x_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#ifdef ZSL42xX3X
#include "../zsl42x/zsl42xx3x_pin.h" /**< \brief ������ZSL42xF030��ZSL42xL13X */
#else    
#include "../zsl42x/zsl42x_pin.h"    /**< \brief ������ZSL42xL/F17X��ZSL42xL/F19X */
#endif
    
/** \brief оƬ�жϱ�Ŷ��� */
#include "../zsl42x/zsl42x_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "../zsl42x/zsl42x_regbase.h"

/** \brief оƬ����ӳ�� */
#include "../zsl42x/zsl42x_periph_map.h"

/** \brief ʱ��ID���� */
#include "../zsl42x/zsl42x_clk.h"

/** \brief DMAͨ���Ŷ��� */
#include "../zsl42x/zsl42x_dma_chan.h"

/**
 * \name Cortex-M0+ �ں˴���������������
 * @{
 */

#ifndef AM_CORTEX_M0

#define AM_CORTEX_M0             1

#endif

#if defined AM_CORTEX_M0

#define __MPU_PRESENT            0  /**< \brief M0+����MPU          */
#define __NVIC_PRIO_BITS         2  /**< \brief M0+��Ϊ2            */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ1 ��������SysTick */

#include "core_cm0plus.h"

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSL42x_H */

/* end of file */
