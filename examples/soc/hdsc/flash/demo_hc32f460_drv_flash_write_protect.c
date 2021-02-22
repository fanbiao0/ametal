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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   flashд������֤��
 *   1. �����������ڴ�ӡ "erase error!"��
 *   2. д��������ڴ�ӡ "program error!"��
 *   3. ��ӡ��д���ַ��ȡ�����ݣ�
 *
 * \par Դ����
 * \snippet demo_hc32f460_drv_flash_write_protect.c src_hc32f460_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 20-12-10  xjy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f460_drv_flash
 * \copydoc demo_hc32f460_drv_flash.c
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_hc32f460_flash.h"
#include "am_hc32f460_flash.h"
#include "am_hc32f460.h"

#define __FLASH_SECTOR  60    /**< \brief ���� */
#define __SECTOR_SIZE (8 * 1024)
#define __DATA_SIZE ((__SECTOR_SIZE / 4))

#define __AM_HC32F460_FLASH_START_ADDR   0x0
#define __AM_HC32F460_FLASH_END_ADDR     0x7FFDF

/**
 * \brief flashȫƬд����
 */
void sector_erase_lock_all(amhw_hc32f460_flash_t *p_hw_flash)
{
    amhw_hc32f460_flash_unlock(p_hw_flash);
    amhw_hc32f460_flash_efm_fpmtsw_set(p_hw_flash, 0x70000);
    amhw_hc32f460_flash_efm_fpmtew_set(p_hw_flash, 0x6FFFF);
    amhw_hc32f460_flash_lock(p_hw_flash);
}

/**
 * \brief flash�涨��ַд����
 */
int32_t sector_erase_lock(amhw_hc32f460_flash_t *p_hw_flash, 
                                        uint32_t start_addr, 
                                        uint32_t end_addr)
{
    if(start_addr > end_addr) {
        return AM_ERROR;
    }
    amhw_hc32f460_flash_unlock(p_hw_flash);
    amhw_hc32f460_flash_efm_fpmtsw_set(p_hw_flash, start_addr);
    amhw_hc32f460_flash_efm_fpmtew_set(p_hw_flash, end_addr);
    amhw_hc32f460_flash_lock(p_hw_flash);
    return AM_OK;
}

/**
 * \brief flashȫƬ����д����
 */
void sector_erase_unlock(amhw_hc32f460_flash_t *p_hw_flash)
{
    amhw_hc32f460_flash_unlock(p_hw_flash);
    amhw_hc32f460_flash_efm_fpmtsw_set(p_hw_flash, 0x6FFFF);
    amhw_hc32f460_flash_efm_fpmtew_set(p_hw_flash, 0x6FFFF);
    amhw_hc32f460_flash_lock(p_hw_flash);
}

/**
 * \brief �������
 */
void demo_hc32f460_drv_flash_write_protect_entry(void *p_hw_flash, uint16_t sector)
{
    int             i;
    uint32_t        status;    /* FLASH ����ִ��״̬ */
    /* Ҫд�� FLASH ������ */
    static uint32_t data1[__DATA_SIZE];

    /* �� FLASH �ж��������� */
    static uint32_t temp1[__DATA_SIZE];
    amhw_hc32f460_flash_t *p_flash = (amhw_hc32f460_flash_t *)p_hw_flash;
    
    /* ���ݳ�ʼ�� */
    for (i = 0; i < __DATA_SIZE; i++) {
        data1[i] = i;
    }

    /* ���ֱ�� */
    am_hc32f460_flash_init(p_flash);
    
    sector_erase_unlock(p_flash);
    /* ����ҳ */
    status = am_hc32f460_flash_sector_erase(p_flash, sector * __SECTOR_SIZE);
    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = am_hc32f460_flash_sector_program(p_flash,
                                   sector * __SECTOR_SIZE,
                                   data1,
                                   __DATA_SIZE);
    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("word program error!\r\n");
        AM_FOREVER;
    }
    
    /* ##########�޸Ĵ˴�����֤########## */
    sector_erase_lock_all(p_flash);
    /* ����ҳ */
    am_hc32f460_flash_sector_erase(p_flash, sector * __SECTOR_SIZE);
    sector_erase_unlock(p_flash);
    
    
    /* ��ҳ��ȡ���� */
    for (i = 0; i < __DATA_SIZE; i++) {
        temp1[i] = *(uint32_t *)((i * 4) + (sector * __SECTOR_SIZE));
    }

    for (i = 0; i < __DATA_SIZE; i++) {
        AM_DBG_INFO("%04d  ", temp1[i]);
    }
    AM_DBG_INFO("\r\n");
}


