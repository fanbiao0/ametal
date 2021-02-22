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
 * \brief RCC
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */
 
#include "hw/amhw_zsl42x_rcc.h"

/* ʹ�ܻ�������� */
static void __rcc_cmd(amhw_zsl42x_peripheral peri, uint8_t cmd)
{
    if(peri > 31) {

        if (cmd) {
            ZSL42x_RCCCTRL->peri_clken[1] |= (1ul << (peri - 31));
        } else {
            ZSL42x_RCCCTRL->peri_clken[1] &= ~(1ul << (peri - 31));
        }
    } else {

        if (cmd) {
            ZSL42x_RCCCTRL->peri_clken[0] |= (1ul << (peri));
        } else {
            ZSL42x_RCCCTRL->peri_clken[0] &= ~(1ul << (peri));
        }
    }
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 *
 */
void amhw_zsl42x_rcc_peripheral_enable (amhw_zsl42x_peripheral peri)
{
    __rcc_cmd(peri, 1);
}

/**
 * \brief ���ĳ����ʱ���Ƿ�ʹ��
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return 1: ��ǰ����ʱ����ʹ�ܣ������ٴ�ʹ��
 *         0: ��ǰ����ʱ��δʹ��
 *
 */
int amhw_zsl42x_rcc_peripheral_enable_check (amhw_zsl42x_peripheral peri)
{
    if(peri > 31) {
        return ((ZSL42x_RCCCTRL->peri_clken[1] >> (peri - 31)) & 0x01);
    } else {
        return ((ZSL42x_RCCCTRL->peri_clken[0] >> peri) & 0x01);
    }
}


/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_zsl42x_rcc_peripheral_disable (amhw_zsl42x_peripheral peri)
{
    __rcc_cmd(peri, 0);
}

/* end of file */
