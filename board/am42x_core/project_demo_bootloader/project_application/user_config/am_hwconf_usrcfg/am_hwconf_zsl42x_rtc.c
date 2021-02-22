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
 * \brief ZSL42x RTC �û������ļ�
 * \sa am_hwconf_zsl42x_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_zsl42x.h"
#include "am_clk.h"
#include "am_zsl42x_rtc.h"
#include "hw/amhw_zsl42x_rcc.h"
#include "am_zsl42x_inst_init.h"
#include "zsl42x_periph_map.h"
#include "zsl42x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zsl42x_rtc
 * \copydoc am_hwconf_zsl42x_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __zsl42x_plfm_rtc_init()
{
    /* �ⲿ������������ѡ�� */
    amhw_zsl42x_rcc_xtl_xtal_driver_set(AMHW_ZSL42x_XTL_XTAL_DRIVER_DEFAULT);

    /* XTL�����񵴷��ȵĵ��� */
    amhw_zsl42x_rcc_xtl_xtal_amplitude_set(
    AMHW_ZSL42x_XTL_XTAL_AMPLITUDE_BIG_DEFAULT);

    /* �ⲿ����ʱ��XTL�ȶ�ʱ��ѡ�� */
    amhw_zsl42x_rcc_xtl_waittime_set(AMHW_ZSL42x_XTL_WAITTIME_16384);

    amhw_zsl42x_rcc_set_start(0x5A5A);
    amhw_zsl42x_rcc_set_start(0xA5A5);
    amhw_zsl42x_rcc_xtl_enable();

    /* �ȴ��ȶ�*/
    while(amhw_zsl42x_rcc_xtl_state_get() == AM_FALSE);

    am_clk_enable(CLK_RTC);

    /* RTC ʱ��Դѡ�� */
    amhw_zsl42x_rtc_clk_src_sel(ZSL42x_RTC, AMHW_ZSL42x_RTC_CLK_SRC_XTL_32768Hz);
}

/** ��� RTC ƽ̨��ʼ�� */
void __zsl42x_plfm_rtc_deinit(void)
{
    am_clk_disable(CLK_RTC);
}

/** \brief RTC�豸��Ϣ */
const struct am_zsl42x_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    ZSL42x_RTC_BASE,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    /** \brief �� 1970-1-1 0:0:0 ��ʼ���� */
    1970,

    /** \brief ƽ̨��ʼ������ */
    __zsl42x_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __zsl42x_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_zsl42x_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_zsl42x_rtc_inst_init (void)
{
    return am_zsl42x_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_zsl42x_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_zsl42x_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */
