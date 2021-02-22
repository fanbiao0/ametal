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
 * \brief ZLG LVD �û������ļ�
 * \sa am_hwconf_zsl42x_lvd.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_zsl42x.h"
#include "am_zsl42x_lvd.h"
#include "hw/amhw_zsl42x_lvd.h"
#include "zsl42x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zsl42x_lvd
 * \copydoc am_hwconf_zsl42x_lvd.c
 * @{
 */

/**
 * \brief LVD ƽ̨��ʼ��
 */
void __zsl42x_plfm_lvd_init (void)
{
    /* ����LVDʱ�� */
    am_clk_enable (CLK_VC_LVD);
}

/**
 * \brief LVD ƽ̨ȥ��ʼ��
 */
void __zsl42x_plfm_lvd_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_VC_LVD);
}

/** \brief LVD �豸��Ϣ */
static const am_zsl42x_lvd_devinfo_t __g_lvd_devinfo =
{
    /**< \brief ָ��LVD�Ĵ������ָ�� */
    ZSL42x_LVD_BASE,

    /**< \brief LVD�жϱ�� */
    INUM_LVD,

    /**
     * \brief LVD��������
     *
     * \note ���ִ�������������Ҫѡ��������������
     *       ����AMHW_ZSL42x_LVD_FTEN | AMHW_ZSL42x_LVD_RTEN��
     */
    AMHW_ZSL42x_LVD_RTEN,

    /**
     * \brief LVD�����˲�ʱ��,�û�����ֵ�ο�ö�ٶ��壺LVD �����˲�ʱ��
     */
    AMHW_ZSL42x_LVD_DEB_TIME_7P2_MS,

    /**
     * \brief LVD��ֵ��ѹ,�û�����ֵ�ο�ö�ٶ��壺LVD ��ֵ��ѹ
     */
    AMHW_ZSL42x_LVD_VIDS_2P5_V,

    /**
     * \brief LVD�����Դ,�û�����ֵ�ο��궨�壺LVD �����Դѡ������
     */
    AMHW_ZSL42x_LVD_SRC_AVCC,

    /**
     * \brief LVD��������,�û�����ֵ�ο��궨�壺LVD ��������ѡ������
     *
     * \note ������λֻ��ѡ��Ϊ�жϻ��߸�λ��������
     */
    AMHW_ZSL42x_LVD_TRI_ACT_SYSTEM_RESET,

    /**< \brief LVDƽ̨��ʼ������ */
    __zsl42x_plfm_lvd_init,

    /**< \brief LVDƽ̨���ʼ������  */
    __zsl42x_plfm_lvd_deinit,
};

/** \brief LVD�豸ʵ�� */
static am_zsl42x_lvd_dev_t __g_lvd_dev;

/** \brief LVD ʵ����ʼ�������LVD��׼������ */
am_zsl42x_lvd_handle_t am_zsl42x_lvd_inst_init (void)
{
    return am_zsl42x_lvd_init(&__g_lvd_dev, &__g_lvd_devinfo);
}

/** \brief LVD ʵ�����ʼ�� */
void am_zsl42x_lvd_inst_deinit (am_zsl42x_lvd_handle_t handle)
{
    am_zsl42x_lvd_deinit(handle);
}

/**
 * @}
 */

/* end of file */
