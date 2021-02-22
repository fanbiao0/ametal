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
 * \brief ZSL42x LPUART �û������ļ�
 * \sa am_zsl42xl_hwconfig_lpuart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-26  zp, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_zsl42x_lpuart.h"
#include "hw/amhw_zsl42x_lpuart.h"
#include "am_clk.h"
#include "am_zsl42x.h"
#include "hw/amhw_zsl42x_gpio.h"
#include "hw/amhw_zsl42x_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_zsl42x_lpuart
 * \copydoc am_hwconf_zsl42x_lpuart.c
 * @{
 */
/** \brief LPUART0ƽ̨��ʼ�� */
static void __zsl42x_plfm_lpuart0_init (void)
{
    am_clk_enable(CLK_LPUART0);

    am_gpio_pin_cfg(PIOB_11, PIOB_11_LPUART0_RXD | PIOB_11_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_LPUART0_TXD | PIOB_12_OUT_PP );
}

/** \brief ���LPUART0ƽ̨��ʼ�� */
static void __zsl42x_plfm_lpuart0_deinit (void)
{
    am_clk_disable(CLK_LPUART0);

    am_gpio_pin_cfg(PIOB_11, PIOB_11_GPIO | PIOB_11_INPUT_PU);
    am_gpio_pin_cfg(PIOB_12, PIOB_12_GPIO | PIOB_12_INPUT_PU);
}

/** \brief LPUART0�豸��Ϣ */
static const am_zsl42x_lpuart_devinfo_t __g_lpuart0_devinfo = {

    ZSL42x_LPUART0_BASE,              /**< \brief LPUART0 */
    INUM_LPUART0,                     /**< \brief LPUART0���жϱ�� */
    AMHW_ZSL42x_LPUART_SCLK_SRC_PCLK, /**< \brief ͨ�Ŵ���ʱ��  */

    AMHW_ZSL42x_LPUART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_ZSL42x_LPUART_STOP_1_0_BIT,  /**< \brief 1��ֹͣλ */

    AM_FALSE,

    115200,                           /**< \brief ���õĲ����� */
                                      
    0,                                /**< \brief �������ж� */
                                      
    NULL,                             /**< \brief ʹ��RS485 */
    __zsl42x_plfm_lpuart0_init,       /**< \brief LPUART0��ƽ̨��ʼ�� */
    __zsl42x_plfm_lpuart0_deinit,     /**< \brief LPUART0��ƽ̨ȥ��ʼ�� */
};

/**< \brief ����LPUART0 �豸 */
static am_zsl42x_lpuart_dev_t  __g_lpuart0_dev;

/** \brief LPUART0ʵ����ʼ�������lpuart0��׼������ */
am_uart_handle_t am_zsl42x_lpuart0_inst_init (void)
{
    return am_zsl42x_lpuart_init(&__g_lpuart0_dev, &__g_lpuart0_devinfo);
}

/** \brief LPUART0ʵ�����ʼ�� */
void am_zsl42x_lpuart0_inst_deinit (am_uart_handle_t handle)
{
    am_zsl42x_lpuart_deinit((am_zsl42x_lpuart_dev_t *)handle);
}

/** \brief lpuart2ƽ̨��ʼ�� */
static void __zsl42x_plfm_lpuart1_init (void)
{
    am_clk_enable(CLK_LPUART1);

    am_gpio_pin_cfg(PIOA_1, PIOA_1_LPUART1_RXD | PIOA_1_INPUT_FLOAT );
    am_gpio_pin_cfg(PIOA_0, PIOA_0_LPUART1_TXD | PIOA_0_OUT_PP);
}

/** \brief ���LPUART1ƽ̨��ʼ�� */
static void __zsl42x_plfm_lpuart1_deinit (void)
{
    am_clk_disable(CLK_LPUART1);

    am_gpio_pin_cfg(PIOA_0, PIOA_0_GPIO | PIOA_0_INPUT_PU);
    am_gpio_pin_cfg(PIOA_1, PIOA_1_GPIO | PIOA_1_INPUT_PU);
}

/** \brief LPUART1�豸��Ϣ */
static const am_zsl42x_lpuart_devinfo_t __g_lpuart1_devinfo = {

    ZSL42x_LPUART1_BASE,              /**< \brief LPUART1 */
    INUM_LPUART1,                   /**< \brief LPUART1���жϱ�� */
    AMHW_ZSL42x_LPUART_SCLK_SRC_PCLK, /**< \brief ͨ�Ŵ���ʱ��  */

    AMHW_ZSL42x_LPUART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_ZSL42x_LPUART_STOP_1_0_BIT,  /**< \brief 1��ֹͣλ */

    AM_FALSE,

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief ʹ��RS485 */
    __zsl42x_plfm_lpuart1_init,       /**< \brief LPUART1��ƽ̨��ʼ�� */
    __zsl42x_plfm_lpuart1_deinit,     /**< \brief LPUART1��ƽ̨ȥ��ʼ�� */
};

/**< \brief ����LPUART1 �豸 */
static am_zsl42x_lpuart_dev_t  __g_lpuart1_dev;

/** \brief LPUART1ʵ����ʼ�������lpuart1��׼������ */
am_uart_handle_t am_zsl42x_lpuart1_inst_init (void)
{
    return am_zsl42x_lpuart_init(&__g_lpuart1_dev, &__g_lpuart1_devinfo);
}

/** \brief LPUART1ʵ�����ʼ�� */
void am_zsl42x_lpuart1_inst_deinit (am_uart_handle_t handle)
{
    am_zsl42x_lpuart_deinit((am_zsl42x_lpuart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
