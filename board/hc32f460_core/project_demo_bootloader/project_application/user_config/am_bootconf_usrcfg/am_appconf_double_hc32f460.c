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
 * \brief HC32 ˫��Ӧ�ó��� �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 20-11-20  xjy, first implementation
 * \endinternal
 */

#include <am_bootconf_usrcfg/am_appconf_double_hc32f460.h>

#include "am_hc32f460.h"
#include "am_hc32f460_inst_init.h"
#include "am_hc32f460_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "am_hc32f460_flash.h"
#include "hc32f460_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_int.h"
#include "am_hc32f460_clk.h"
#include "hw/amhw_hc32f460_rcc.h"
#include "am_arm_nvic.h"
#include "am_boot_msg_flag.h"

static am_boot_flash_handle_t flash_handle;
static am_boot_mem_handle_t   mem_handle;
/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_hc32f460_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x00000000,
        /** \brief flash���ܵĴ�С */
        512 * 1024,
        /** \brief flash������С */
        8192,
        /** \brief flashҳ��С */
        8192,
    },

    /** \brief flash�Ĵ����Ļ���ַ */
    HC32F460_EFM_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_hc32f460_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_hc32_boot_flash_inst_init(void)
{
    return am_hc32f460_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * ��flag��ʽ����Ϣ����
 ******************************************************************************/

static am_boot_msg_flag_devinfo_t __g_boot_msg_flag_info = {
    /** \brief ��������ʼ��ַ */
    0x00044000,
    /** \brief Ӧ������С */
    (512-32)/2 * 1024,
    /** \brief ��־��ŵ�ַ */
    0x00006600,
    /** \brief ��־ռ�õ�ʵ�ʴ�С��һ��Ϊ�ڴ���С��д�뵥Ԫ�����ʹ��flash�ڴ棬��Ϊ��С�Ĳ�����Ԫ*/
    4,
    /** \brief �̼���������Ҫ�ӹ̼��ı�������������Ӧ�ó����ִ����(�����־��Ӧ�ó�����������������ͬһ���ڴ��豸�У����Բ���ʵ�ָú���)*/
    NULL,
};

am_boot_msg_handle_t am_hc32_boot_msg_flag_inst_init()
{
    mem_handle = am_boot_mem_flash_init(flash_handle);
    return am_boot_msg_flag_init(&__g_boot_msg_flag_info,
                                  mem_handle);
}

/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼����ڴ��д�ŵ���ʼ��ַ */
    0x00044000,
    /**< \brief �̼���������ܴ�С */
    (512-32)/2 * 1024,
    /** \brief ������Ź̼���������С , ֵΪ�ڴ�д����С��С�������� */
    4,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_hc32_boot_firmware_flash_inst_init()
{
    flash_handle = am_hc32_boot_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}


/*******************************************************************************
 * ��׼bootloader�û�����
 ******************************************************************************/

/* ������bootloader���õ�����Դ��Ҫ�ӳ�ʼ�����ͷţ��������綨ʱ�������ڵ� */
static void __hc32_boot_plfm_deinit()
{
    uint32_t u32Timeout = 0u;
    volatile uint32_t i = 1000000;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){
    }
    /* ���ô��� */
    am_int_disable(INUM_USART3);
    am_clk_disable(CLK_USART3);
    am_gpio_pin_cfg(PIOE_4, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOE_5, AM_GPIO_INPUT);
    /* ���ö�ʱ�� */
    am_int_disable(INUM_TIMER0_1);
    am_clk_disable(CLK_TIMER0_1);
    
    /* ����ʱ�� */
    HC32F460_SYSCREG->PWR_FPRC = 0xa501;
    HC32F460_MSTP->FCG0_PC = 0XA5A50001;
    HC32F460_MSTP->FCG0    = 0XFFFFFAEE;
    HC32F460_MSTP->FCG0_PC = 0XA5A50000;
    HC32F460_MSTP->FCG1    = 0XFFFFFFFF;
    HC32F460_MSTP->FCG2    = 0XFFFFFFFF;
    HC32F460_MSTP->FCG3    = 0XFFFFFFFF;
    /* Wait stable after close fcg. */
    u32Timeout = 0x1000;
    while (u32Timeout--);
    HC32F460_SYSCREG->CMU_CKSWR = ((uint8_t)0x1);
    /* Wait stable after close fcg. */
    u32Timeout = 0x1000;
    while (u32Timeout--);
    HC32F460_SYSCREG->CMU_HRCCR    = (uint8_t)0x01;
    HC32F460_SYSCREG->CMU_PLLCFGR  = (uint32_t)0x11101300;
    HC32F460_SYSCREG->CMU_PLLCR    = (uint8_t)0x01;
    HC32F460_SYSCREG->CMU_SCFGR    = (uint32_t)0x00;
    /* Wait stable after close fcg. */
    u32Timeout = 0x2000;
    while (u32Timeout--);
    HC32F460_SYSCREG->PWR_FPRC = 0xa500;

    am_arm_nvic_deinit();

    __disable_irq();
}

/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_hc32_boot_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x00008000,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ֻ����ram1��ram2 */
    128 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __hc32_boot_plfm_deinit,
};

int am_hc32_boot_inst_init()
{
    return am_arm_boot_init(&__g_hc32_boot_devinfo);
}

/** @} */

/* end of file */
