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
 * \brief LoRa �ŵ���Ծ�������̹���
 *
 * - ʵ������:
 *   ģ������:LED0��1���Ƶ����˸; demo�������:���demo��ں����ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-16  win, first implementation
 * - 1.01 20-09-23  yg,  adaptation zsl42x.
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_softimer.h"

#include "am_zsl42x_lora.h"
#include "am_hwconf_zsl42x_lora.h"


/**
 * \brief lora������
 */
static am_zsl42x_lora_handle_t g_lora_handle;

#define LORA_RF_FREQUENCY           504000000  /**< \brief �ŵ�Ƶ�� */
#define LORA_TX_POWER               17         /**< \brief ���书��17dB */
#define LORA_PREAMBLE_LENGTH        10         /**< \brief ǰ���볤�� */
#define LORA_BANDWIDTH              0          /**< \brief 125khz ���� */
#define LORA_SPREADING_FACTOR       AM_ZSL42X_LORA_SERVER_SF8     /**< \brief �ŵ����� SFx */
#define LORA_CODINGRATE             AM_ZSL42X_LORA_SERVER_CR_4_5  /**< \brief ������ 4/5 */
#define LORA_SYMBOL_TIMEOUT         8         /**< \brief ���ų�ʱ�� */
#define LORA_FIX_LENGTH_PAYLOAD_ON  AM_FALSE  /**< \brief ���̶ܹ����� */
#define LORA_IQ_INVERSION_OFF       AM_FALSE  /**< \brief ����IQ�źŷ�ת */

/**
 * \brief CAD��ɻص�����
 */
static void __on_cad_done (void *p_arg, uint8_t channel_activity_detected)
{
    if (channel_activity_detected == 1) {
        am_kprintf("Channel is active\r\n");
    } else {
        am_kprintf("Channel is negative\r\n");
    }
}

/**
 * \brief LoRa�ŵ���Ծ���Գ������
 */
void demo_zsl42x_core_lora_channel_activity_detect_entry (void)
{
    static am_zsl42x_lora_radio_events_t events;

    g_lora_handle = am_zsl42x_lora_inst_init();

    am_zsl42x_lora_memset1((uint8_t *)&events,
                           0x00,
                           sizeof(am_zsl42x_lora_radio_events_t));

    /* ���ûص����� */
    events.pfn_cad_done_cb = __on_cad_done;
    am_zsl42x_lora_server_radio_events_set(g_lora_handle, &events);

    /* �ŵ��������� */
    am_zsl42x_lora_server_channel_set(g_lora_handle, LORA_RF_FREQUENCY);

    /* �������� */
    am_zsl42x_lora_server_rx_config_set(g_lora_handle,
                                        AM_ZSL42X_LORA_MODEM_LORA,
                                        LORA_BANDWIDTH,
                                        LORA_SPREADING_FACTOR,
                                        LORA_CODINGRATE,
                                        0,
                                        LORA_PREAMBLE_LENGTH,
                                        LORA_SYMBOL_TIMEOUT,
                                        LORA_FIX_LENGTH_PAYLOAD_ON,
                                        0,
                                        AM_FALSE,
                                        0,
                                        0,
                                        LORA_IQ_INVERSION_OFF,
                                        0);

    while (1) {

        am_zsl42x_lora_server_cad_start(g_lora_handle);

        am_mdelay(3000);

        am_led_toggle(LED0);
    }
}

/* end of file */
