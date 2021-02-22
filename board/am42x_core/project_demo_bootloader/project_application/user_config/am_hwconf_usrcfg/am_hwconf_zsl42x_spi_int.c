/*******************************************************************************

                                AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zsl42x.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZSL42x SPI INT �û������ļ�
 * \sa am_hwconf_zsl42x_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zsl42x_spi_int.h"
#include "am_gpio.h"
#include "hw/amhw_zsl42x_spi.h"
#include "am_clk.h"
#include "am_zsl42x.h"
#include "zsl42x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zsl42x_spi_int
 * \copydoc am_hwconf_zsl42x_spi_int.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __zsl42x_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zsl42x_plfm_spi1_int_deinit (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_INPUT_PU);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_INPUT_PU);

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 �豸��Ϣ */
const  struct am_zsl42x_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZSL42x_SPI1_BASE,                        /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                /**< \brief ʱ��ID�� */
    INUM_SPI1,                               /**< \brief SPI1�жϺ� */
    PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP,      /**< \brief SPI1���ñ�ʶ */
    PIOB_15,                                 /**< \brief MOSI���ź� */
    __zsl42x_plfm_spi1_int_init,             /**< \brief SPI1ƽ̨��ʼ������ */
    __zsl42x_plfm_spi1_int_deinit            /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zsl42x_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zsl42x_spi1_int_inst_init (void)
{
    return am_zsl42x_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zsl42x_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zsl42x_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
