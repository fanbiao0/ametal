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
 * \brief LoRa���ճ�ʱ����
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

/**
 * \brief lora������
 */
static am_zsl42x_lora_handle_t g_lora_handle;

#define RADIO_RF_FREQUENCY         504000000   /**< \brief �ŵ�Ƶ�� */

#if (__LORA_ENABLE)
#define LORA_BANDWIDTH              0          /**< \brief ����125Khz */
#define LORA_TX_POWER               17         /**< \brief ����17dB */
#define LORA_SPREADING_FACTOR       AM_ZSL42X_LORA_SERVER_SF8    /**< \brief �ŵ����� SFx */
#define LORA_CODINGRATE             AM_ZSL42X_LORA_SERVER_CR_4_5 /**< \brief ������ 4/5 */
#define LORA_PREAMBLE_LENGTH        10         /**< \brief ǰ���볤�� */
#define LORA_FIX_LENGTH_PAYLOAD_ON  AM_FALSE   /**< \brief ���̶ܹ����� */
#define LORA_SYMBOL_TIMEOUT         8          /**< \brief ���ų�ʱ�� */
#define LORA_IQ_INVERSION_ON        AM_FALSE   /**< \brief ����IQ�źŷ�ת */

#else



#define FSK_BANDWIDTH               58600      /**< \brief ���ʹ��� */
#define FSK_DATARATE                50000      /**< \brief �������� */
#define FSK_CODINGRATE              0          /**< \brief ��֧�֣�����Ϊ0 */
#define FSK_BANDWIDTH_AFC           2500       /**< \brief ����AFC ����  */
#define FSK_PREAMBLE_LENGTH         8          /**< \brief ǰ���볤�� */
#define FSK_SYMB_TIMEOUT            10         /**< \brief ���ų�ʱ */
#define FSK_FIX_LENGTH_PAYLOAD_ON   AM_FALSE   /**< \brief ���̶ܹ����� */
#define FSK_CRC                     AM_TRUE    /**< \brief ʹ��CRCУ�� */
#define FSK_FER_HOP                 AM_FALSE   /**< \brief ��ֹ��Ƶ */
#define FSK_FER_HOP_PERIOD          0          /**< \brief ��֧�֣�����Ϊ0 */
#define FSK_IQ_INVERSION            AM_FALSE   /**< \brief ����IQ�źŷ�ת */

#endif

/**
 * \brief ������ɻص�����
 */
static void __on_rx_done (void    *p_arg,
                          uint8_t *p_payload,
                          uint16_t size,
                          int16_t  rssi,
                          int8_t   snr)
{
    char  buffer[256] = {0};

    am_zsl42x_lora_memcpy1((uint8_t *)&buffer[0], p_payload, size);

    am_kprintf("snr     : %d\r\n", snr);
    am_kprintf("rssi    : %d\r\n", rssi);
    am_kprintf("payload : %s\r\n\r\n", buffer);
}

/**
 * \brief ���մ���ص�����
 */
static void __on_rx_error (void *p_arg)
{
    am_kprintf("RX error!\r\n");
}

/**
 * \brief ���ճ�ʱ�ص�����
 */
static void __on_rx_timeout_cb (void *p_arg)
{
    am_kprintf("RX Timeout!\r\n");
}

/**
 * \brief cad���ص�����
 */
static void __on_cad_cb (void *p_arg, uint8_t channel_activity_detected)
{
    am_kprintf("CAD done!\r\n");
}

/**
 * \brief LoRa���ճ�ʱ���Գ������
 */
void demo_zsl42x_core_lora_rx_timeout_entry (void)
{
    am_zsl42x_lora_radio_events_t events;

    g_lora_handle = am_zsl42x_lora_inst_init();

    am_zsl42x_lora_memset1((uint8_t *)&events,
                           0x00,
                           sizeof(am_zsl42x_lora_radio_events_t));

    /* ���ûص����� */
    events.pfn_rx_done_cb    = __on_rx_done;
    events.pfn_rx_error_cb   = __on_rx_error;
    events.pfn_rx_timeout_cb = __on_rx_timeout_cb;
    events.pfn_cad_done_cb   = __on_cad_cb;
    am_zsl42x_lora_server_radio_events_set(g_lora_handle, &events);

    /* �ŵ�Ƶ������ */
    am_zsl42x_lora_server_channel_set(g_lora_handle, RADIO_RF_FREQUENCY);

#if __LORA_ENABLE

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
                                        LORA_IQ_INVERSION_ON,
                                        1);

#else
    /* �������� */
    am_zsl42x_lora_server_rx_config_set(g_lora_handle,
                                        AM_ZSL42X_LORA_MODEM_FSK,
                                        FSK_BANDWIDTH,
                                        FSK_DATARATE,
                                        FSK_CODINGRATE,
                                        FSK_BANDWIDTH_AFC,
                                        FSK_PREAMBLE_LENGTH,
                                        FSK_SYMB_TIMEOUT,
                                        FSK_FIX_LENGTH_PAYLOAD_ON,
                                        FSK_CRC,
                                        AM_TRUE,
                                        FSK_FER_HOP,
                                        FSK_FER_HOP_PERIOD,
                                        FSK_IQ_INVERSION,
                                        1);

#endif

    while (1) {

        /* �������ν��� */
        am_zsl42x_lora_server_receive(g_lora_handle, 500);

        am_mdelay(2000);

        am_led_toggle(LED0);
    }
}

/* end of file */
