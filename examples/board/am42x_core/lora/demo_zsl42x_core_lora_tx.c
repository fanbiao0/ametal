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
 * \brief LoRa�������ճ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-31  sky, first implementation.
 * - 1.01 20-09-23  yg,  adaptation zsl42x.
 * \endinternal
 */

#include <string.h>
#include "am_board.h"
#include "am_delay.h"
#include "am_vdebug.h"

#include "am_zsl42x_lora.h"
#include "am_hwconf_zsl42x_lora.h"

#define __LORA_ENABLE    1

static uint32_t __g_cnt   = 0;

/**
 * \brief lora������
 */
static am_zsl42x_lora_handle_t g_lora_handle;

#define RADIO_RF_FREQUENCY         504000000   /**< \brief �ŵ�Ƶ�� */

#if (__LORA_ENABLE)

#define LORA_BANDWIDTH              0          /**< \brief ����125Khz */
#define LORA_TX_POWER               17         /**< \brief ����17dB */
#define LORA_SPREADING_FACTOR       AM_ZSL42X_LORA_SERVER_SF8     /**< \brief �ŵ����� SFx */
#define LORA_CODINGRATE             AM_ZSL42X_LORA_SERVER_CR_4_5  /**< \brief ������ 4/5 */
#define LORA_PREAMBLE_LENGTH        10         /**< \brief ǰ���볤�� */
#define LORA_FIX_LENGTH_PAYLOAD_ON  AM_FALSE   /**< \brief ���̶ܹ����� */
#define LORA_SYMBOL_TIMEOUT         8          /**< \brief ���ų�ʱ�� */
#define LORA_IQ_INVERSION_ON        AM_FALSE   /**< \brief ����IQ�źŷ�ת */

#else

#define FSK_TX_POWER                17         /**< \brief ���͹��� */
#define FSK_FRE_DIVI                25000      /**< \brief Ƶ�ʷ�Ƶ��  */
#define FSK_BANDWIDTH               0          /**< \brief ����Ϊ0 */
#define FSK_DATARATE                50000      /**< \brief �������� */
#define FSK_CODINGRATE              0          /**< \brief ��֧�֣�����Ϊ0*/
#define FSK_PREAMBLE_LENGTH         8          /**< \brief ǰ���볤�� */
#define FSK_FIX_LENGTH_PAYLOAD_ON   AM_FALSE   /**< \brief ���̶ܹ����� */
#define FSK_CRC                     AM_TRUE    /**< \brief ʹ��CRCУ�� */
#define FSK_FER_HOP                 AM_FALSE   /**< \brief ��ֹ��Ƶ */
#define FSK_FER_HOP_PERIOD          0          /**< \brief ��֧�֣�����Ϊ0 */
#define FSK_IQ_INVERSION            AM_FALSE   /**< \brief ����IQ�źŷ�ת */

#endif

/**
 * \brief ������ɻص�����
 */
static void __on_tx_done (void *p_arg)
{
    __g_cnt++;
    am_kprintf("%d TX Done!\r\n", __g_cnt);
}

/**
 * \brief ���ͳ�ʱ�ص�����
 */
static void __on_tx_timeout (void *p_arg)
{
    am_kprintf("TX Timeout!\r\n");
}

/**
 * \brief LoRa���Ͳ��Գ������
 */
void demo_zsl42x_core_lora_tx_entry (void)
{
    static am_zsl42x_lora_radio_events_t events;

    g_lora_handle = am_zsl42x_lora_inst_init();

    am_zsl42x_lora_memset1((uint8_t *)&events,
                           0x00,
                           sizeof(am_zsl42x_lora_radio_events_t));

    /* ���ûص����� */
    events.pfn_tx_done_cb    = __on_tx_done;
    events.pfn_tx_timeout_cb = __on_tx_timeout;
    am_zsl42x_lora_server_radio_events_set(g_lora_handle, &events);

    /* �ŵ�Ƶ������ */
    am_zsl42x_lora_server_channel_set(g_lora_handle, RADIO_RF_FREQUENCY);

#if __LORA_ENABLE
    /* �������� */
    am_zsl42x_lora_server_tx_config_set(g_lora_handle,
                                        AM_ZSL42X_LORA_MODEM_LORA,
                                        LORA_TX_POWER,
                                        AM_FALSE,
                                        LORA_BANDWIDTH,
                                        LORA_SPREADING_FACTOR,
                                        LORA_CODINGRATE,
                                        LORA_PREAMBLE_LENGTH,
                                        LORA_FIX_LENGTH_PAYLOAD_ON,
                                        AM_FALSE,
                                        0,
                                        0,
                                        LORA_IQ_INVERSION_ON,
                                        4000);
#else
    am_zsl42x_lora_server_tx_config_set(g_lora_handle,
                                        AM_ZSL42X_LORA_MODEM_FSK,
                                        FSK_TX_POWER,
                                        FSK_FRE_DIVI,
                                        FSK_BANDWIDTH,
                                        FSK_DATARATE,
                                        FSK_CODINGRATE,
                                        FSK_PREAMBLE_LENGTH,
                                        FSK_FIX_LENGTH_PAYLOAD_ON,
                                        FSK_CRC,
                                        FSK_FER_HOP,
                                        FSK_FER_HOP_PERIOD,
                                        FSK_IQ_INVERSION,
                                        4000);
#endif

    while (1) {

        /* �������η��� */
        am_zsl42x_lora_server_send(g_lora_handle,
                                   (uint8_t *)"hello,lora!",
                                   strlen("hello,lora!"));

        am_mdelay(3000);

        am_led_toggle(LED0);
    }
}

/* end of file */
