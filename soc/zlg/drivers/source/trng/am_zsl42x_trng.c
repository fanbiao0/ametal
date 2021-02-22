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
 * \brief trng����ʵ��
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
#include "am_zsl42x_trng.h"
#include "hw/amhw_zsl42x_trng.h"

/**
 * \brief ���������
 */
int am_zsl42x_trng_generate (am_trng_handle_t handle,
                             uint8_t          env_flag,
                             uint32_t         *p_data)
{
    amhw_zsl42x_trng_t *p_hw_trng;

    if (handle == NULL || p_data == NULL){
        return AM_ERROR;
    }

    p_hw_trng = (amhw_zsl42x_trng_t *)(handle->p_devinfo->reg_base);

    /* �����Դ��· */
    amhw_zsl42x_trng_cir_enable (p_hw_trng);

    if (env_flag == AM_ZSL42x_TRNG_POWER_ON){
        /* ѡ������װ�س�ʼֵ */
        amhw_zsl42x_trng_load_set (p_hw_trng, AM_TRUE);
    }else{
        /* ѡ������װ�س�ʼֵ */
        amhw_zsl42x_trng_load_set (p_hw_trng, AM_FALSE);
    }

    /* ѡ������ʽ */
    amhw_zsl42x_trng_load_set (p_hw_trng, AM_TRUE);

    /* ѡ����λ���� */
    amhw_zsl42x_trng_load_set (p_hw_trng, handle->p_devinfo->rng_cnt);

    /* ������������� */
    amhw_zsl42x_trng_run (p_hw_trng);

    /* �ȴ�������� */
    while (amhw_zsl42x_trng_stu_check (p_hw_trng)){

        ;
    }

    if (env_flag == AM_ZSL42x_TRNG_POWER_ON){
        /* ѡ������װ�س�ʼֵ */
        amhw_zsl42x_trng_load_set (p_hw_trng, AM_FALSE);
    }else{
        ;
    }

    /* ѡ������ʽ */
    amhw_zsl42x_trng_load_set (p_hw_trng, AM_FALSE);

    /* ѡ����λ���� */
    amhw_zsl42x_trng_load_set (p_hw_trng, AMHW_ZSL42x_TRNG_CNT_64);

    /* ������������� */
    amhw_zsl42x_trng_run (p_hw_trng);

    /* �ȴ�������� */
    while (amhw_zsl42x_trng_stu_check (p_hw_trng)){

        ;
    }

    /* ��ȡ64λ������� */
    p_data[0] = amhw_zsl42x_trng_low32_data_read (p_hw_trng);
    p_data[1] = amhw_zsl42x_trng_high32_data_read (p_hw_trng);

    /* �ر����Դ��· */
    amhw_zsl42x_trng_cir_disable (p_hw_trng);

    return AM_OK;
}

/**
 * \brief TRNG ��ʼ��
 */
am_trng_handle_t am_zsl42x_trng_init(am_zsl42x_trng_dev_t           *p_dev,
                                   const am_zsl42x_trng_devinfo_t *p_devinfo)
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
 * \brief TRNG ȥ��ʼ��
 */
void am_zsl42x_trng_deinit (am_trng_handle_t handle)
{
    am_zsl42x_trng_dev_t *p_dev  = (am_zsl42x_trng_dev_t *)handle;

    if (handle == NULL){

        return ;
    }

    /* ƽ̨ȥ��ʼ�� */
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

}

/* end of file */
