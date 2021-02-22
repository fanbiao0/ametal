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
 * \brief HC32F460 aes 用户配置文件
 * \sa am_hwconf_hc32f460_aes.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-26
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32f460.h"
#include "am_hc32f460_aes.h"
#include "hw/amhw_hc32f460_aes.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_aes
 * \copydoc am_hwconf_hc32f460_aes.c
 * @{
 */

/**
 * \brief AES 平台初始化
 */
void __hc32f460_plfm_aes_init (void)
{
    /* 开启AES钟 */
    am_clk_enable(CLK_AES);
}

/**
 * \brief AES 平台去初始化
 */
void __hc32f460_plfm_aes_deinit (void)
{
    /* 关闭AES时钟 */
    am_clk_disable(CLK_AES);
}

/** \brief AES 设备信息 */
static const am_hc32f460_aes_devinfo_t __g_aes_devinfo =
{
    /**< \brief 指向aes寄存器块的指针 */
    HC32F460_AES_BASE,

    /**< \brief aes平台初始化函数 */
    __hc32f460_plfm_aes_init,

    /**< \brief aes平台解初始化函数  */
    __hc32f460_plfm_aes_deinit,
};

/** \brief AES设备实例 */
static am_hc32f460_aes_dev_t __g_aes_dev;

/** \brief AES 实例初始化，获得AES标准服务句柄 */
am_aes_handle_t am_hc32f460_aes_inst_init (void)
{
    return am_hc32f460_aes_init(&__g_aes_dev, &__g_aes_devinfo);
}

/** \brief AES 实例解初始化 */
void am_hc32f460_aes_inst_deinit (am_aes_handle_t handle)
{
    am_hc32f460_aes_deinit(handle);
}

/**
 * @}
 */

/* end of file */
