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
 * \brief LoRa LoRa modem registers and bits definitions
 *
 * \internal
 * \par Modification history
 * - 1.0.0 19-10-29  zp,first implementation.
 * - 1.0.1 20-09-23  yg,adaptation zsl42x.
 * \endinternal
 */

#ifndef __AM_ZSL42X_LORA_H
#define __AM_ZSL42X_LORA_H

#include "am_types.h"
#include "am_zsl42x_lpsoftimer.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name LoRa error number
 * @{
 */
#define AM_ZSL42X_LORA_RET_OK          0       /**< \brief ��ȷ */
#define AM_ZSL42X_LORA_RET_ERROR       -1      /**< \brief ���� */
#define AM_ZSL42X_LORA_ESRCH           3       /**< \brief ���̲����� */
#define AM_ZSL42X_LORA_RET_EAGAIN      11      /**< \brief ��Դ�����ã������� */
#define AM_ZSL42X_LORA_ENOMEM          12      /**< \brief �ռ䣨�ڴ棩���� */
#define AM_ZSL42X_LORA_RET_EBUSY       16      /**< \brief �豸����Դæ */
#define AM_ZSL42X_LORA_RET_EINVAL      22      /**< \brief ��Ч���� */
#define AM_ZSL42X_LORA_ENOTSUP         35      /**< \brief ��֧�� */
#define AM_ZSL42X_LORA_ENOBUFS         55      /**< \brief ����ռ䲻�� */
/** @} */

/**
 * \name LoRa bool type
 * @{
 */
#ifndef AM_ZSL42X_LORA_TRUE
#define AM_ZSL42X_LORA_TRUE    1
#endif

#ifndef AM_ZSL42X_LORA_FALSE
#define AM_ZSL42X_LORA_FALSE   0
#endif

/** \brief ��ṹ���Ա��ƫ��*/
#define AM_ZSL42X_LORA_OFFSET(structure, member) ((size_t)(&(((structure *)0)->member)))

/**
 * \brief ͨ���ṹ���Աָ���ȡ�����ýṹ���Ա�Ľṹ��
 */
#define AM_ZSL42X_LORA_CONTAINER_OF(ptr, type, member) \
            ((type *)((char *)(ptr) - AM_ZSL42X_LORA_OFFSET(type,member)))

/**
 * \brief ��������Ԫ�ظ���
 */
#define AM_ZSL42X_LORA_NELEMENTS(array) (sizeof (array) / sizeof ((array) [0]))

/**
 * \brief ��Ƶ����ģʽ
 */
typedef enum {
    AM_ZSL42X_LORA_MODEM_FSK = 0,     /**< \brief FSKģʽ */
    AM_ZSL42X_LORA_MODEM_LORA,        /**< \brief LORAģʽ */
} am_zsl42x_lora_server_radio_modems_t;

/**
 * \brief ��Ƶģ�鹤��״̬
 */
typedef enum {
    AM_ZSL42X_LORA_RF_IDLE_STATE = 0,     /**< \brief ����״̬  */
    AM_ZSL42X_LORA_RF_RX_RUNNING_STATE,   /**< \brief ����״̬  */
    AM_ZSL42X_LORA_RF_TX_RUNNING_STATE,   /**< \brief ����״̬  */
    AM_ZSL42X_LORA_RF_CAD_STATE,          /**< \brief CAD���״̬  */
    AM_ZSL42X_LORA_RF_SLEEP_STATE         /**< \brief ˯��״̬  */
} am_zsl42x_lora_server_radio_state_t;

/**
 * \brief lora ����
 */
typedef enum {
    AM_ZSL42X_LORA_BW_125 = 0,    /**< \brief 125KHZ */
    AM_ZSL42X_LORA_BW_250,        /**< \brief 250KHZ */
    AM_ZSL42X_LORA_BW_500,        /**< \brief 500KHZ */
    AM_ZSL42X_LORA_BW_200,        /**< \brief 200KHz */
    AM_ZSL42X_LORA_BW_400,        /**< \brief 400KHz */
    AM_ZSL42X_LORA_BW_800,        /**< \brief 800KHZ */
    AM_ZSL42X_LORA_BW_1600,       /**< \brief 1600KHZ */
} am_zsl42x_lora_server_bw_t;

/**
 * \brief lora ��Ƶ����
 */
typedef enum {
    AM_ZSL42X_LORA_SERVER_SF5 = 0x05,        /**< \brief ��Ƶ����5 */
    AM_ZSL42X_LORA_SERVER_SF6,               /**< \brief ��Ƶ����6 */
    AM_ZSL42X_LORA_SERVER_SF7,               /**< \brief ��Ƶ����7 */
    AM_ZSL42X_LORA_SERVER_SF8,               /**< \brief ��Ƶ����8 */
    AM_ZSL42X_LORA_SERVER_SF9,               /**< \brief ��Ƶ����9 */
    AM_ZSL42X_LORA_SERVER_SF10,              /**< \brief ��Ƶ����10 */
    AM_ZSL42X_LORA_SERVER_SF11,              /**< \brief ��Ƶ����11 */
    AM_ZSL42X_LORA_SERVER_SF12               /**< \brief ��Ƶ����12 */
} am_zsl42x_lora_server_sf_t;

/**
 * \brief lora ������
 */
typedef enum {
    AM_ZSL42X_LORA_SERVER_CR_4_5    = 0x01,    /**< \brief ������4/5 */
    AM_ZSL42X_LORA_SERVER_CR_4_6,              /**< \brief ������4/6 */
    AM_ZSL42X_LORA_SERVER_CR_4_7,              /**< \brief ������4/7 */
    AM_ZSL42X_LORA_SERVER_CR_4_8,              /**< \brief ������4/8 */
    AM_ZSL42X_LORA_SERVER_CR_LI_4_5,           /**< \brief �����������4/5 */
    AM_ZSL42X_LORA_SERVER_CR_LI_4_6,           /**< \brief �����������4/6 */
    AM_ZSL42X_LORA_SERVER_CR_LI_4_7,           /**< \brief �����������4/7 */
} am_zsl42x_lora_server_cr_t;

/** \brief LoRa˽��ͬ���� */
#define AM_ZSL42X_LORA_SERVER_MAC_PRIVATE_SYNCWORD        0x12

/** \brief LoRa����ͬ���� */
#define AM_ZSL42X_LORA_SERVER_MAC_PUBLIC_SYNCWORD         0x34

/**
 * \brief ��Ƶ�¼��ص�
 */
typedef struct {

    /**
     * \brief ������ɻص�����ԭ��
     *
     * \param[in] p_arg : ����ص������Ĳ���
     *
     * \return    ��
     */
    void (*pfn_tx_done_cb) (void *p_arg);

    /**< \brief ������ɻص����� */
    void *p_tx_done_arg;

    /**
     * \brief ���䳬ʱ�ص�����ԭ��
     *
     * \param[in] p_arg : ����ص������Ĳ���
     *
     * \return    ��
     */
    void (*pfn_tx_timeout_cb) (void *p_arg);

    /**< \brief ���䳬ʱ�ص����� */
    void *p_tx_timeout_arg;

    /**
     * \brief ������ɻص�����ԭ��
     *
     * \param[in] p_arg     : ����ص������Ĳ���
     * \param[in] p_payload : ָ����ջ�����
     * \param[in] size      : ���յ������ݴ�С
     * \param[in] rssi      : ���ո�֡ʱ�ļ���õ� RSSI ֵ [dBm]
     * \param[in] snr       : �����
     *                        FSK : N/A (set to 0)
     *                        LoRa: SNR value in dB
     * \return     ��
     */
    void (*pfn_rx_done_cb) (void       *p_arg,
                            uint8_t    *p_payload,
                            uint16_t    size,
                            int16_t     rssi,
                            int8_t      snr);

    /**< \brief ������ɻص����� */
    void *p_rx_done_arg;

    /**
     * \brief ���ճ�ʱ�ص�����ԭ��
     *
     * \param[in] p_arg : ����ص������Ĳ���
     *
     * \return    ��
     */
    void (*pfn_rx_timeout_cb) (void *p_arg);

    /**< \brief ���ճ�ʱ�ص����� */
    void *p_rx_timeout_arg;

    /**
     * \brief ���մ���ص�����ԭ��
     *
     * \param[in] p_arg : ����ص������Ĳ���
     *
     * \return    ��
     */
    void (*pfn_rx_error_cb) (void *p_arg);

    /**< \brief ���մ���ص����� */
    void *p_rx_error_arg;

    /**
     * \brief FHSS��Ƶ�ص�����ԭ��
     *
     * \param[in] p_arg           : ����ص������Ĳ���
     * \param[in] current_channel : ��ǰ�ŵ��ı��, ��1��ʼ, ÿ��Ƶһ�ε���+1
     *
     * \return    ��
     */
    void (*pfn_fhss_change_channel_cb) (void *p_arg, uint8_t current_channel);

    /**< \brief FHSS��Ƶ�ص����� */
    void *p_fhss_change_channel_arg;

    /**
     * \brief �ŵ���Ծ�����ɻص�����ԭ��
     *
     * \param[in] p_arg                     : ����ص������Ĳ���
     * \param[in] channel_activity_detected : �Ƿ��Ծ[1:�ŵ���Ծ��0���ŵ�����Ծ]
     *
     * \return    ��
     */
    void (*pfn_cad_done_cb) (void *p_arg, uint8_t channel_activity_detected);

    /**< \brief �ŵ���Ծ�����ɻص����� */
    void *p_cad_done_arg;

    /**
     * \brief ��Ч��ͷ�ص�����ԭ��
     *
     * \param[in] p_arg : ����ص������Ĳ���
     *
     * \return    ��
     */
    void (*pfn_valid_header_cb) (void *p_arg);

    /**< \brief ��Ч��ͷ�ص����� */
    void *p_valid_header_arg;

    /**
     * \brief ��Чͬ���ֻص�����ԭ��
     */
    void (*pfn_valid_syncword_cb) (void *p_arg);

    /** \brief ��Чͬ���ֻص����� */
    void *p_valid_syncword_arg;

    /**
     * \brief �����ɻص�ԭ��
     *
     * \param[in] p_arg      : ����ص������Ĳ���
     * \param[in] raw_result : ���ԭʼ���
     * \param[in] rssi       : ���ո�֡ʱ�ļ���õ� RSSI ֵ [dBm]
     * \param[in] snr        : �����
     *                          FSK : N/A (set to 0)
     *                          LoRa: SNR value in dB
     *
     * \return    ��
     */
    void (*pfn_ranging_done_cb) (void    *p_arg,
                                 float    raw_result,
                                 int16_t  rssi,
                                 int8_t   snr);

    /** \brief �����ɻص����� */
    void *p_ranging_done_arg;

    /**
     * \brief ������ص�ԭ��
     * \param[in] p_arg : ����ص������Ĳ���
     * \return ��
     */
    void (*pfn_ranging_error_cb) (void *p_arg);

    /** \brief ������ص����� */
    void *p_ranging_error_arg;

} am_zsl42x_lora_radio_events_t;

/**
 * \brief lora ����������
 */
typedef struct {

    /**
     * \brief ��λ��Ƶģ��
     *
     * \param[in] p_drv  : lora��������
     *
     * \retval AM_ZSL42X_LORA_TRUE  ��λ�ɹ�
     * \retval AM_ZSL42X_LORA_FALSE ��λʧ��
     */
    int (*pfn_reset) (void *p_drv);

    /**
     * \brief ���Ѹ�λ��ʼ��
     *
     * \param[in] p_drv  : lora��������
     * \param[in] p_arg  : ��λ����
     *
     * \retval AM_ZSL42X_LORA_TRUE  : ��λ�ɹ�
     * \retval AM_ZSL42X_LORA_FALSE : ��λʧ��
     */
    int (*pfn_wakeup_init) (void *p_dev, void *p_arg);

    /**
     * \brief ������Ƶģ��
     *
     * \param[in] p_drv  : lora��������
     *
     * \retval AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_wakeup) (void *p_drv);

    /**
     * \brief ��Ƶģʽ����
     *
     * \param[in] p_drv  : lora��������
     * \param[in] modem  : ��Ƶģʽ [0: FSK, 1: LoRa]
     *
     * \retval AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval AM_ZSL42X_LORA_FALSE : ���óɹ�
     */
    int (*pfn_mode_set) (void *p_drv, am_zsl42x_lora_server_radio_modems_t modem);

    /**
     * \brief ��Ƶģʽ��ȡ
     *
     * \param[in] p_drv    : lora��������
     * \param[in] p_modem  : ��Ƶģʽ
     *
     * \retval AM_ZSL42X_LORA_TRUE  : ��ȡ�ɹ�
     * \retval AM_ZSL42X_LORA_FALSE : ��ȡʧ��
     */
    int (*pfn_mode_get) (void *p_drv, am_zsl42x_lora_server_radio_modems_t *p_modem);

    /**
     * \brief ��ȡ��Ƶ״̬
     *
     * \param[in]  p_drv     : lora��������
     * \param[out] p_status  : ��Ƶ״̬
     *
     * \retval AM_ZSL42X_LORA_TRUE  : ��ȡ�ɹ�
     * \retval AM_ZSL42X_LORA_FALSE : ��ȡʧ��
     */
    int (*pfn_status_get) (void *p_drv, am_zsl42x_lora_server_radio_state_t *p_status);

    /**
     * \brief ���ʹ����������
     *
     * \remark ʹ��LoRa����ģʽʱ��֧�� 125��250��500kHz
     *
     * \param[in] p_drv        : lora��������
     * \param[in] modem        : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
     * \param[in] power        : ���ù��� [dBm]
     * \param[in] freq_divider : ���÷�Ƶ�� (FSK only)
     *                            FSK : [Hz]
     *                            LoRa: 0
     * \param[in] bandwidth    : ���ô��� (LoRa only)
     *                            FSK : 0
     *                            LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                   2: 500 kHz, 3: Reserved]
     * \param[in] datarate     : ������������
     *                            FSK : 600..300000 bits/s
     *                            LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                  10: 1024, 11: 2048, 12: 4096  chips]
     * \param[in] coderate     : ���ñ����� (LoRa only)
     *                            FSK : N/A (set to 0)
     *                            LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     * \param[in] preamble_len : ����ǰ���볤��
     *                            FSK : Number of bytes
     *                            LoRa: Length in symbols (the hardware adds 4 more symbols)
     * \param[in] fix_len      : �̶�����ʹ�� [0: variable, 1: fixed]
     * \param[in] crc_on       : CRCУ��ʹ�� [0: OFF, 1: ON]
     * \param[in] freq_hop_on  : �ڲ���Ƶʹ��
     *                            FSK : N/A (set to 0)
     *                            LoRa: [0: OFF, 1: ON]
     * \param[in] hop_period   : ÿ����Ƶ�ķ�������
     *                            FSK : N/A (set to 0)
     *                            LoRa: Number of symbols
     * \param[in] iq_inverted  : ת�� IQ �ź� (LoRa only)
     *                            FSK : N/A (set to 0)
     *                            LoRa: [0: not inverted, 1: inverted]
     * \param[in] timeout      : ���䳬ʱ [ms]
     *
     * \retval    AM_ZSL42X_LORA_TRUE   ���óɹ�
     * \retval    AM_ZSL42X_LORA_FALSE  ����ʧ��
     */
    int (*pfn_tx_config_set) (
        void    *p_drv, am_zsl42x_lora_server_radio_modems_t modem,
        int8_t   power,           uint32_t freq_divider,
        uint32_t bandwidth,       uint32_t datarate,
        uint8_t  coderate,        uint16_t preamble_len,
        uint8_t  fix_len,         uint8_t  crc_on,
        uint8_t  freq_hop_on,     uint8_t  hop_period,
        uint8_t  iq_inverted,     uint32_t timeout);

    /**
     * \brief ���ղ�������
     *
     * \remark ʹ��LoRa����ģʽʱ��֧�� 125��250��500kHz
     *
     * \param[in] p_drv         : lora��������
     * \param[in] modem         : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
     * \param[in] bandwidth     : ���ô���
     *                             FSK : >= 2600 and <= 250000 Hz
     *                             LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                    2: 500 kHz, 3: Reserved]
     * \param[in] datarate      : ������������
     *                             FSK : 600..300000 bits/s
     *                             LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                   10: 1024, 11: 2048, 12: 4096  chips]
     * \param[in] coderate      : ���ñ����� (LoRa only)
     *                             FSK : N/A (set to 0)
     *                             LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     * \param[in] bandwidth_afc : ���� AFC ���� (FSK only)
     *                             FSK : >= 2600 and <= 250000 Hz
     *                             LoRa: N/A (set to 0)
     * \param[in] preamble_len  : ����ǰ���볤��
     *                             FSK : Number of bytes
     *                             LoRa: Length in symbols (the hardware adds 4 more symbols)
     * \param[in] symb_timeout  : ���õ��ν��ճ�ʱֵ (LoRa only)
     *                             FSK : N/A (set to 0)
     *                             LoRa: timeout in symbols
     * \param[in] fix_len       : ���г���ʹ�� [0: variable, 1: fixed]
     * \param[in] payload_len   : ���ø��س��� (�����г���ʹ��ʱ)
     * \param[in] crc_on        : CRCУ��ʹ�� [0: OFF, 1: ON]
     * \param[in] freq_hop_on   : �ڲ�����Ƶʹ��
     *                             FSK : N/A (set to 0)
     *                             LoRa: [0: OFF, 1: ON]
     * \param[in] hop_period    : ÿ����Ƶ�ķ�������
     *                             FSK : N/A (set to 0)
     *                             LoRa: Number of symbols
     * \param[in] iq_inverted   : ת�� IQ �ź� (LoRa only)
     *                             FSK : N/A (set to 0)
     *                             LoRa: [0: not inverted, 1: inverted]
     * \param[in] rx_continuous : ������������ģʽ
     *                             [false: single mode, true: continuous mode]
     *
     * \retval    AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval    AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_rx_config_set) (
        void    *p_drv,  am_zsl42x_lora_server_radio_modems_t modem,
        uint32_t bandwidth,       uint32_t datarate,
        uint8_t  coderate,        uint32_t bandwidth_afc,
        uint16_t preamble_len,    uint16_t symb_timeout,
        uint8_t  fix_len,         uint8_t  payload_len,
        uint8_t  crc_on,          uint8_t  freq_hop_on,
        uint8_t  hop_period,      uint8_t  iq_inverted,
        uint8_t  rx_continuous);

    /**
     * \brief ���ڻ��ѽ�������
     *
     * \param[in] p_drv         : lora��������
     * \param[in] rx_period     : ����ʱ��[ms]
     * \param[in] sleep_period  : ˯��ʱ��[ms]
     *
     * \retval    AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval    AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_rxdutycycle) (void      *p_drv,
                            uint32_t   rx_period,
                            uint32_t   sleep_period);

    /**
     * \brief ������Ƶ����(����������)
     *
     * \param[in] p_drv    : lora��������
     * \param[in] timeout  : ���ճ�ʱ [ms] (0:��������ģʽ��others�����γ�ʱ����ģʽ)
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_receive) (void *p_drv, uint32_t timeout);

    /**
     * \brief ������Ƶ���ͣ����Σ�
     *
     * \param[in] p_drv   : lora��������
     * \param[in] p_data  : ָ����������ݵ�ָ��
     * \param[in] len     : ���������ݳ���
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_send) (void *p_drv, uint8_t *p_data, uint8_t len);

    /**
     * \brief ����˯��ģʽ
     *
     * \param[in] p_drv        :lora��������
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_sleep) (void *p_drv);

    /**
     * \brief �������ģʽ
     *
     * \param[in] p_drv        : lora��������
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_standby) (void *p_drv);

    /**
     * \brief ����һ���ŵ���Ծ���
     *
     * \param[in] p_drv        : lora��������
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_cad_start) (void *p_drv);

    /**
     * \brief ����RFƵ��(ͨ���ŵ�Ƶ��)
     *
     * \param[in] p_drv     : lora��������
     * \param[in] frequency : RFƵ��(Hz)
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_channel_set) (void *p_drv, uint32_t frequency);

    /**
     * \brief ��ȡRFƵ��(ͨ���ŵ�Ƶ��)
     *
     * \param[in]  p_drv  : lora��������
     * \param[out] p_freq : RFƵ��[Hz]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_channel_get) (void *p_drv, uint32_t *p_freq);

    /**
     * \brief ���ͨ���ŵ��Ƿ����
     *
     * \param[in]  p_drv        : lora��������
     * \param[in]  modem        : ��Ƶ����ģʽ
     * \param[in]  freq         : �ŵ�Ƶ��
     * \param[in]  rssi_thresh  : rssi�ٽ�ֵ�������ж��Ƿ���е����ݣ�
     * \param[out] p_state      : ����״̬[0��æµ, 1�� ����]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_is_channel_free) (void                   *p_drv,
                                am_zsl42x_lora_server_radio_modems_t  modem,
                                uint32_t                freq,
                                int16_t                 rssi_thresh,
                                uint8_t                *p_state);

    /**
     * \brief ���Ӳ���Ƿ�֧�ָ�������ƵƵ��
     *
     * \param[in]  p_drv      : lora��������
     * \param[in]  frequency  : Ƶ��
     * \param[out] p_state    : �Ƿ�֧��[0����֧��, 1�� ֧��]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_rf_frequency_check) (void     *p_drv,
                                   uint32_t  frequency,
                                   uint8_t  *p_state);

    /**
     * \brief д�ض���ַ����Ƶ�Ĵ��� (���ֽ�д��)
     *
     * \param[in] p_drv    : lora��������
     * \param[in] addr     : д���ݵ�ַ
     * \param[in] p_data   : д�������
     * \param[in] size     : д�����ݵĴ�С[��λ���ֽ�]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_reg_write) (void      *p_drv,
                          uint16_t   addr,
                          uint8_t   *p_data,
                          uint8_t    size);

    /**
     * \brief ���ض���ַ����Ƶ�Ĵ���(���ֽڶ�ȡ)
     *
     * \param[in]  p_drv    : lora��������
     * \param[in]  addr     : ��ȡ��ַ
     * \param[out] p_data   : ��ȡ������
     * \param[in]  size     : ��ȡ���ݵĴ�С[��λ���ֽ�]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_reg_read) (void       *p_drv,
                         uint16_t    addr,
                         uint8_t    *p_data,
                         uint8_t     size);

    /**
     * \brief ����ʼ��ַд����Ĵ���
     *
     * \param[in] p_drv    : lora��������
     * \param[in] addr     : д���ݵ�ַ
     * \param[in] p_data   : д�������
     * \param[in] size     : д�����ݵĴ�С[��λ���ֽ�]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_buffer_write) (void      *p_drv,
                             uint8_t    addr,
                             uint8_t   *p_data,
                             uint8_t    size);

    /**
     * \brief ����ʼ��ַ������Ĵ���
     *
     * \param[in]  p_drv    : lora��������
     * \param[in]  addr     : ��ȡ��ַ
     * \param[out] p_data   : ��ȡ������
     * \param[in]  size     : ��ȡ���ݵĴ�С[��λ���ֽ�]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_buffer_read) (void     *p_drv,
                            uint8_t   addr,
                            uint8_t  *p_data,
                            uint8_t   size);

    /**
     * \brief  ��������س���
     *
     * \param[in] p_drv         : lora��������
     * \param[in] modem         : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
     * \param[in] payload_size  : ��������ֽ���
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_max_payload_length_set) (void                   *p_dev,
                         am_zsl42x_lora_server_radio_modems_t  modem,
                                       uint8_t                 payload_size);

    /**
     * \brief ���ù�����˽��
     *
     * \param[in] p_drv  : lora��������
     * \param[in] enable : 1 ������ 0 ˽��
     *
     * \note     ֻ������LoRaģʽ
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_public_network_set) (void *p_drv, uint8_t enable);

    /**
     * \brief ������������
     *
     * \param[in] p_drv  : lora��������
     * \param[in] enable : 1:ʹ�ܣ� 0 ����
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : ���óɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_rx_continue_set) (void *p_drv, uint8_t enable);

    /**
     * \brief ����32λ�����
     *
     * \param[in]  p_drv    : lora��������
     * \param[out] p_random : 32λ�����ֵ
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_random) (void *p_drv, uint32_t *p_random);

    /**
     * \brief ����������ض�Ӧ�ķ�����
     *
     * \param[in]  p_drv            : lora��������
     * \param[in]  pkt_len          : ���ذ�����
     * \param[out] p_pkt_symbol_num : ��Ч���صķ�����
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_time_pkt_symbol_get) (void      *p_drv,
                                    uint8_t    pkt_len,
                                    uint16_t  *p_pkt_symbol_num);

    /**
     * \brief ����������ص��ڿ�ʱ�䣨ms��
     *
     * \param[in]  p_drv        : lora��������
     * \param[in]  modem        : ��Ƶģʽ
     * \param[in]  packet_len   : ���ذ�����
     * \param[out] p_time       : �ڿ�ʱ�䣨us��
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_time_on_air_get) (void                   *p_drv,
                  am_zsl42x_lora_server_radio_modems_t  modem,
                                uint8_t                 packet_len,
                                uint64_t               *p_time);

    /**
     * \brief ���÷��ų�ʱʱ��
     *
     * \param[in] p_drv   : lora��������
     * \param[in] ms      :  ���ų�ʱʱ��[��λ��ms]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_symb_timeout_set) (void *p_drv, uint32_t ms);

    /**
     * \brief ��ȡ��ǰ��Ƶ���ò�������µ�������ʱ��,LoRaģʽ
     *
     * \param[in]  p_drv   : lora��������
     * \param[out] p_time  : ��������ʱ��[��λ��us]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_symbol_time_get) (void *p_drv, float *p_time);

    /**
     * \brief ������Ƶ������������ģʽ(����ʹ��)
     *
     * \param[in] p_drv  : lora��������
     * \param[in] freq   : �ŵ�Ƶ��
     * \param[in] power  : ���书�� [dBm]
     * \param[in] time   : ���䳬ʱ [us]
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_tx_continuous_wave) (void     *p_drv,
                                   uint32_t  freq,
                                   int8_t    power,
                                   uint32_t  time);

    /**
     * \brief ��ȡ��ǰ��RSSIֵ
     *
     * \param[in] p_drv         : lora��������
     * \param[in] modem         : ��Ƶ����ģʽ
     * \param[in] p_rssi_value  : RSSIֵ
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_rssi_get) (void                   *p_drv,
           am_zsl42x_lora_server_radio_modems_t  modem,
                         int16_t                *p_rssi_value);

    /**
     * \brief ����ͬ����(syncword)
     *
     * \param[in] p_drv       : lora��������
     * \param[in] p_wordbuff  : ָ��ͬ���������ָ��
     * \param[in] num         : ͬ���ָ���
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_syncword_set) (void     *p_drv,
                             uint8_t  *p_syncword,
                             uint8_t   num);

    /**
     * \brief �ش�(���size��Ϊ0��ת��һ���ָ��ص�FIFO��)
     *
     * \param[in] p_drv    : lora��������
     * \param[in] p_txbuff : �ش�����������ָ��
     * \param[in] len      : ���ݳ���[��λ���ֽ�]
     * \param[in] offset   : ����ƫ��
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_tx_repeat_set) (void      *p_drv,
                              uint8_t   *p_txbuff,
                              uint8_t    len,
                              uint8_t    offset);

    /**
     * \brief ��ȡlora���ݵ�ǰ�����ֽ�����
     *
     * \param[in] p_drv     : lora��������
     * \param[in] p_buffer  : ��ȡ������
     * \param[in] size      �� ���ݳ���
     *
     * \retval   AM_ZSL42X_LORA_TRUE  : �����ɹ�
     * \retval   AM_ZSL42X_LORA_FALSE : ����ʧ��
     */
    int (*pfn_recv_nbbytes_get) (void *p_drv, uint8_t *p_buffer, uint8_t size);

    /**
     * \brief ��ȡ��Ƶ����ʱ��
     *
     * \param[in] p_drv     : lora��������
     * \param[in] p_time    : ��ȡ�Ļ���ʱ��
     *
     * \return              : ���ػ���ʱ��ֵ
     */
    int (*pfn_wakeup_time_get) (void *p_drv);
} am_zsl42x_lora_server_funcs_t;

/**
 * \brief lora ��׼�����豸�ṹ��
 */
typedef struct am_zsl42x_lora_server_dev {

    /** \brief ָ����Ƶ������ */
    am_zsl42x_lora_server_funcs_t        *p_server_funcs;

    /** \brief ָ����Ƶ�ص��¼� */
    const am_zsl42x_lora_radio_events_t  *p_radio_events;

    /** \brief ���ڱ���ײ�Ӳ�������豸�ṹ���ָ��  */
    void                                 *p_hw_drv;
} am_zsl42x_lora_server_dev_t;

/**< \brief lora ��׼�豸��� */
typedef am_zsl42x_lora_server_dev_t *am_zsl42x_lora_server_handle_t;

/**
 * @addtogroup am_if_sx1266_regs_zsl42x_lora
 * @copydoc am_sx1266_regs_zsl42x_lora.h
 * @{
 */

/**
 * @addtogroup am_if_lora
 * @copydoc am_lora.h
 * @{
 */

/**
 * \brief ��Ƶ����֧�ֵĵ��Ʒ�ʽ
 * @{
 */
#define AM_ZSL42X_LORA_RADIO_PACKET_FSK      0x00   /**< \brief FSK���Ƽ������� */
#define AM_ZSL42X_LORA_RADIO_PACKET_LORA     0x01   /**< \brief LORA���Ƽ������� */
/** @} */

/**
 * \brief ���ʱ��Ķ���
 * @{
 */
#define AM_ZSL42X_LORA_RADIO_OSC_STARTUP  0  /**< \brief ��Ƶ˯��ģʽ�Ļ���ʱ��[ms] */
#define AM_ZSL42X_LORA_RADIO_SLEEP_TO_RX  3  /**< \brief ��ƵPLL����ģʽ׼��ʱ��(���ܻ����¶ȱ仯)[ms] */

/**< \brief ��Ƶ��ɻ���ʱ����¶Ȳ����ٽ�ֵ[ms] */
#define AM_ZSL42X_LORA_RADIO_WAKEUP_TIME (AM_ZSL42X_LORA_RADIO_OSC_STARTUP + \
                                          AM_ZSL42X_LORA_RADIO_SLEEP_TO_RX)
/** @} */

/**
 * \brief ����Ƶ��
 * @{
 */
#define AM_ZSL42X_LORA_XTAL_FREQ           32000000
/** @} */

/**
 * \brief �����궨��
 * @{
 */
#define AM_ZSL42X_LORA_LORA_CR_4_5            1
#define AM_ZSL42X_LORA_LORA_CR_4_6            2
#define AM_ZSL42X_LORA_LORA_CR_4_7            3
#define AM_ZSL42X_LORA_LORA_CR_4_8            4

#define AM_ZSL42X_LORA_XTAL_FREQ              32000000
#define AM_ZSL42X_LORA_RX_BUFFER_SIZE         256
/** @} */

/**
 * \brief ��Ƶ��Ƶ�ٽ�
 */
#define __ZSL42X_LORA_RF_MID_BAND_THRESH      525000000

/**
 * \brief ���� RSSI ��Ҫ�õĳ��� (RSSIƫ��ֵ)
 */
#define __ZSL42X_LORA_RSSI_OFFSET_LF          -164
#define __ZSL42X_LORA_RSSI_OFFSET_HF          -157

#define __ZSL42X_LORA_MAX_PAYLOAD_LRNGRH       0XFE


#define AM_ZSL42X_LORA_CRC_IBM_SEED     0xFFFF /** \brief ����IBM����CRC��LFSR��ʼ��ֵ */
#define AM_ZSL42X_LORA_CRC_CCITT_SEED   0x1D0F /** \brief ����CCIT����CRC��LFSR��ʼ��ֵ */

#define AM_ZSL42X_LORA_CRC_POLYNOMIAL_IBM    0x8005  /**< \brief ����IBM CRC�Ķ���ʽ */
#define AM_ZSL42X_LORA_CRC_POLYNOMIAL_CCITT  0x1021  /**< \breif ����CCIT CRC�Ķ���ʽ */

/** \brief void (*pfn) (void *) */
typedef void (*am_zsl42x_lora_pfnvoid_t) (void *);

/**
 *  \brief ���ݰ���Ƶ��������--FSK�������
 */
typedef struct {

    uint32_t datarate;           /**< \brief �������� */
    uint32_t bw;                 /**< \brief ���� */
    uint32_t bw_afc;             /**< \brief AFC���� */
    uint32_t freq_deviation;     /**< \brief ƫ��Ƶ�� */

    uint8_t  addr_filter_enable; /**< \brief ��ַ���ˣ�AM_TRUE:ʹ��, AM_FALSE:���ܣ� */
    uint8_t  node_addr;          /**< \brief �ڵ��ַ */
    uint8_t  broadcast_addr;     /**< \brief �㲥��ַ */
    uint8_t  detector_length;    /**< \brief ��������� */
    uint8_t  syncword_number;    /**< \brief ͬ��������  */
    uint8_t *p_syncword;         /**< \brief ָ��ͬ���������ָ��  */

    uint8_t  whiteng_enable;  /**< \brief whitengʹ��(AM_TRUE:ʹ��, AM_FALSE:����)*/
    uint8_t  rx_continuous;   /**< \brief �������� */
    uint8_t  tx_timeout;      /**< \brief ���ͳ�ʱʱ�� */
    uint8_t  crc_length;      /**< \brief Size of the CRC */

    uint8_t  radio_modshapings;  /**< \brief  modulation shaping parameter */
} am_zsl42x_lora_settings_fsk_t;

/**
 *  ���ݰ���Ƶ��������--lora�������
 */
typedef struct {

    uint8_t  sf;                   /**< \brief ��Ƶ���� */
    uint32_t bw;                   /**< \brief ���� */
    uint8_t  cr;                   /**< \brief ������ */
    uint8_t  lowdatarate_optimize; /**< \brief �����Ż�(AM_TRUE:ʹ��, AM_FALSE:����)*/
    uint8_t  network_num;          /**< \brief ������� */
    uint8_t  freq_hop_on;          /**< \brief ��Ƶʹ��(AM_TRUE:ʹ��, AM_FALSE:����)*/
    uint8_t  hop_period;           /**< \brief ��Ƶ���� */
    uint8_t  symbol_timeout;       /**< \brief ���ų�ʱʱ�� */
    uint32_t tx_timeout;           /**< \brief ���ͳ�ʱʱ�� */
} am_zsl42x_lora_settings_lora_t;

/**
 * \brief zsl42x lora ������Ϣ
 */
typedef struct {

    uint8_t   packet_type;         /**< \brief ���ݰ���Ƶ��������(0��FKS, 1�� LoRa) */
    uint32_t  frequency;           /**< \brief �ŵ�Ƶ�� */
    int8_t    tx_power;            /**< \brief TX���� */
    uint16_t  tx_ramptime;         /**< \brief б��ʱ�� */
    uint8_t   tx_base_addr;        /**< \brief TX������FIFO�еĻ������ַ */
    uint8_t   rx_base_addr;        /**< \brief RX������FIFO�еĻ������ַ */
    uint8_t   idel_mode;           /**< \brief �豸����ʱ����ģʽ���ã�����оƬ���У� */

    uint8_t   iq_inverted_enable; /**< \brief �źŷ�ת(AM_TRUE:ʹ��, AM_FALSE:����)*/
    uint16_t  preamble_length;    /**< \brief ǰ�������ȣ�������*/

    uint8_t   header_type;        /**< \brief ͷ����(0 :�ɱ䳤�Ȱ�, 1:�̶����Ȱ�) */
    uint8_t   payloadlength;      /**< \brief ��Ч���ش�С(����)*/
    uint8_t   crc_enable;         /**< \brief CRCʹ��(AM_TRUE:ʹ��, AM_FALSE:����)*/
    uint8_t   network_current;    /**< \brief ��������(������˽��) */
    uint8_t   network_previous;   /**< \brief ��������(������˽��) */

    am_zsl42x_lora_settings_fsk_t  fsk_setting;    /**< \brief FSK��Ϊ���е�������� */
    am_zsl42x_lora_settings_lora_t lora_setting;   /**< \brief LORA��Ϊ���е�������� */
} am_zsl42x_lora_settings_t;

/**
 * \brief ��ƵFSK������ṹ
 */
typedef struct {
    uint8_t  preamble_detected;
    uint8_t  sync_word_detected;
    int8_t   rssi_value;
    int32_t  afc_value;
    uint8_t  rx_gain;
    uint16_t size;
    uint16_t nb_bytes;
    uint8_t  fifo_thresh;
    uint8_t  chunk_size;
} am_zsl42x_lora_packet_fsk_deal_t;

/**
 * \brief ��ƵLoRa������ṹ
 */
typedef struct {
    int8_t   snr_value;
    int16_t  rssi_value;
    uint8_t  size;
} am_zsl42x_lora_packet_lora_deal_t;

/**
 * \brief zsl42x lora ��ƵоƬ����
 */
typedef enum {
    AM_ZSL42X_LORA_CORE_TYPE_SX1261 = 0,
    AM_ZSL42X_LORA_CORE_TYPE_SX1262,
    AM_ZSL42X_LORA_CORE_TYPE_SX1268
} am_zsl42x_lora_core_type_t;

typedef struct {

    am_zsl42x_lora_core_type_t core_type;   /**< \brief оƬ������� */

//  float    xta_pf;         /**< \brief XTA���ŵ���ѡ��(11.3pF~33.4pF,����0.47pF) */
//  float    xtb_pf;         /**< \brief XTB���ŵ���ѡ��(11.3pF~33.4pF,����0.47pF) */
    uint32_t nss_pin;        /**< \brief Ƭѡ���� */
    uint32_t reset_pin;      /**< \brief ��λ���� */
    uint32_t busy_pin;       /**< \brief BUSY�ź����� */
    uint32_t dio1_pin;       /**< \brief DIO1���� */
    uint32_t dio2_pin;       /**< \brief DIO2���� */
    uint32_t dio3_pin;       /**< \brief DIO3���� */
    uint32_t txen_pin;       /**< \brief txen���� */
    uint32_t rxen_pin;       /**< \brief rxen���� */
    uint32_t frequency;      /**< \brief ZSL42X_LORAʹ�õľ���Ƶ�� */

    uint8_t  calibrate_image;

    uint32_t irq_mask;
    uint32_t dio1_mask;
    uint32_t dio2_mask;
    uint32_t dio3_mask;

    void (*pfn_plfm_init)   (void *p_arg);          /**< \brief ������ų�ʼ������ */
    void (*pfn_plfm_deinit) (void *p_arg);          /**< \brief �������ȥ��ʼ������ */
    int  (*pfn_gpio_set)    (int   pin, int value); /**< \brief ���ŵ�ƽ���ú���ָ�� */
    int  (*pfn_gpio_get)    (int   pin);            /**< \brief ���ŵ�ƽ��ȡ����ָ�� */

    int  (*pfn_dio_irq_enable)  (int pin);          /**< \brief �����ж�ʹ�� */
    int  (*pfn_dio_irq_disable) (int pin);          /**< \brief �����жϽ��� */
} am_zsl42x_lora_devinfo_t;

/** \brief ZSL42X LORA ��������ǰ������ */
typedef struct am_zsl42x_lora_drv_funcs  am_zsl42x_lora_drv_funcs_t;

/**
 * \brief lora �豸�ṹ��
 */
typedef struct am_zsl42x_lora_dev {

    am_zsl42x_lora_server_dev_t     lora_dev;        /**< \brief ����lora ʵ�� */
    am_zsl42x_lora_settings_t       setconfig;       /**< \brief lora���ò��� */
    am_zsl42x_lora_drv_funcs_t     *p_drv_funcs;     /**< \brief �ײ��������� */
    am_zsl42x_lora_pfnvoid_t        p_dio_irq;       /**< \brief DIO�жϺ����� */
    const am_zsl42x_lora_devinfo_t *p_devinfo;       /**< \brief ָ���豸��Ϣ������ָ�� */

    am_lpsoftimer_t            tx_timeout_timer;           /**< \brief ���ͳ�ʱ��ʱ�� */
    am_lpsoftimer_t            rx_timeout_timer;           /**< \brief ���ճ�ʱ��ʱ�� */
    am_lpsoftimer_t            rx_timeout_sync_word_timer; /**< \brief ͬ���ֳ�ʱ��ʱ�� */

    am_zsl42x_lora_packet_lora_deal_t lora_packet_deal;  /**< \brief lora������ṹ */
    am_zsl42x_lora_packet_fsk_deal_t  fsk_packet_deal;   /**< \brief fsk������ṹ */

    uint8_t                    rx_continuous; /**< \brief ��������  */
    uint8_t                    tx_continuous; /**< \brief ��������  */
    uint8_t                    cad_activity;  /**< \brief CAD����� 0������  1����Ծ  */
    uint8_t                    fhss_channel;  /**< \brief ��Ƶ��ǰ�ŵ��ı��  */

    am_zsl42x_lora_server_radio_state_t    state;        /**< \brief ��Ƶ����״̬ */

    /** \brief �շ�������(����5���ֽ�У����Ч֡ͷ) */
    uint8_t                    rx_tx_buffer[AM_ZSL42X_LORA_RX_BUFFER_SIZE + 5];
    uint8_t                   *p_rx_tx_buffer;
} am_zsl42x_lora_dev_t;

/** \brief lora����������� */
typedef am_zsl42x_lora_dev_t *am_zsl42x_lora_handle_t;

/**
 * \brief lora �ײ�������������
 */
struct am_zsl42x_lora_drv_funcs {

    /**
     * \brief  �����Ƿ���Ч
     *
     * \retval 1:��Ч;0:��Ч
     */
    int (*pfn_dio_is_valid) (void *p_drv, int dio);

    /**
     * \brief  �������DIO�����жϱ�־
     */
    int (*pfn_int_flag_clr) (void *p_drv);

    /**
     * \brief  ��λ
     */
    int (*pfn_reset) (void *p_drv);

    /**
     * \brief  ���Ĵ���
     */
    int (*pfn_buf_read) (am_zsl42x_lora_dev_t  *p_dev,
                         uint8_t               *p_addr,
                         uint32_t               addr_len,
                         uint8_t               *p_buff,
                         uint32_t               buff_len);

    /**
     * \brief  д�Ĵ���
     */
    int (*pfn_buf_write) (am_zsl42x_lora_dev_t  *p_dev,
                          uint8_t               *p_addr,
                          uint32_t               addr_len,
                          const uint8_t         *p_buff,
                          uint32_t               buff_len);
};

/*******************************************************************************
    ZSL42X LORA API
*******************************************************************************/

/**
 * \brief zsl42x lora ��Ƶģ���ʼ��
 *
 * \param[in] p_dev       : lora �豸�ṹ���ָ��
 * \param[in] p_devinfo   : ָ��  lora �豸��Ϣ
 * \param[in] p_drv_funcs : ָ�� ���������б�
 *
 * \return lora ����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_zsl42x_lora_handle_t am_zsl42x_lora_init (
                                  am_zsl42x_lora_dev_t         *p_dev,
                            const am_zsl42x_lora_devinfo_t     *p_devinfo,
                                  am_zsl42x_lora_drv_funcs_t   *p_drv_funcs);

/**
 * \brief zsl42x lora��Ƶģ��ȥ��ʼ��
 *
 * \param[in] handle : lora ������
 *
 * \return ��
 */
void am_zsl42x_lora_deinit (am_zsl42x_lora_handle_t handle);

/**
 * \brief Set size elements of dst array with value
 *
 * \remark avoid standard memset function only works on pointers that are aligned
 *
 * \param [out] dst   : Destination array
 * \param [in]  value : Default value
 * \param [in]  size  : Number of bytes to be copied
 */
void am_zsl42x_lora_memset1 (uint8_t *p_dst, uint8_t value, uint32_t size);

/**
 * \brief Copies size elements of src array to dst array
 *
 * \remark avoid standard memset function only works on pointers that are aligned
 *
 * \param [out] dst  :  Destination array
 * \param [in]  src  : Source array
 * \param [in]  size : Number of bytes to be copied
 */
void am_zsl42x_lora_memcpy1 (uint8_t *p_dst, const uint8_t *p_src, uint32_t size);

/**
 * \brief �ص��¼�����
 *
 * \param[in] handle   : lora���
 * \param[in] p_events : ָ��ص��¼���ָ��
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 *
 */
am_static_inline
int am_zsl42x_lora_server_radio_events_set (am_zsl42x_lora_handle_t   handle,
                                const am_zsl42x_lora_radio_events_t  *p_events)
{
    if (p_events == NULL) {
        return -AM_ZSL42X_LORA_RET_EINVAL;
    }

    handle->lora_dev.p_radio_events = p_events;

    return AM_ZSL42X_LORA_TRUE;
}

/**
 * \brief ��λ
 *
 * \param[in] handle : lora���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_reset (am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_reset == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_reset(handle->lora_dev.p_hw_drv);
}

/**
 * \brief ���ѳ�ʼ��
 *
 * \param[in] handle : lora���
 * \param[in] p_arg  : ��ʼ������
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_wakeup_init(am_zsl42x_lora_handle_t handle, void *p_arg)
{
    if (handle->lora_dev.p_server_funcs->pfn_wakeup_init == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_wakeup_init(handle->lora_dev.p_hw_drv, p_arg);
}

/**
 * \brief ������Ƶģ��
 *
 * \param[in] handle : lora���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_wakeup (am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_wakeup == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_wakeup(handle->lora_dev.p_hw_drv);
}

/**
 * \brief ��Ƶģʽ����
 *
 * \param[in] handle : lora���
 * \param[in] modem  : ��Ƶģʽ [0: FSK, 1: LoRa]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_modem_set(am_zsl42x_lora_handle_t  handle,
                       am_zsl42x_lora_server_radio_modems_t  modem)
{
    if (handle->lora_dev.p_server_funcs->pfn_mode_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_mode_set(handle->lora_dev.p_hw_drv, modem);
}

/**
 * \brief ��Ƶģʽ����
 *
 * \param[in] handle   : lora���
 * \param[in] p_modem  : ��Ƶģʽ [0: FSK, 1: LoRa]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_modem_get(am_zsl42x_lora_handle_t    handle,
                       am_zsl42x_lora_server_radio_modems_t   *p_modem)
{
    if (handle->lora_dev.p_server_funcs->pfn_mode_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_mode_get(handle->lora_dev.p_hw_drv, p_modem);
}

/**
 * \brief ��ȡ��Ƶģ��״̬
 *
 * \param[in]  handle   : lora���
 * \param[out] p_status : ״̬����
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_status_get (am_zsl42x_lora_handle_t    handle,
                        am_zsl42x_lora_server_radio_state_t     *p_status)
{
    if (handle->lora_dev.p_server_funcs->pfn_status_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_status_get(handle->lora_dev.p_hw_drv, p_status);
}

/**
 * \brief ���ղ�������
 *
 * \remark ʹ��LoRa����ģʽʱ��֧�� 125��250��500kHz
 *
 * \param[in] handle        : lora��������
 * \param[in] modem         : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
 * \param[in] bandwidth     : ���ô���
 *                             FSK : >= 2600 and <= 250000 Hz
 *                             LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                    2: 500 kHz, 3: Reserved]
 * \param[in] datarate      : ������������
 *                             FSK : 600..300000 bits/s
 *                             LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                   10: 1024, 11: 2048, 12: 4096  chips]
 * \param[in] coderate      : ���ñ����� (LoRa only)
 *                             FSK : N/A (set to 0)
 *                             LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param[in] bandwidth_afc : ���� AFC ���� (FSK only)
 *                             FSK : >= 2600 and <= 250000 Hz
 *                             LoRa: N/A (set to 0)
 * \param[in] preamble_len  : ����ǰ���볤��
 *                             FSK : Number of bytes
 *                             LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param[in] symb_timeout  : ���õ��ν��ճ�ʱֵ (LoRa only)
 *                             FSK : N/A (set to 0)
 *                             LoRa: timeout in symbols
 * \param[in] fix_len       : ���г���ʹ�� [0: variable, 1: fixed]
 * \param[in] payload_len   : ���ø��س��� (�����г���ʹ��ʱ)
 * \param[in] crc_on        : CRCУ��ʹ�� [0: OFF, 1: ON]
 * \param[in] freq_hop_on   : �ڲ�����Ƶʹ��
 *                             FSK : N/A (set to 0)
 *                             LoRa: [0: OFF, 1: ON]
 * \param[in] hop_period    : ÿ����Ƶ�ķ�������
 *                             FSK : N/A (set to 0)
 *                             LoRa: Number of symbols
 * \param[in] iq_inverted   : ת�� IQ �ź� (LoRa only)
 *                             FSK : N/A (set to 0)
 *                             LoRa: [0: not inverted, 1: inverted]
 * \param[in] rx_continuous : ������������ģʽ
 *                             [false: single mode, true: continuous mode]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_rx_config_set(
    am_zsl42x_lora_handle_t handle,  am_zsl42x_lora_server_radio_modems_t  modem,
    uint32_t         bandwidth,      uint32_t           datarate,
    uint8_t          coderate,       uint32_t           bandwidth_afc,
    uint16_t         preamble_len,   uint16_t           symb_timeout,
    uint8_t          fix_len,        uint8_t            payload_len,
    uint8_t          crc_on,         uint8_t            freq_hop_on,
    uint8_t          hop_period,     uint8_t            iq_inverted,
    uint8_t          rx_continuous)
{
    if (handle->lora_dev.p_server_funcs->pfn_rx_config_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_rx_config_set(
        handle->lora_dev.p_hw_drv, modem,
        bandwidth,                 datarate,
        coderate,                  bandwidth_afc,
        preamble_len,              symb_timeout,
        fix_len,                   payload_len,
        crc_on,                    freq_hop_on,
        hop_period,                iq_inverted,
        rx_continuous);
}

/**
 * \brief ���ʹ����������
 *
 * \remark ʹ��LoRa����ģʽʱ��֧�� 125��250��500kHz
 *
 * \param[in] handle       : lora��������
 * \param[in] modem        : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
 * \param[in] power        : ���ù��� [dBm]
 * \param[in] freq_divider : ���÷�Ƶ�� (FSK only)
 *                            FSK : [Hz]
 *                            LoRa: 0
 * \param[in] bandwidth    : ���ô��� (LoRa only)
 *                            FSK : 0
 *                            LoRa: [0: 125 kHz, 1: 250 kHz,
 *                                   2: 500 kHz, 3: Reserved]
 * \param[in] datarate     : ������������
 *                            FSK : 600..300000 bits/s
 *                            LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
 *                                  10: 1024, 11: 2048, 12: 4096  chips]
 * \param[in] coderate     : ���ñ����� (LoRa only)
 *                            FSK : N/A (set to 0)
 *                            LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 * \param[in] preamble_len : ����ǰ���볤��
 *                            FSK : Number of bytes
 *                            LoRa: Length in symbols (the hardware adds 4 more symbols)
 * \param[in] fix_len      : �̶�����ʹ�� [0: variable, 1: fixed]
 * \param[in] crc_on       : CRCУ��ʹ�� [0: OFF, 1: ON]
 * \param[in] freq_hop_on  : �ڲ���Ƶʹ��
 *                            FSK : N/A (set to 0)
 *                            LoRa: [0: OFF, 1: ON]
 * \param[in] hop_period   : ÿ����Ƶ�ķ�������
 *                            FSK : N/A (set to 0)
 *                            LoRa: Number of symbols
 * \param[in] iq_inverted  : ת�� IQ �ź� (LoRa only)
 *                            FSK : N/A (set to 0)
 *                            LoRa: [0: not inverted, 1: inverted]
 * \param[in] timeout      : ���䳬ʱ [ms]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_tx_config_set(
    am_zsl42x_lora_handle_t handle, am_zsl42x_lora_server_radio_modems_t modem,
    int8_t           power,         uint32_t          freq_divider,
    uint32_t         bandwidth,     uint32_t          datarate,
    uint8_t          coderate,      uint16_t          preamble_len,
    uint8_t          fix_len,       uint8_t           crc_on,
    uint8_t          freq_hop_on,   uint8_t           hop_period,
    uint8_t          iq_inverted,   uint32_t          timeout)
{
    if (handle->lora_dev.p_server_funcs->pfn_tx_config_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_tx_config_set(
        handle->lora_dev.p_hw_drv, modem,
        power,            freq_divider,
        bandwidth,        datarate,
        coderate,         preamble_len,
        fix_len,          crc_on,
        freq_hop_on,      hop_period,
        iq_inverted,      timeout);
}

/**
 * \brief ���ڻ��ѽ�������
 *
 * \param[in] handle       : lora���
 * \param[in] rx_period    : ����ʱ��(ms)
 * \param[in] sleep_period : ˯��ʱ��(ms)
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_rxdutycycle_set (am_zsl42x_lora_handle_t handle,
                                           uint32_t                rx_period,
                                           uint32_t                sleep_period)
{
    if (handle->lora_dev.p_server_funcs->pfn_rxdutycycle == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_rxdutycycle(handle->lora_dev.p_hw_drv,
                                                            rx_period,
                                                            sleep_period);
}

/**
 * \brief ������Ƶ����(����������)
 *
 * \param[in] handle  : lora���
 * \param[in] timeout : ���ճ�ʱ [ms] (0:��������ģʽ��others�����γ�ʱ����ģʽ)
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_receive (am_zsl42x_lora_handle_t handle, uint32_t timeout)
{
    if (handle->lora_dev.p_server_funcs->pfn_receive == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_receive(handle->lora_dev.p_hw_drv,
                                                        timeout);
}

/**
 * \brief ������Ƶ���ݣ����Σ�
 *
 * \param[in] handle  : lora���
 * \param[in] p_data  : ָ����������ݵ�ָ��
 * \param[in] len     : ���������ݳ���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_send (am_zsl42x_lora_handle_t handle,
                                uint8_t                *p_data,
                                uint8_t                 len)
{
    if (handle->lora_dev.p_server_funcs->pfn_send == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_send(handle->lora_dev.p_hw_drv,
                                                     p_data, len);
}

/**
 * \brief ����˯��ģʽ
 *
 * \param[in] handle     : lora���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_sleep (am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_sleep == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_sleep(handle->lora_dev.p_hw_drv);
}

/**
 * \brief �������ģʽ
 * \param[in] handle   : lora���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_standby (am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_standby == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_standby(handle->lora_dev.p_hw_drv);
}

/**
 * \brief ����һ���ŵ���Ծ���
 *
 * \param[in] handle  : lora���
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */

am_static_inline
int am_zsl42x_lora_server_cad_start (am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_cad_start == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_cad_start(handle->lora_dev.p_hw_drv);
}

/**
 * \brief ����RFƵ��(ͨ���ŵ�Ƶ��)
 *
 * \param[in] handle           : lora���
 * \param[in] frequency        : RFƵ��[��λ��Hz]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_channel_set (am_zsl42x_lora_handle_t handle,
                                       uint32_t                frequency)
{
    if (handle->lora_dev.p_server_funcs->pfn_channel_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_channel_set(handle->lora_dev.p_hw_drv,
                                                            frequency);
}

/**
 * \brief ��ȡRFƵ��(ͨ���ŵ�Ƶ��)
 *
 * \param[in]  handle           : lora���
 * \param[out] p_freq           : RFƵ��[��λ��Hz]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_channel_get (am_zsl42x_lora_handle_t handle,
                                       uint32_t               *p_freq)
{
    if (handle->lora_dev.p_server_funcs->pfn_channel_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_channel_get(handle->lora_dev.p_hw_drv,
                                                            p_freq);
}

/**
 * \brief ���ͨ���ŵ��Ƿ����
 *
 * \param[in]  handle           : lora���
 * \param[in]  modem            : ��Ƶ����ģʽ
 * \param[in]  freq             : �ŵ�Ƶ��
 * \param[in]  rssi_thresh      : rssi�ٽ�ֵ�������ж��Ƿ���е����ݣ�
 * \param[out] p_state          : ����״̬[0��æµ, 1�� ����]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_is_channel_free (am_zsl42x_lora_handle_t    handle,
                             am_zsl42x_lora_server_radio_modems_t     modem,
                                           uint32_t                   freq,
                                           int16_t                    rssi_thresh,
                                           uint8_t                   *p_state)
{
    if (handle->lora_dev.p_server_funcs->pfn_is_channel_free == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_is_channel_free(handle->lora_dev.p_hw_drv,
                                                                modem,
                                                                freq,
                                                                rssi_thresh,
                                                                p_state);
}

/**
 * \brief ���Ӳ���Ƿ�֧�ָ�������ƵƵ��
 *
 * \param[in]  handle           : lora���
 * \param[in]  frequency        : Ƶ��
 * \param[out] p_state          : �Ƿ�֧��[0����֧��, 1�� ֧��]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_rf_frequency_check (am_zsl42x_lora_handle_t  handle,
                                              uint32_t                 frequency,
                                              uint8_t                 *p_state)
{
    if (handle->lora_dev.p_server_funcs->pfn_rf_frequency_check == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_rf_frequency_check(handle->lora_dev.p_hw_drv,
                                                                   frequency,
                                                                   p_state);
}

/**
 * \brief д�ض���ַ����Ƶ�Ĵ���
 *
 * \param[in] handle  : lora���
 * \param[in] address : д���ݵĵ�ַ
 * \param[in] p_data  : ��Ҫд�������
 * \param[in] size    : д�����ݵĴ�С[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_reg_write(am_zsl42x_lora_handle_t  handle,
                                    uint16_t                 address,
                                    uint8_t                 *p_data,
                                    uint8_t                  size)
{
    if (handle->lora_dev.p_server_funcs->pfn_reg_write == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_reg_write(handle->lora_dev.p_hw_drv,
                                                          address,
                                                          p_data,
                                                          size);
}

/**
 * \brief ���ض���ַ����Ƶ�Ĵ���
 *
 * \param[in] handle  : lora���
 * \param[in] address : �����ݵĵ�ַ
 * \param[in] p_data  : ��ȡ������
 * \param[in] size    : ��ȡ���ݵĴ�С[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_reg_read(am_zsl42x_lora_handle_t  handle,
                                   uint16_t                 address,
                                   uint8_t                 *p_data,
                                   uint8_t                  size)
{
    if (handle->lora_dev.p_server_funcs->pfn_reg_read == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_reg_read(handle->lora_dev.p_hw_drv,
                                                         address,
                                                         p_data,
                                                         size);
}

/**
 * \brief ����ʼ��ַд����Ĵ���
 *
 * \param[in] handle  : lora���
 * \param[in] address : �����ݵĵ�ַ
 * \param[in] p_data  : ��ȡ������
 * \param[in] size    : ��ȡ���ݵĴ�С[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_buffer_write (am_zsl42x_lora_handle_t  handle,
                                        uint8_t                  address,
                                        uint8_t                 *p_data,
                                        uint8_t                  size)
{
    if (handle->lora_dev.p_server_funcs->pfn_buffer_write == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_buffer_write(handle->lora_dev.p_hw_drv,
                                                             address,
                                                             p_data,
                                                             size);
}

/**
 * \brief ����ʼ��ַ������Ĵ���
 *
 * \param[in] handle  : lora���
 * \param[in] address : �����ݵĵ�ַ
 * \param[in] p_data  : ��ȡ������
 * \param[in] size    : ��ȡ���ݵĴ�С[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_buffer_read (am_zsl42x_lora_handle_t  handle,
                                       uint8_t                  address,
                                       uint8_t                 *p_data,
                                       uint8_t                  size)
{
    if (handle->lora_dev.p_server_funcs->pfn_buffer_read == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_buffer_read(handle->lora_dev.p_hw_drv,
                                                            address,
                                                            p_data,
                                                            size);
}

/**
 * \brief ���������س���
 *
 * \param[in] handle     : lora���
 * \param[in] modem      : ʹ�õ���Ƶģʽ [0: FSK, 1: LoRa]
 * \param[in] length_max : ��������ֽ���[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_max_payload_length_set(am_zsl42x_lora_handle_t  handle,
                                   am_zsl42x_lora_server_radio_modems_t   modem,
                                                 uint8_t                  length_max)
{
    if (handle->lora_dev.p_server_funcs->pfn_max_payload_length_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_max_payload_length_set(handle->lora_dev.p_hw_drv,
                                                                       modem,
                                                                       length_max);
}

/**
 * \brief ������������ (������˽��)
 *
 * \param[in] handle  : lora���
 * \param[in] enable  : 1 : ����, 0 : ˽��
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_public_network_set(am_zsl42x_lora_handle_t   handle,
                                             uint8_t                   enable)

{
    if (handle->lora_dev.p_server_funcs->pfn_public_network_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_public_network_set(handle->lora_dev.p_hw_drv,
                                                                   enable);
}

/**
 * \brief ������������
 *
 * \param[in] handle  : lora���
 * \param[in] enable  : 1 �����������գ� 0��������������
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_rx_continuous_set (am_zsl42x_lora_handle_t handle,
                                             uint8_t                 enable)
{
    if (handle->lora_dev.p_server_funcs->pfn_rx_continue_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_rx_continue_set(handle->lora_dev.p_hw_drv,
                                                                enable);
}

/**
 * \brief ����32λ�����
 *
 * \param[in]  handle    : lora���
 * \param[out] p_random  : 32λ�����ֵ
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_random (am_zsl42x_lora_handle_t handle, uint32_t *p_random)
{
    if (handle->lora_dev.p_server_funcs->pfn_random == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_random(handle->lora_dev.p_hw_drv,
                                                       p_random);
}

/**
 * \brief ����������ض�Ӧ�ķ�����
 *
 * \param[in]  handle           : lora���
 * \param[in]  pkt_len          : ���ذ�����
 * \param[out] p_pkt_symbol_num : ��Ч���صķ�����
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_time_pkt_symbol_get (am_zsl42x_lora_handle_t  handle,
                                               uint8_t                  pkt_len,
                                               uint16_t       *p_pkt_symbol_num)
{
    if (handle->lora_dev.p_server_funcs->pfn_time_pkt_symbol_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_time_pkt_symbol_get(handle->lora_dev.p_hw_drv,
                                                                    pkt_len,
                                                                    p_pkt_symbol_num);
}

/**
 * \brief ����������ص��ڿ�ʱ�䣨ms��
 *
 * \param[in]  handle      : lora���
 * \param[in]  modem       : ��Ƶģʽ
 * \param[in]  packet_len  : ���ذ�����
 * \param[out] p_time      : �ڿ�ʱ�䣨ms��
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_time_on_air_get (am_zsl42x_lora_handle_t handle,
                             am_zsl42x_lora_server_radio_modems_t  modem,
                                           uint8_t                 packet_len,
                                           uint64_t               *p_time)
{
    if (handle->lora_dev.p_server_funcs->pfn_time_on_air_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_time_on_air_get(handle->lora_dev.p_hw_drv,
                                                                modem,
                                                                packet_len,
                                                                p_time);
}

/**
 * \brief ���÷��ų�ʱʱ��
 *
 * \param[in] handle   : lora���
 * \param[in] timeout  : ���ų�ʱʱ��[��λ��ms]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_symb_timeout_set (am_zsl42x_lora_handle_t handle,
                                            uint32_t                timeout)
{
    if (handle->lora_dev.p_server_funcs->pfn_symb_timeout_set== NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_symb_timeout_set(handle->lora_dev.p_hw_drv,
                                                                 timeout);
}

/**
 * \brief ��ȡ��ǰ��Ƶ���ò�������µ�������ʱ��,LoRaģʽ
 *
 * \param[in]  handle : lora���
 * \param[out] p_time : ��������ʱ��[��λ��ms]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_symbol_time_get (am_zsl42x_lora_handle_t handle,
                                           float                  *p_time)
{
    if (handle->lora_dev.p_server_funcs->pfn_symbol_time_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_symbol_time_get(handle->lora_dev.p_hw_drv,
                                                                p_time);
}

/**
 * \brief ������Ƶ������������ģʽ
 *
 * \param[in] handle : lora���
 * \param[in] freq   : �ŵ�Ƶ��
 * \param[in] power  : ���书�� [dBm]
 * \param[in] time   : ���䳬ʱ [ms]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_tx_continuous_wave (am_zsl42x_lora_handle_t handle,
                                              uint32_t                freq,
                                              int8_t                  power,
                                              uint32_t                time)
{
    if (handle->lora_dev.p_server_funcs->pfn_tx_continuous_wave == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_tx_continuous_wave(handle->lora_dev.p_hw_drv,
                                                                   freq,
                                                                   power,
                                                                   time);
}

/**
 * \brief ��ȡ��ǰ��RSSIֵ
 *
 * \param[in] handle        : lora���
 * \param[in] modem         : ��Ƶ����ģʽ
 * \param[in] p_rssi_value  : RSSIֵ
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_rssi_get (am_zsl42x_lora_handle_t  handle,
                      am_zsl42x_lora_server_radio_modems_t   modem,
                                    int16_t                 *p_rssi_value)
{
    if (handle->lora_dev.p_server_funcs->pfn_rssi_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_rssi_get(handle->lora_dev.p_hw_drv,
                                                         modem,
                                                         p_rssi_value);
}

/**
 * \brief ����ͬ����(syncword)
 *
 * \param[in] handle     : lora���
 * \param[in] p_syncword : ָ��ͬ���������ָ��
 * \param[in] num        : ͬ���ָ���[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_syncword_set (am_zsl42x_lora_handle_t handle,
                                        uint8_t                *p_syncword,
                                        uint8_t                 num)
{
    if (handle->lora_dev.p_server_funcs->pfn_syncword_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_syncword_set(handle->lora_dev.p_hw_drv,
                                                             p_syncword,
                                                             num);
}

/**
 * \brief �ش�(���size��Ϊ0��ת��һ���ָ��ص�FIFO��)
 *
 * \param[in] handle   : lora���
 * \param[in] p_txbuff : �ش�����������ָ��
 * \param[in] len      : ��������[��λ���ֽ�]
 * \param[in] offset   : ����ƫ��
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_tx_repeat_set (am_zsl42x_lora_handle_t handle,
                                         uint8_t                *p_txbuff,
                                         uint8_t                 len,
                                         uint8_t                 offset)
{
    if (handle->lora_dev.p_server_funcs->pfn_tx_repeat_set == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_tx_repeat_set(handle->lora_dev.p_hw_drv,
                                                              p_txbuff,
                                                              len,
                                                              offset);
}

/**
 * \brief ��ȡfifo�е�ǰ�����ֽ�����(loranetЭ��ջʹ��)
 *
 * \param[in] handle    : lora��������
 * \param[in] p_buffer  : ��ȡ������
 * \param[in] nbbytes   �� ���ݳ���[��λ���ֽ�]
 *
 * \retval   AM_ZSL42X_LORA_TRUE        : �����ɹ�
 * \retval   AM_ZSL42X_LORA_FALSE       : ����ʧ��
 * \retval   -AM_ZSL42X_LORA_ENOTSUP    �� ��֧��
 * \retval   -AM_ZSL42X_LORA_RET_EINVAL : ��Ч����
 */
am_static_inline
int am_zsl42x_lora_server_recv_nbbytes_get(am_zsl42x_lora_handle_t  handle,
                                           uint8_t                 *p_buffer,
                                           uint8_t                  nbbytes)
{
    if (handle->lora_dev.p_server_funcs->pfn_recv_nbbytes_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_recv_nbbytes_get(handle->lora_dev.p_hw_drv,
                                                                 p_buffer,
                                                                 nbbytes);
}

/**
 * \brief ��ȡ����ʱ��
 *
 * \param[in] handle : lora��������
 *
 * \return ����ʱ�䣬-AM_LORA_ENOTSUPֵ��ʾ��֧�ָò���
 */
am_static_inline
int am_zsl42x_lora_server_wakeup_time_get(am_zsl42x_lora_handle_t handle)
{
    if (handle->lora_dev.p_server_funcs->pfn_wakeup_time_get == NULL) {
        return -AM_ZSL42X_LORA_ENOTSUP;
    }

    return handle->lora_dev.p_server_funcs->pfn_wakeup_time_get(handle->lora_dev.p_hw_drv);
}

/*******************************************************************************
    API END
*******************************************************************************/

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSL42X_LORA_H */

/* end of file */
