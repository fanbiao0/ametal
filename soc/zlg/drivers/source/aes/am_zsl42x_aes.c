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
 * \brief AES����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08
 * \endinternal
 */

#include "ametal.h"
#include "am_zsl42x.h"
#include "am_delay.h"
#include "zsl42x_periph_map.h"
#include "am_zsl42x_aes.h"
#include "hw/amhw_zsl42x_aes.h"

/**
 * \brief AES ����
 */
uint32_t am_zsl42x_aes_encrypt (am_aes_handle_t handle,
                                uint8_t         key_len,
                                uint32_t       *p_aes_data,
                                uint32_t       *p_key_data,
                                uint32_t       *p_ency_data)
{
    amhw_zsl42x_aes_t *p_hw_aes;

    if (handle == NULL) {
        return -AM_ERROR;
    }

    p_hw_aes = (amhw_zsl42x_aes_t *)(handle->p_devinfo->reg_base);

    /* ������Ҫ���ܵ��������� */
    amhw_zsl42x_aes_data_write (p_hw_aes, p_aes_data);

    /* ������Կ  */
    switch (key_len){

        case AM_ZSL42x_AES_KEY_LEN_128_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_128_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_128_BIT,
                                      p_key_data);
            break;
        case AM_ZSL42x_AES_KEY_LEN_192_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_192_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_192_BIT,
                                      p_key_data);
            break;
        case AM_ZSL42x_AES_KEY_LEN_256_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_256_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_256_BIT,
                                      p_key_data);
            break;
    }

    /* ʹ�ܼ������� */
    amhw_zsl42x_aes_encrypt (p_hw_aes);

    /* ������������ */
    amhw_zsl42x_aes_start (p_hw_aes);

    /* �ȴ������������ */
    while (amhw_zsl42x_aes_stu_check (p_hw_aes)){

        am_kprintf ("Encrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_zsl42x_aes_stu_check (p_hw_aes)){

            return -AM_ERROR;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_zsl42x_aes_data_read (p_hw_aes, p_ency_data);

    return AM_OK;
}

/**
 * \brief AES ����
 */
uint32_t am_zsl42x_aes_decrypt (am_aes_handle_t handle,
                                uint8_t         key_len,
                                uint32_t       *p_aes_data,
                                uint32_t       *p_key_data,
                                uint32_t       *p_decy_data)
{
    amhw_zsl42x_aes_t *p_hw_aes;

    if (handle == NULL) {
        return -AM_ERROR;
    }

    p_hw_aes = (amhw_zsl42x_aes_t *)(handle->p_devinfo->reg_base);

    /* ������Ҫ���ܵ��������� */
    amhw_zsl42x_aes_data_write (p_hw_aes, p_aes_data);

    /* ������Կ  */
    switch (key_len){

        case AM_ZSL42x_AES_KEY_LEN_128_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_128_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_128_BIT,
                                      p_key_data);
            break;
        case AM_ZSL42x_AES_KEY_LEN_192_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_192_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_192_BIT,
                                      p_key_data);
            break;
        case AM_ZSL42x_AES_KEY_LEN_256_BIT:
            /* ������Կ���� */
            amhw_zsl42x_aes_key_len_sel (p_hw_aes,
                                         AMHW_ZSL42x_AES_KEY_LEN_256_BIT);

            amhw_zsl42x_aes_key_save (p_hw_aes,
                                      AMHW_ZSL42x_AES_KEY_LEN_256_BIT,
                                      p_key_data);
            break;
    }

    /* ʹ�ܼ������� */
    amhw_zsl42x_aes_decrypt (p_hw_aes);

    /* ������������ */
    amhw_zsl42x_aes_start (p_hw_aes);

    /* �ȴ������������ */
    while (amhw_zsl42x_aes_stu_check (p_hw_aes)){

        am_kprintf ("decrypt ... !\r\n");

        /* ��ʱ10us�������ʱ�����ʧ�� */
        am_udelay (10);
        if (amhw_zsl42x_aes_stu_check (p_hw_aes)){

            return -AM_ERROR;
        }
    }

    /* ��ȡ���ܺ������ */
    amhw_zsl42x_aes_data_read (p_hw_aes, p_decy_data);

    return AM_OK;
}

/**
 * \brief AES ��ʼ��
 */
am_aes_handle_t am_zsl42x_aes_init(am_zsl42x_aes_dev_t           *p_dev,
                                   const am_zsl42x_aes_devinfo_t *p_devinfo)
{
    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    return p_dev;
}

/**
 * \brief AES ȥ��ʼ��
 */
void am_zsl42x_aes_deinit (am_aes_handle_t handle)
{
    am_zsl42x_aes_dev_t *p_dev  = (am_zsl42x_aes_dev_t *)handle;

    if (handle == NULL){

        return ;
    }

    /* ƽ̨ȥ��ʼ�� */
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
