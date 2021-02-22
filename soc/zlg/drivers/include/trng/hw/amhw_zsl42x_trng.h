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
 * \brief TRNG �ײ�����ӿ�
 * \internal
 * \par Modification History
 * - 1.00 19-10-08
 * \endinternal
 */

#ifndef __AMHW_ZSL42x_TRNG_H
#define __AMHW_ZSL42x_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_zsl42x_if_trng
 * \copydoc amhw_zsl42x_trng.h
 * @{
 */
/**
 * \brief TRNG - �Ĵ�����
 */
typedef struct amhw_zsl42x_trng {
    __IO uint32_t trngcr;            /**< \brief ���ƼĴ��� */
    __IO uint32_t trngmode;          /**< \brief ģʽ�Ĵ��� */
         uint32_t res;               /**< \brief ���� */
    __IO uint32_t trngdat0;          /**< \brief ���ݼĴ���0 */
    __IO uint32_t trngdat1;          /**< \brief ���ݼĴ���1 */
} amhw_zsl42x_trng_t;

/**
 * \brief TRNG �������������
 *
 * \note :Ӳ������
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_run (amhw_zsl42x_trng_t *p_hw_trng)
{
    p_hw_trng->trngcr |= (1 << 1);
}

/**
 * \brief TRNG ���������״̬��ȡ
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : 1 ���ڲ�������� 0 ������������
 */
am_static_inline
int amhw_zsl42x_trng_stu_check (amhw_zsl42x_trng_t *p_hw_trng)
{
    return ((p_hw_trng->trngcr & (0x2)) >> 1);
}

/**
 * \brief ���Դ��·ʹ��
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_cir_enable (amhw_zsl42x_trng_t *p_hw_trng)
{
    p_hw_trng->trngcr |= (1 << 0);
}

/**
 * \brief ���Դ��·����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_cir_disable (amhw_zsl42x_trng_t *p_hw_trng)
{
    p_hw_trng->trngcr &= ~(1 << 0);
}

/**
 * \brief RNG ��������λ����
 */
typedef enum amhw_zsl42x_trng_cnt {
    AMHW_ZSL42x_TRNG_CNT_0 = 0,
    AMHW_ZSL42x_TRNG_CNT_8,
    AMHW_ZSL42x_TRNG_CNT_16,
    AMHW_ZSL42x_TRNG_CNT_32,
    AMHW_ZSL42x_TRNG_CNT_64,
    AMHW_ZSL42x_TRNG_CNT_128,
    AMHW_ZSL42x_TRNG_CNT_256,
    AMHW_ZSL42x_TRNG_CNT_RES
}amhw_zsl42x_trng_cnt_t;

/**
 * \brief RNG������λ����ѡ��
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 * \param[in] flag      : ������λ�������ο�ö�ٶ��壺RNG ��������λ����
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_cnt_sel (amhw_zsl42x_trng_t *p_hw_trng ,uint32_t flag)
{
    p_hw_trng->trngmode = (p_hw_trng->trngmode & (~(0x7 << 2))) | (flag << 2);
}

/**
 * \brief RNG�����ź��Ƿ������Դ��������������
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 * \param[in] flag      : �Ƿ��������ñ�־ ��AM_TRUE��,AM_FALSE��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_fdbk_set (amhw_zsl42x_trng_t *p_hw_trng ,am_bool_t flag)
{
    if (flag == 1){
        p_hw_trng->trngmode |= (1 << 1);
    }else {
        p_hw_trng->trngmode &= ~(1 << 1);
    }
}

/**
 * \brief �ڲ����µ������ʱ��64bits RNG�Ƿ�����Դ����µĳ�ʼֵ
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 * \param[in] flag      : �Ƿ��������ñ�־ ��AM_TRUE��,AM_FALSE��
 *
 * \retval : ��
 */
am_static_inline
void amhw_zsl42x_trng_load_set (amhw_zsl42x_trng_t *p_hw_trng, am_bool_t flag)
{
    if (flag == 1){
        p_hw_trng->trngmode |= (1 << 0);
    }else {
        p_hw_trng->trngmode &= ~(1 << 0);
    }
}

/**
 * \brief TRNG ��ȡ��32λ�����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��32Ϊ�����
 */
am_static_inline
uint32_t amhw_zsl42x_trng_low32_data_read (amhw_zsl42x_trng_t *p_hw_trng)
{
    return (p_hw_trng->trngdat0);
}

/**
 * \brief TRNG ��ȡ��32λ�����
 *
 * \param[in] p_hw_trng : ָ��TRNG�Ĵ�����ָ��
 *
 * \retval : ��32Ϊ�����
 */
am_static_inline
uint32_t amhw_zsl42x_trng_high32_data_read (amhw_zsl42x_trng_t *p_hw_trng)
{
    return (p_hw_trng->trngdat1);
}

/**
 * @} amhw_if_zsl42x_trng
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZSL42x_TRNG_H */

/* end of file */
