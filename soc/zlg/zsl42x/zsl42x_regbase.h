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
 * \brief ZSL42x оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-03  zp, first implementation
 * \endinternal
 */

#ifndef __ZSL42x_REGBASE_H
#define __ZSL42x_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zsl42x_if_regbase
 * \copydoc zsl42x_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

#define ZSL42x_UART0_BASE              (0x40000000UL)  /** \brief UART0����ַ */
#define ZSL42x_UART1_BASE              (0x40000100UL)  /** \brief UART1����ַ */
#define ZSL42x_UART2_BASE              (0x40006000UL)  /** \brief UART2����ַ */
#define ZSL42x_UART3_BASE              (0x40006400UL)  /** \brief UART3����ַ */
#define ZSL42x_LPUART0_BASE            (0x40000200UL)  /** \brief LPUART0����ַ */
#define ZSL42x_LPUART1_BASE            (0x40004000UL)  /** \brief LPUART1����ַ */
#define ZSL42x_I2C0_BASE               (0x40000400UL)  /** \brief I2C0����ַ */
#define ZSL42x_I2C1_BASE               (0x40004400UL)  /** \brief I2C1����ַ */
#define ZSL42x_SPI0_BASE               (0x40000800UL)  /** \brief SPI0����ַ */
#define ZSL42x_SPI1_BASE               (0x40004800UL)  /** \brief SPI1����ַ */
#define ZSL42x_TIM0_BASE               (0x40000C00UL)  /** \brief TIM0����ַ */
#define ZSL42x_TIM1_BASE               (0x40000D00UL)  /** \brief TIM1����ַ */
#define ZSL42x_TIM2_BASE               (0x40000E00UL)  /** \brief TIM2����ַ */
#define ZSL42x_TIM3_BASE               (0x40005800UL)  /** \brief TIM3����ַ */
#define ZSL42x_TIM4_BASE               (0x40003000UL)  /** \brief TIM4����ַ */
#define ZSL42x_TIM5_BASE               (0x40003400UL)  /** \brief TIM5����ַ */
#define ZSL42x_TIM6_BASE               (0x40003800UL)  /** \brief TIM6����ַ */
#define ZSL42x_LPTIM0_BASE             (0x40000F00UL)  /** \brief LPTIM0����ַ */
#define ZSL42x_LPTIM1_BASE             (0x40000F40UL)  /** \brief LPTIM1����ַ */
#define ZSL42x_AES_BASE                (0x40021400UL)  /** \brief AES����ַ */
#define ZSL42x_ADC_BASE                (0x40002400UL)  /** \brief ADC����ַ */
#define ZSL42x_CLKTRIM_BASE            (0x40001800UL)  /** \brief CLKTRIM����ַ */
#define ZSL42x_CRC_BASE                (0x40020900UL)  /** \brief CRC����ַ */
#define ZSL42x_DAC_BASE                (0x40002500UL)  /** \brief DAC����ַ */
#define ZSL42x_DMA_BASE                (0x40021000UL)  /** \brief DMA����ַ */
#define ZSL42x_FLASH_BASE              (0x40020000UL)  /** \brief FLASH����ַ */
#define ZSL42x_PORT0_BASE              (0x40020C00UL)  /** \brief PORT0����ַ */
#define ZSL42x_PORT1_BASE              (0x40022000UL)  /** \brief PORT1����ַ */
#define ZSL42x_LCD_BASE                (0x40005C00UL)  /** \brief LCDCTRL����ַ */
#define ZSL42x_LVD_BASE                (0x40002400UL)  /** \brief LVD����ַ */
#define ZSL42x_RCC_BASE                (0x40002000UL)  /** \brief RCC����ַ */
#define ZSL42x_PCNT_BASE               (0x40005400UL)  /** \brief PCNT����ַ */
#define ZSL42x_RAM_BASE                (0x40020400UL)  /** \brief RAM����ַ */
#define ZSL42x_PCA_BASE                (0x40001000UL)  /** \brief PCA����ַ */
#define ZSL42x_RTC_BASE                (0x40001400UL)  /** \brief RTC����ַ */
#define ZSL42x_TRNG_BASE               (0x40004C00UL)  /** \brief TRNG����ַ */
#define ZSL42x_VC_BASE                 (0x40002410UL)  /** \brief VC����ַ */
#define ZSL42x_WDT_BASE                (0x40000F80UL)  /** \brief WDT����ַ */
#define ZSL42x_BGR_BASE                (0x40002400UL)  /** \brief BGR����ַ */
#define ZSL42x_SYSTICK                 (0xE000E010UL)  /** \brief SYSTICK����ַ */

#ifdef ZSL42xX3X
#define ZSL42x_OPA_BASE                (0x40002430UL)  /** \brief OPA����ַ */
#else
#define ZSL42x_OPA_BASE                (0x40002400UL)  /** \brief OPA����ַ */
#endif
/** @} */

/**
 * @} zsl42x_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZSL42x_REGBASE_H */

/* end of file */
