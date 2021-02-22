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
 * \brief HC32ϵ�������������������̺����������
 * \sa    demo_hc32_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_HC32F07X_ENTRIES_H
#define __DEMO_HC32F07X_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"

#include "hw/amhw_hc32_adc.h"
#include "hw/amhw_hc32f07x_flash.h"
#include "hw/amhw_hc32_gpio.h"
#include "hw/amhw_hc32_i2c.h"
#include "hw/amhw_hc32_spi.h"
#include "hw/amhw_hc32_dma.h"
#include "hw/amhw_hc32_tim.h"
#include "hw/amhw_hc32_uart.h"
#include "hw/amhw_hc32_wdt.h"
#include "hw/amhw_hc32_lvd.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_flash ָ�� FLASH ����Ĵ������ָ��
 * \param[in] sector     ʹ�� FLASH ������
 *
 * \retval ��
 */
void demo_hc32f07x_drv_flash_entry (void *p_hw_flash, uint16_t sector);


/**
 * \brief DAC�����ѹ���̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_dac  ָ��DAC�Ĵ���ָ��
 * \param[in] dma_src   DMA����Դ
 * \param[in] dma_chan  DMAͨ��
 * \param[in] p_vol_val ��ѹֵ
 *
 * \retval ��
 */
void demo_hc32f07x_hw_dac_dma_entry(void     *p_hw_dac,
                                int32_t   dma_src,
                                int32_t   dma_chan,
                                uint16_t *p_vol_val);

/**
 * \brief OPA ͨ������Ŵ���ģʽ��ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa :ָ��OPA�Ĵ���ָ��
 * \param[in] mode     :OPA����ģʽ
 *
 * \retval ��
 */
void demo_hc32f07x_hw_opa_one_entry (void *p_hw_opa, uint8_t mode);

/**
 * \brief LVDϵͳ�ж����̣�hw�ӿڲ�ʵ��
 *
 * \param[in] p_hw_lvd   : ָ��LVD�Ĵ���ָ��
 * \param[in] lvd_vids   : LVD ��ֵ��ѹ��amhw_hc32_lvd_vids_t
 * \param[in] lvd_src    : LVD �����Դѡ�񣬺궨�� AMHW_HC32_LVD_SRC_
 * \param[in] pfn_lvd_cb : �û��ص�����
 * \param[in] p_arg      : �û��ص���������
 *
 * \retval ��
 */
void demo_hc32f07x_hw_lvd_int_entry (amhw_hc32_lvd_t        *p_hw_base,
                                     amhw_hc32_lvd_vids_t    lvd_vids,
                                     uint32_t                lvd_src,
                                     am_pfnvoid_t            pfn_lvd_cb,
                                     void                   *p_arg);

/**
 * \brief OPA DAC��ѹ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_opa  : ָ��OPA�Ĵ���ָ��
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ���ָ��
 * \param[in] mode      : OPA����ģʽ
 * \param[in] p_vol_val : DAC���õ�ѹֵ����
 * \param[in] number    : DAC���õ�ѹֵ���鳤��
 *
 * \retval ��
 */
void demo_hc32f07x_hw_opa_dac_entry (void      *p_hw_opa,
                                 void      *p_hw_dac,
                                 uint8_t    mode,
                                 uint16_t  *p_vol_val,
                                 uint32_t   number);

/**
 * \brief USBģ��U������
 * \param[in] handle      USBģ����̷�����
 * \return ��
 */
void demo_usbd_msc_entry (void* p_handle);	

/**
 * \brief USBģ�ⰴ������
 * \param[in] handle      USBģ����̷�����
 * \return ��
 */
void demo_usbd_keyboard_entry (void* p_handle);

/**
 * \brief USB��ӡ������   �����̽���ӡ�����Ϣ
 * \param[in] handle      USB��ӡ��������
 * \return ��
 */
void demo_usbd_printer_entry (void* p_handle);

/**
 * \brief USB��ӡ������   �����̴���ӡʱ���Լ���ӡ��������ʾ
 * \param[in] handle      USB��ӡ��������
 * \return ��
 */
void demo_usbd_printer_counter_entry (void* p_handle);

/**
 * \brief USBģ�⴮������
 * \param[in] handle      USBģ�⴮�ڷ�����
 * \return ��
 */
void demo_usbd_vcom_entry (void* p_handle);

/**
 * \brief �������
 */
void demo_hc32f07x_drv_flash_write_protect_entry(void *p_flash, uint16_t sector);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_HC32_ENTRIES_H */

/* end of file */
