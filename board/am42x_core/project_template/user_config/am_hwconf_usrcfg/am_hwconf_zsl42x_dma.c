/*******************************************************************************
*                                 AMetal
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
 * \brief ZSL42x DMA �û������ļ�
 * \sa am_hwconf_zsl42x_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-18  zp, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_zsl42x.h"
#include "hw/amhw_zsl42x_rcc.h"
#include "am_zsl42x_dma.h"
/**
 * \addtogroup am_if_src_hwconf_zsl42x_dma
 * \copydoc am_hwconf_zsl42x_dma.c
 * @{
 */

/**
 * \brief DMA ƽ̨��ʼ����
 */
static void __zsl42x_plfm_dma_init (void)
{
    am_clk_enable(CLK_DMA);
}

/**
 * \brief DMA ƽ̨ȥ��ʼ����
 */
static void __zsl42x_plfm_dma_deinit (void)
{
    am_clk_disable(CLK_DMA);
}

/** \brief DMA �豸��Ϣ */
static const am_zsl42x_dma_devinfo_t __g_dma_devinfo = {
    ZSL42x_DMA_BASE,           /**< \brief ָ��DMA�Ĵ������ָ�� */
    INUM_DMA,                  /**< \brief DMA�ж������� */
    __zsl42x_plfm_dma_init,    /**< \brief DMAƽ̨��ʼ�� */
    __zsl42x_plfm_dma_deinit   /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA�豸ʵ�� */
static am_zsl42x_dma_dev_t __g_dma_dev;

/**
 * \brief DMA ʵ����ʼ��
 * \return ��
 */
int am_zsl42x_dma_inst_init (void)
{
    return am_zsl42x_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_zsl42x_dma_inst_deinit (void)
{
    am_zsl42x_dma_deinit();
}

/**
 * @}
 */

/* end of file */
