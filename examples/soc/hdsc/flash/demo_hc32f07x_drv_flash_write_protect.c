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
 * \snippet demo_hc32f07x_drv_flash_write_protect.c src_hc32f07x_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 20-12-10  xjy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32f07x_drv_flash
 * \copydoc demo_hc32f07x_drv_flash.c
 */

#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_hc32f07x_flash.h"
#include "hc32f07x_periph_map.h"
#include "am_hc32_flash.h"
#include "am_types.h"
#include "am_bitops.h"

#define __DATA_SIZE 512/4

#define AM_HC32_FLASH                 ((amhw_hc32_flash_typedef *)0x40020000UL)
#define AM_HC32_FLASH_END_ADDR        (0x0001FFFFu)
#define AM_HC32_FLASH_BYPASS()        AM_HC32_FLASH->bypass = 0x5A5A;\
                                      AM_HC32_FLASH->bypass = 0xA5A5;
#define AM_HC32_FLASH_TIMEOUT_PGM     (0xFFu)
#define AM_HC32_FLASH_TIMEOUT_ERASE   (0xFFu)

/**
 * \brief ��ҳ���ֱ��
 */
uint32_t flash_writeword(uint32_t addr, uint32_t data)
{
    uint32_t             result  = AM_OK;
    volatile uint32_t    timeout = AM_HC32_FLASH_TIMEOUT_PGM;
    volatile uint32_t    key     = 0;

    key = am_int_cpu_lock();

    if (AM_HC32_FLASH_END_ADDR < addr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_HC32_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_HC32_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //set op
    timeout = AM_HC32_FLASH_TIMEOUT_PGM;
    while(Program != AM_HC32_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_HC32_FLASH_BYPASS();
            AM_HC32_FLASH->cr_f.op = Program;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //write data
    *((volatile uint32_t*)addr) = data;

    //busy?
    timeout = AM_HC32_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_HC32_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    am_int_cpu_unlock(key);

    return (result);
}

/**
 * \brief ��flashд����
 */
int32_t flash_sector_word_program (amhw_hc32f07x_flash_t *p_hw_flash,
                                      uint32_t             dst_addr,
                                      uint32_t            *p_src,
                                      uint32_t             size)
{
    uint32_t i    = 0;

    for(i = 0; i < size; i++) {
        flash_writeword(dst_addr + i * 4, p_src[i]);
    }

    for (i = 0; i < size; i++) {

        if (p_src[i] != *(uint32_t *)(dst_addr + i * 4)) {
            break;
      }
    }
    return i;
}

/**
 * \brief ��������
 */
uint32_t flash_sector_erase(uint32_t sectoraddr)
{
    uint32_t           result  = AM_OK;
    volatile uint32_t  timeout = AM_HC32_FLASH_TIMEOUT_ERASE;
    volatile uint32_t  key     = 0;

    key = am_int_cpu_lock();

    if (AM_HC32_FLASH_END_ADDR < sectoraddr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_HC32_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == AM_HC32_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //set op
    timeout = AM_HC32_FLASH_TIMEOUT_ERASE;
    while(SectorErase != AM_HC32_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_HC32_FLASH_BYPASS();
            AM_HC32_FLASH->cr_f.op = SectorErase;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //write data
    *((volatile uint8_t*)sectoraddr) = 0;

    //busy?
    timeout = AM_HC32_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == (AM_HC32_FLASH->cr_f.busy))
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    am_int_cpu_unlock(key);

    return (result);
}

/**
 * \brief �������
 */
void demo_hc32f07x_drv_flash_write_protect_entry(void *p_hw_flash, uint16_t sector)
{
    int             i;
    uint32_t        status;    /* FLASH ����ִ��״̬ */

    /* Ҫд�� FLASH ������ */
    static uint32_t data1[__DATA_SIZE];
    /* �� FLASH �ж��������� */
    static uint32_t temp1[__DATA_SIZE];
    amhw_hc32f07x_flash_t *p_flash = (amhw_hc32f07x_flash_t *)p_hw_flash;
    /* ���ݳ�ʼ�� */
    for (i = 0; i < __DATA_SIZE; i++) {
        data1[i] = i;
    }
    
    am_hc32f07x_flash_unlockall();
    /* ����ҳ */
    status = flash_sector_erase(sector << 9);
    /* ҳ�������� ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");
        AM_FOREVER;
    }

    /* ��ҳ��д������ */
    status = flash_sector_word_program(p_flash,
                                              sector << 9,
                                              data1,
                                              __DATA_SIZE);
    /* ҳд���������ͣ�ڴ˴� */
    if (__DATA_SIZE != status) {
        AM_DBG_INFO("byte program error!\r\n");
        AM_FOREVER;
    }
    
    /* ###########���θ�������֤########### */
    am_hc32f07x_flash_lockall();  
    /* ����ҳ */
    status = flash_sector_erase(sector << 9);
    am_hc32f07x_flash_unlockall();
    
    /* ��������ȡ���� */
    for (i = 0; i < (512/4); i++) {
        temp1[i] = *(uint32_t *)((i * 4) + (sector << 9));
    }

    for (i = 0; i < (512/4); i++) {
        AM_DBG_INFO("%04d  ", temp1[i]);
    }
    AM_DBG_INFO("\r\nflash test success!\r\n");
}


