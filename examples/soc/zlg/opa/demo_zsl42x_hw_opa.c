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
 * \brief OPA ��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PB00����ģ���ѹ����ӦOPA�������PA04Ҳ�����PB00��С��ȵ�ѹ��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_opa_one.c src_zsl42x_hw_opa_one
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-10-10  ly, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_opa_one
 * \copydoc demo_zsl42x_hw_opa_one.c
 */

/** [src_zsl42x_hw_opa_one] */
#include "ametal.h"
#include "am_zsl42x.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_board.h"
#include "am_zsl42x_opa.h"
#include "hw/amhw_zsl42x_opa.h"

/** \brief У׼���� */
#define __OPA_CLK        AMHW_ZSL42x_OPA_CLK_16

/** \brief У׼��ʽ */
#define __OPA_AZ_WAY     AMHW_ZSL42x_OPA_AZ_SW

/**
 * \brief OPA��ʼ��
 */
static void __opa_general_purpose_init (amhw_zsl42x_opa_t *p_hw_opa)
{
    /* ʹ�� OPA */
    amhw_zsl42x_opa_en(p_hw_opa);

    /* �Զ�У׼ʹ�� */
    amhw_zsl42x_opa_az_en(p_hw_opa);

    /* �Զ�У׼���������� */
    amhw_zsl42x_opa_clk_sel(p_hw_opa, __OPA_CLK);

    /* ѡ��У׼��ʽ */
    amhw_zsl42x_opa_az_way_sel(p_hw_opa, __OPA_AZ_WAY);
}

/**
 * \brief OPA ͨ������Ŵ���ģʽ��ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsl42x_hw_opa_entry (void *p_hw_opa)
{
    /* ʹ��BGR */
    amhw_zsl42x_bgr_enable(AM_TRUE);

    /* OPA��ʼ�� */
    __opa_general_purpose_init((amhw_zsl42x_opa_t *)p_hw_opa);

    /* ����У׼ */
    amhw_zsl42x_az_start (p_hw_opa, AMHW_ZSL42x_AZ_SW_START);

    /* ��ʱ 20us*/
    am_udelay(20);

    while (1) {
        ;
    }
}

/* end of file */
