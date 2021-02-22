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
 * \brief ZLG116 I2C �û������ļ�
 * \sa am_hwconf_zlg116_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_i2c.h"
#include "am_zlg116_clk.h"
#include "am_i2c_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_gpio_i2c
 * \copydoc am_hwconf_zlg116_gpio_i2c.c
 * @{
 */

/**
 * \brief I2C_GPIO �豸�ṹ��
 */
/**
 * \brief I2C_GPIO �豸��Ϣ�����ṹ��
 */
am_i2c_gpio_devinfo_t __g_gpio_i2c_devinfo = {
    PIOA_11,        /**< \brief SCL���� */
    PIOA_12,        /**< \brief SDA���� */

    /** \brief �����ٶ�ָ��, ֵԽ�������ٶ�Խ��, ͨ������߼���������ȷ��ʵ�ʵ������ٶ�  */
    1000,
};

static am_i2c_gpio_dev_t __g_gpio_i2c_dev;    /**< \brief GPIO_I2C ��ss��ʵ�� */

/** \brief GPIO_I2C ʵ����ʼ�������I2C��׼������ */
am_i2c_handle_t am_zlg116_gpio_i2c_inst_init (void)
{
    return am_i2c_gpio_init(&__g_gpio_i2c_dev, &__g_gpio_i2c_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_zlg116_gpio_i2c_inst_deinit (am_i2c_handle_t handle)
{
    am_i2c_gpio_deinit(handle);
}

/** @} */

/* end of file */
