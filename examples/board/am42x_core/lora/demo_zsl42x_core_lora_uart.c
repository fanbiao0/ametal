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
 * \brief LoRa ����͸������
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-03  zcb, first implementation.
 * - 1.01 20-10-30  yg,  adaptation zsl42x.
 * \endinternal
 */

#include <string.h>
#include "am_board.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_uart_rngbuf.h"

#include "am_zsl42x_lora.h"
#include "am_hwconf_zsl42x_lora.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_RX_BUF_SIZE                64        /**< \brief ���ջ��λ�������С��Ӧ��Ϊ2^n  */
#define UART_TX_BUF_SIZE                64        /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ2^n  */

#define LORA_RF_FREQUENCY               504000000 /**< \brief �ŵ�Ƶ�� */
#define LORA_TX_OUTPUT_POWER            17        /**< \brief ����17dB */
#define LORA_TX_TIMEOUT                 65535     /**< \brief ���ʱʱ�� */
#define LORA_BANDWIDTH                  0         /**< \brief ����125Khz */
#define LORA_SPREADING_FACTOR           AM_ZSL42X_LORA_SERVER_SF8    /**< \brief �ŵ����� SFx */
#define LORA_CODINGRATE                 AM_ZSL42X_LORA_SERVER_CR_4_5 /**< \brief ������ 4/5 */
#define LORA_PREAMBLE_LENGTH            10        /**< \brief ǰ���볤�� */
#define LORA_FIX_LENGTH_PAYLOAD_ON      AM_FALSE  /**< \brief ���̶ܹ����� */
#define LORA_SYMBOL_TIMEOUT             8         /**< \brief ���ų�ʱ�� */
#define LORA_IQ_INVERSION_ON            AM_FALSE  /**< \brief ����IQ�źŷ�ת */

#define ST_IDLE   0
#define ST_TX     1
#define ST_RX     2

/**
 * \brief ���ڵ��Է�����
 */
extern am_uart_handle_t         g_dbg_handle;

/**
 * \brief lora������
 */
static am_zsl42x_lora_handle_t  g_lora_handle;

/**
 * \brief �����������ھ��
 */
static am_uart_rngbuf_handle_t  rngbuf_uart_handle;

/**
 * \brief �ڲ�״̬
 */
static volatile uint8_t         status = ST_RX;

/**
 * \brief ������ɻص�����
 */
static void __on_tx_done (void *p_arg)
{
    am_uart_rngbuf_send(rngbuf_uart_handle,
                        (const uint8_t *)"TX Done!\r\n",
                        strlen("TX Done!\r\n"));

    status = ST_RX;
}

/**
 * \brief ���ͳ�ʱ�ص�����
 */
static void __on_tx_timeout (void *p_arg)
{
    am_uart_rngbuf_send(rngbuf_uart_handle,
                        (const uint8_t *)"TX Timeout!\r\n",
                        strlen("TX Timeout!\r\n"));

    status = ST_RX;
}

/**
 * \brief ���ճ�ʱ�ص�����
 */
static void __on_rx_timeout (void *p_arg)
{
    am_uart_rngbuf_send(rngbuf_uart_handle,
                        (const uint8_t *)"RX Timeout!\r\n",
                        strlen("RX Timeout!\r\n"));
}

/**
 * \brief ���մ���ص�����
 */
static void __on_rx_error (void *p_arg)
{
    am_uart_rngbuf_send(rngbuf_uart_handle,
                        (const uint8_t *)"RX error!\r\n",
                        strlen("RX error!\r\n"));
}

/**
 * \brief ������ɻص�����
 */
static void __on_rx_done (void      *p_arg,
                          uint8_t   *p_payload,
                          uint16_t   size,
                          int16_t    rssi,
                          int8_t     snr)
{
    am_uart_rngbuf_send(rngbuf_uart_handle,
                        (const uint8_t *)"RX done!\r\n",
                        strlen("RX done!\r\n"));

    am_uart_rngbuf_send(rngbuf_uart_handle,
                        p_payload,
                        size);
}

/**
 * \brief LoRa����͸���������
 */
void demo_zsl42x_core_lora_uart_entry (void)
{
    static am_zsl42x_lora_radio_events_t events;
    uint8_t                              uart_rxbuf[UART_RX_BUF_SIZE];
    uint8_t                              uart_txbuf[UART_TX_BUF_SIZE];
    am_uart_rngbuf_dev_t                 uart_ringbuf_dev;

    uint8_t                              buf[UART_RX_BUF_SIZE];
    uint8_t                              nbytes = 0;

    g_lora_handle = am_zsl42x_lora_inst_init();

    am_zsl42x_lora_memset1((uint8_t *)&events,
                           0x00,
                           sizeof(am_zsl42x_lora_radio_events_t));

    /* ���ûص����� */
    events.pfn_tx_done_cb    = __on_tx_done;
    events.pfn_tx_timeout_cb = __on_tx_timeout;
    events.pfn_rx_done_cb    = __on_rx_done;
    events.pfn_rx_error_cb   = __on_rx_error;
    events.pfn_rx_timeout_cb = __on_rx_timeout;
    am_zsl42x_lora_server_radio_events_set(g_lora_handle, &events);

    am_zsl42x_lora_server_channel_set(g_lora_handle, LORA_RF_FREQUENCY);

    rngbuf_uart_handle = am_uart_rngbuf_init(&uart_ringbuf_dev,
                                             g_dbg_handle,
                                             uart_rxbuf,
                                             UART_RX_BUF_SIZE,
                                             uart_txbuf,
                                             UART_TX_BUF_SIZE);

    am_uart_rngbuf_ioctl(rngbuf_uart_handle,
                         AM_UART_RNGBUF_TIMEOUT,
                         (void *)50);

    while (1) {

        if ((nbytes != 0) && (status == ST_TX)) {

            am_zsl42x_lora_server_tx_config_set(g_lora_handle,
                                                AM_ZSL42X_LORA_MODEM_LORA,
                                                LORA_TX_OUTPUT_POWER,
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

            am_zsl42x_lora_server_send(g_lora_handle, buf, nbytes);

            nbytes = 0;
        }

        if (status == ST_RX) {

            am_zsl42x_lora_server_standby(g_lora_handle);

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
                                                AM_TRUE,
                                                0,
                                                0,
                                                LORA_IQ_INVERSION_ON,
                                                AM_TRUE);

            am_zsl42x_lora_server_receive(g_lora_handle, 0);

            status = ST_IDLE;
        }

        if (status == ST_IDLE) {

            nbytes = am_uart_rngbuf_receive(rngbuf_uart_handle,
                                            buf,
                                            UART_RX_BUF_SIZE);

            if (nbytes != 0) {
                status = ST_TX;
            }
        }
    }
}

/* end of file */
