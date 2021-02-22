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
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �� MOSI(PIOA_7) ���ź� MISO(PIOA_6) ��������������ģ��ӻ��豸���ػ����ԡ�
 *
 * - ʵ������
 *   1. ����ͨ�� MISO �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���Դ��ڴ�ӡ���Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml165_core_hw_spi_master.c src_aml165_core_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml165_core_hw_spi_master
 * \copydoc demo_aml165_core_hw_spi_master.c
 */

/** [src_aml165_core_hw_spi_master] */
#include <am_aml165_inst_init.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
#include "am_zml165.h"
#include "demo_zlg_entries.h"
#include "demo_aml165_core_entries.h"

/**
 * \brief �������
 */
void demo_aml165_core_hw_spi_master_entry (void)
{
    am_kprintf("demo aml165_core hw spi master!\r\n");

    /* ����ʱ�� */
    am_clk_enable(CLK_SPI1);

    /* �������� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_SPI1_NSS | PIOA_4_AF_PP);
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO | PIOA_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI | PIOA_7_AF_PP);

    demo_zlg_hw_spi_master_entry(ZML165_SPI1,
                                 PIOA_4,
                                 am_clk_rate_get(CLK_SPI1));
}
/** [src_aml165_core_hw_spi_master] */

/* end of file */