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
 * \brief zsl42x lora SPI��д����
 *
 * \internal
 * \par modification history:
 * - 1.00 19-04-16 zcb, first implementation.
 * - 1.01 20-09-23  yg, adaptation zsl42x.
 * \endinternal
 */

#ifndef __AM_ZSL42X_LORA_IF_SPI_H
#define __AM_ZSL42X_LORA_IF_SPI_H

/**
 * \addtogroup am_if_zsl42x_lora_if_spi
 * \copydoc am_zsl42x_lora_if_spi.h
 * @{
 */

#include "am_zsl42x_lora.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ZSL42X_LORA_SPI_CS_ENABLE      0   /**< \brief SPIƬѡ��Ч��ƽ */
#define ZSL42X_LORA_SPI_CS_DISABLE     1   /**< \brief SPIƬѡ��Ч��ƽ */

/**
 * \brief ZSL42X LORA SPI����������Ϣ
 */
typedef struct am_zsl42x_lora_if_spi_devinfo {

    /** \brief zsl42x lora �豸ʵ��  */
    am_zsl42x_lora_devinfo_t   zsl42x_lora_devinfo;

    /** \brief SPI �������ַ */
    uint32_t                   spi_rebase;

    /** \brief SPI ƽ̨��ʼ������ */
    void                     (*pfn_plfm_init) (void);

    /** \brief SPI ƽ̨���ʼ������ */
    void                     (*pfn_plfm_deinit)(void);
} am_zsl42x_lora_if_spi_devinfo_t;

/**
 * \brief ZSL42X LORA SPI �豸�ṹ��
 */
typedef struct am_zsl42x_lora_if_spi_dev {

    /** \brief zsl42x lora �豸ʵ��  */
    am_zsl42x_lora_dev_t                   zsl42x_lora_dev;

    /** \brief ZSL42X LORA SPI����������Ϣ */
    const am_zsl42x_lora_if_spi_devinfo_t *p_spi_devinfo;

} am_zsl42x_lora_if_spi_dev_t;


/**
 * \brief ZSL42X LORA SPI�����ʼ��
 *
 * \param[in] p_dev     : zsl42x lora spi�豸
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * return : ��ʼ���ɹ�����lora���������������ʾ��ʼ������
 */
am_zsl42x_lora_handle_t
am_zsl42x_lora_if_spi_init (am_zsl42x_lora_if_spi_dev_t       *p_dev,
                      const am_zsl42x_lora_if_spi_devinfo_t   *p_devinfo);

/**
 * \brief ZSL42X LORA SPI����ȥ��ʼ��
 *
 * \param[in] handle : lora handle
 *
 * \retval AM_OK    : ȥ��ʼ���ɹ�
 * \retval AM_ERROR : ȥ��ʼ��ʧ��
 */
int am_zsl42x_lora_if_spi_deinit (am_zsl42x_lora_handle_t handle);

#ifdef __cplusplus
}
#endif

/** @} grp_am_if_zsl42x_lora_if_spi */

#endif /* } __AM_ZSL42X_LORA_IF_SPI_H */

/* end of file */
