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
 * \brief LoRa modem registers and bits definitions
 *
 * \internal
 * \par Modification history
 * - 1.0.0 20-03-25  enf,first implementation.
 * - 1.0.1 20-09-23  yg, adaptation zsl42x.
 * \endinternal
 */

#ifndef __AM_ZSL42X_LORA_REG_H
#define __AM_ZSL42X_LORA_REG_H

#include "am_types.h"
#include "am_zsl42x_lora.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief LoRa ������ö��
 */
typedef enum {

    /** \brief Commands Selecting the Operating Modes of the Radio */
    AM_ZSL42X_LORA_OPCODE_SET_SLEEP              = 0x84, /** \brief ˯��ģʽ���� */
    AM_ZSL42X_LORA_OPCODE_SET_STANDBY            = 0x80, /** \brief ����ģʽ���� */
    AM_ZSL42X_LORA_OPCODE_SET_FS                 = 0xC1, /** \brief FSģʽ���� */
    AM_ZSL42X_LORA_OPCODE_SET_TX                 = 0x83, /** \brief �������� */
    AM_ZSL42X_LORA_OPCODE_SET_RX                 = 0x82, /** \brief �������� */
    AM_ZSL42X_LORA_OPCODE_STOPTIMERONPREAMBLE    = 0x9F, /** \brief ֹͣ��ʱ��� */
    AM_ZSL42X_LORA_OPCODE_SET_RXDUTYCYCLE        = 0x94, /** \brief ���ڻ������� */
    AM_ZSL42X_LORA_OPCODE_SET_CAD                = 0xC5, /** \brief �ŵ�������� */
    AM_ZSL42X_LORA_OPCODE_SET_TXCONTINUOUSWAVE   = 0xD1, /** \brief ���а��Ĳ������� */
    AM_ZSL42X_LORA_OPCODE_SET_TXINFINITEPREAMBLE = 0xD2, /** \brief �������� */
    AM_ZSL42X_LORA_OPCODE_SET_REGULATORMODE      = 0x96, /** \brief ���õ���������ѡ�� */
    AM_ZSL42X_LORA_OPCODE_CALIBRATE              = 0x89, /** \brief У׼ʹ�� */
    AM_ZSL42X_LORA_OPCODE_CALIBRATEIMAGE         = 0x98, /** \brief �ض�Ƶ�εľ�ƵУ׼ */
    AM_ZSL42X_LORA_OPCODE_SET_PACONFIG           = 0x95, /** \brief PA���� */
    AM_ZSL42X_LORA_OPCODE_SET_RXTXFALLBACKMODE   = 0x93, /** \brief ���ͽ�����ɽ����ģʽ */

    /** \brief Register and Buffer Access Commands */
    AM_ZSL42X_LORA_OPCODE_REGISTER_WRITE         = 0x0D, /** \brief д�Ĵ��� */
    AM_ZSL42X_LORA_OPCODE_REGISTER_READ          = 0x1D, /** \brief ���Ĵ��� */
    AM_ZSL42X_LORA_OPCODE_BUFFER_WRITE           = 0x0E, /** \brief д���ݵ�FIFO�� */
    AM_ZSL42X_LORA_OPCODE_BUFFER_READ            = 0x1E, /** \brief ��FIFO�ж�ȡ���� */

    /** \brief DIO and IRQ Control */
    AM_ZSL42X_LORA_OPCODE_SET_DIOIRQ_PARAMS = 0x08, /** \brief DIOx�ж�ʹ�� */
    AM_ZSL42X_LORA_OPCODE_GET_IRQSTATUS     = 0x12, /** \brief ��ȡDIO�ж�״̬ */
    AM_ZSL42X_LORA_OPCODE_CLEAR_IRQSTATUS   = 0x02, /** \brief ���DIO�ж�״̬ */
    AM_ZSL42X_LORA_OPCODE_SET_DIO2_RFSWITCH = 0x9D, /** \brief DIO2����RF�л����� */
    AM_ZSL42X_LORA_OPCODE_SET_DIO3_TCXOCTRL = 0x97, /** \brief DIO3��Ϊ�ⲿTCXO���õ�ѹ���� */

    /** \brief RF, Modulation and Packet Commands */
    AM_ZSL42X_LORA_OPCODE_SET_RF_FREQUENCY       = 0x86, /** \brief ����RFƵ�� */
    AM_ZSL42X_LORA_OPCODE_SET_PACKET_TYPE        = 0x8A, /** \brief ����֡���� */
    AM_ZSL42X_LORA_OPCODE_GET_PACKET_TYPE        = 0x11, /** \brief ��ȡ֡���� */
    AM_ZSL42X_LORA_OPCODE_SET_TX_PARAMS          = 0x8E, /** \brief ����TX���� */
    AM_ZSL42X_LORA_OPCODE_SET_MODULATION_PARAMS  = 0x8B, /** \brief ���õ��Ʋ���*/
    AM_ZSL42X_LORA_OPCODE_SET_PACKET_PARAMS      = 0x8C, /** \brief �������ݰ���ز��� */
    AM_ZSL42X_LORA_OPCODE_SET_CAD_PARAMS         = 0x88, /** \brief ����CAD��ز��� */
    AM_ZSL42X_LORA_OPCODE_SET_BUFFER_BASEADDRESS = 0x8F, /** \brief ���շ��ͻ������Ļ���ַ */
    AM_ZSL42X_LORA_OPCODE_SET_LORA_SYMBNUM_TIMEOUT = 0xA0, /** \brief ���ó�ʱ��������ʱ�� */

    /** \brief  Status Commands */
    AM_ZSL42X_LORA_OPCODE_GET_STATUS          = 0xC0, /** \brief ��ȡоƬ״̬ */
    AM_ZSL42X_LORA_OPCODE_GET_RSSI_INST       = 0x15, /** \brief ��ȡ˲��RSSI���� */
    AM_ZSL42X_LORA_OPCODE_GET_RXBUFFER_STATUS = 0x13, /** \brief ��ȡ����buffer״̬  */
    AM_ZSL42X_LORA_OPCODE_GET_PACKET_STATUS   = 0x14, /** \brief ��ȡ����Ϣ */
    AM_ZSL42X_LORA_OPCODE_GET_STATS           = 0x10, /** \brief ��ȡ��󼸸����ݰ���Ϣ���� */
    AM_ZSL42X_LORA_OPCODE_RESET_STATS         = 0x00, /** \brief ��λ0x10����õ���ֵ */
    AM_ZSL42X_LORA_OPCODE_GET_DEVICE_ERRORS   = 0x17, /** \brief ��ȡ�����ѷ����Ĵ��� */
    AM_ZSL42X_LORA_OPCODE_CLEAR_DEVICE_ERRORS = 0x07, /** \brief ���������������  */
} am_zsl42x_lora_opcode_t;

/**< \brief Syncword for Private LoRa networks */
#define AM_ZSL42X_LORA_MAC_PRIVATE_SYNCWORD              0x1424

/**< \brief Syncword for Public LoRa networks */
#define AM_ZSL42X_LORA_MAC_PUBLIC_SYNCWORD               0x3444

/**
 * \brief LoRa ˯��ģʽѡ��   ��������������
 */
typedef enum {
    AM_ZSL42X_LORA_SLEEP_MODE_COLD_START = 0, /**< \brief ����ʱ���������� */
    AM_ZSL42X_LORA_SLEEP_MODE_WARM_START = 1, /**< \brief ����ʱ�������� */
} am_zsl42x_lora_sleep_mode_t;

/**
 * \brief LoRa RTC�Զ�����
 */
typedef enum {
    AM_ZSL42X_LORA_SLEEP_MODE_RTC_WAKEUP_DISABLE = 0,
    AM_ZSL42X_LORA_SLEEP_MODE_RTC_WAKEUP_ENABLE  = 1,
} am_zsl42x_lora_sleep_mode_rtc_wakeup_t;

/**
 * \brief sleepģʽ����
 *
 * \param[in] am_zsl42x_lora_dev_t                   ��lora�豸
 * \param[in] am_zsl42x_lora_sleep_mode_t            ��˯��ģʽѡ��
 * \param[in] am_zsl42x_lora_sleep_mode_rtc_wakeup_t ��RTC�Զ�����ʹ��(��Ҫ�������ڻ��ѹ���)
 *
 * \note ������ֻ����SDBY�·��ͣ���NSS�����غ󣬳��˱��ݵ�������sleepconfigָ���Ŀ飨RC64k����
 *       �����鶼���ر�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setsleep (am_zsl42x_lora_dev_t                  *p_dev,
                             am_zsl42x_lora_sleep_mode_t            mode,
                             am_zsl42x_lora_sleep_mode_rtc_wakeup_t enable);

/**
 * \brief LoRa RTC�Զ�����
 */
typedef enum {
    AM_ZSL42X_LORA_STANDBY_MODE_STDBY_RC   = 0,
    AM_ZSL42X_LORA_STANDBY_MODE_STDBY_XOSC = 1,
} am_zsl42x_lora_standby_mode_t;

/**
 * \brief standbyģʽ����
 *
 * \param[in] am_zsl42x_lora_dev_t          ��lora�豸
 * \param[in] am_zsl42x_lora_standby_mode_t ������ģʽģʽѡ��
 *
 * \note ��ģʽר������ʹ�ø߼��������оƬ���á�
 *       Ĭ������£���ز����λ����������ʱ��оƬ����SDBY_RCģʽ������13MHz��RCʱ�ӡ�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setstandby (am_zsl42x_lora_dev_t  *p_dev,
                               uint8_t                mode);
/**
 * \brief FS����
 *
 * \param[in] am_zsl42x_lora_dev_t   :lora�豸
 *
 * \note ���ڲ���PLLĿ�ġ���STDBY�л���TX��RXģʽ�����Զ�����FS��
 *       ��FSģʽ�£�PLL��Ƶ�ʽ������ó�Setrffrequency�������õ�Ƶ�ʡ�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setfs (am_zsl42x_lora_dev_t *p_dev);

/**
 * \brief TX����
 *
 * \param[in] am_zsl42x_lora_dev_t     :lora�豸
 * \param[in] data                     :��ʱʱ�����ã�24bit���ݣ�
 *
 * \note ��STDBY_RCģʽ��ʼ������������PLL����PA��Ȼ��PA����������Settxparams������������ã�
 *       ���ʼ��������ݡ�
 *       ���ݷ�����ɻ�ʧ�ܣ�TX_DONE����λ��ʱ��־��PA�����������ͣ�PA�رգ��˻ص�STDBY_RCģʽ��
 *
 *       ��ʱʱ������: Time = data * 15.625us (data:���볬ʱʱ�����ò�����Time:ʵ�ʳ�ʱʱ��)
 *       ��data����Ϊ0ʱ���������TX��ʱ���ã�ֻ�д�����ɣ������˻ص�STDBY_RCģʽ��
 *       ��data���ò�Ϊ0ʱ����������TX��ʱ���ã�������ɻ�ʱ�������˻ص�STDBY_RCģʽ��
 *
 *       data��һ��24λ�����ݡ�Time��ʱʱ�����Ϊ262s��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_settx (am_zsl42x_lora_dev_t *p_dev,
                          uint32_t              data);

/**
 * \brief RX����
 *
 * \param[in] am_zsl42x_lora_dev_t     :lora�豸
 * \param[in] data                     :��ʱʱ�����ã�24bit���ݣ�
 *
 * \note ����Ϊ����ģʽ���ȴ�һ���������ݰ��Ľ��ա�
 *
 *       ��ʱʱ������: Time = data * 15.625us (data:���볬ʱʱ�����ò�����Time:ʵ�ʳ�ʱʱ��)
 *
 *       ��data����0x000000ʱ���������RX��ʱ���ã�ֻ�д�����ɣ������˻ص�STDBY_RCģʽ��
 *       ��data����0xffffffʱ����������RX����ģʽ�����յ����ݻ��߳�ʱ�����������Խ�����һ���ݣ�
 *       ���˻�STDBY_RCģʽ��
 *       ��data����������ֵʱ����������RX��ʱ���ã�������ɻ�ʱ�������˻ص�STDBY_RCģʽ��
 *
 *       ��������˳�ʱ���ã��ڼ�⵽ǰ������ͬ����ʱ��FSK�����߼�⵽��ͷ��LoRa��ʱ��ֱ�ӵ���stoptimeron
 *       preamble��ֹͣ��ʱʱ��ļ�ʱ��ֱ�ӽ����������ݡ���������˻�STDBY_RCģʽ�����δ��⵽���ݣ���ȴ�
 *       ��ʱ������
 *
 *       data��һ��24λ�����ݡ�Time��ʱʱ�����Ϊ262s��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setrx (am_zsl42x_lora_dev_t *p_dev,
                          uint32_t              data);

/**
 * \brief LoRa stoptimeronpreambleֹͣ���(���ճ�ʱ)
 */
typedef enum {
    AM_ZSL42X_LORA_STOPTIMER_SYNCWORD_HEADER = 0x00,
    AM_ZSL42X_LORA_STOPTIMER_PREAMBLE        = 0x01,
} am_zsl42x_lora_stoptimeronpreamble_t;

/**
 * \brief ZSL42X LORA LowDataRateOptimize
 */
typedef enum {
    AM_ZSL42X_LORA_LOW_DATA_DATE_OPTIMIZE_OFF = 0X00,
    AM_ZSL42X_LORA_LOW_DATA_DATE_OPTIMIZE_ON  = 0X01,
} am_zsl42x_lora_lowdatarateoptimize_t;

/**
 * \brief stoptimeronpreamble����
 *
 * \param[in] am_zsl42x_lora_dev_t    :lora�豸
 * \param[in] type                    :ֹͣ���ռ�⣨ǰ������ͬ���ֺͰ�ͷ����ֱ�����ݽ������
 *
 * \note ֻ��Խ��ճ�ʱ��Чʱ�ļ�⣬�ɵ��ô˺����ս᱾�μ�⣬ֱ�����ݽ������
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_stoptimeronpreamble (am_zsl42x_lora_dev_t *p_dev,
                                        uint8_t               type);

/**
 * \brief ���ڻ�������
 *
 * \param[in] am_zsl42x_lora_dev_t    :lora�豸
 * \param[in] rx_period               :���������趨ֵ��ʵ��ʱ�� = �趨ֵ * 15.625us��
 * \param[in] sleep_period            :˯�������趨ֵ��ʵ��ʱ�� = �趨ֵ * 15.625us��
 *
 * \note ���豸����STDBY_RCģʽ�£����ʹ�����������豸���ã�оƬ����һ��ѭ������ѭ�������²��趨�壺
 *          1.оƬ����RXģʽ�����������ݰ�һ��ʱ�䣨ʱ����rx_period���� ��
 *          2.��⵽һ�����ݰ���ʼ��LoRa--��ͷ��FSK--ǰ������ͬ���֣�
 *          3.��⵽һ�����ݰ���ʼ��LoRa--��ͷ��FSK--ǰ������ͬ���֣�����ֹͣ��ʱ������2*rx_period +
 *            sleep_period��ʱ�������������ʱ
 *          4.�����rx_period��ʱ����δ��⵽���ݰ���ʼ��LoRa--��ͷ��FSK--ǰ������ͬ���֣��������˯��
 *            ģʽ��˯��ʱ����sleep_period�趨��
 *          5.˯��ʱ��������ظ�ǰ�沽�衣
 *
 *       ��Ҫע����ǣ��������κ�ʱ�̶�����ֹͣ��ѭ�����̡��������������������ѭ����
 *          1.��rx_periodʱ���ڣ���⵽���ݣ�ͨ��RX_DONE��־�����������ж��źţ��������˻ص�STBY_RCģʽ��
 *          2.��rx_periodʱ���ڣ���������setstandby���˯��ģʽ�����������ƣ���
 *
 *       ʱ����㷽ʽ��
 *          sleep = sleep_period * 15.625us
 *          rx    = rx_period * 15.625us
 *       ��rx_period��sleep_period֮������500us��ʱ�������������Լ�ģʽ���л������ʱ�䲻׼ȷ����Ӳ����ء�
 *       ���ʹ�������TCXOʱ��delay�����������ʱҲ����rx_period��sleep_period֮����롣
 *
 *       ���⣬��Ϊ��⵽һ�����ݰ���ʼ��Ľ���ʱ��Ϊ2*rx_period+sleep_period��Ϊ�˷�ֹα���Լ����Ҫ��
 *       ���������
 *           T1(preamble)+T2(header) <= 2*rx_period+sleep_period
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setrxdutycycle (am_zsl42x_lora_dev_t  *p_dev,
                                   uint32_t               rx_period,
                                   uint32_t               sleep_period);

/**
 * \brief setcad�ŵ���Ծ��⣨LoRa���еĲ���ָ�
 *
 * \param[in] am_zsl42x_lora_dev_t : lora�豸
 *
 * \note ����setcadparams�������õĳ��ȣ�����LoRa�źţ�������ɺ󣬷��ص�STDBY_RCģʽ��
 *
 *       ����������ʱ���������irq_done�����������źš�
 *
 *       �����һ����Ч�źű���⵽�������һ��irq_caddetect�źš�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setcad (am_zsl42x_lora_dev_t *p_dev);

/**
 * \brief settxcontinuouswave���а��Ĳ�������
 *
 * \param[in] am_zsl42x_lora_dev_t :lora�豸
 *
 * \note ����һ��ѡ��Ƶ�ʺ�������ʵ���������RX tone�����豸����TX��������ֱ�����������������
 *
 *       ʵ����û���м�ֵ�����������ǿ���Ϊ������Ա��TXģʽ�¼��ͼ���������һ��������
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_settxcontinuouswave (am_zsl42x_lora_dev_t *p_dev);

/**
 * \brief settxinfinitepreamble��������
 *
 * \param[in] am_zsl42x_lora_dev_t : lora�豸
 *
 * \note ��FSKģʽ�£��������޸������0��1�����У�0x55����
 *       ��LoRaģʽ�£�ֻ�ܲ��ϵ���ǰ������
 *
 *       �豸����TX�������ԣ����ܷ����κ����ݣ�ֱ��������������������ġ�
 *
 *       ��������԰����û���Ϊ���׵ؼ�⵽���Ʋ����ع���Ӱ�졣
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_settxinfinitepreamble (am_zsl42x_lora_dev_t *p_dev);

/**
 * \brief LoRa setregulatormode LDO��DC_DCѡ��
 */
typedef enum {
    AM_ZSL42X_LORA_STOPTIMER_LDO   = 0x00, /**< \brief ����������ģʽ */
    AM_ZSL42X_LORA_STOPTIMER_DC_DC = 0x01, /**< \brief ������STBY_XOSC��FS��RX��TXģʽ */
} am_zsl42x_lora_setregulatormode_t;

/**
 * \brief setregulatormode���õ���������ѡ��LDO��DC_DC��
 *
 * \param[in] am_zsl42x_lora_dev_t     :lora�豸
 * \param[in] type                     :����ѡ��
 *
 * \note Ĭ��ʹ��LDO��ʹ��DC_DC�ϵ��¹��ʵ����������ڲ�����regmodeparam�趨
 *
 *       ������Ӳ���йء�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setregulatormode (am_zsl42x_lora_dev_t *p_dev,
                                     uint8_t               type);

/** \brief setcalibratefunction У׼ʹ�ܺ궨�壨����ʹ�û�������У׼��*/
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_RC64K       (1 << 0)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_RC13M       (1 << 1)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_PLL         (1 << 2)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_ADCPULSE    (1 << 3)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_ADCBULK_N   (1 << 4)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_ADCBULK_P   (1 << 5)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_IMAGE       (1 << 6)
#define AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_ALL         (0x7F)

/**
 * \brief setcalibratefunctionУ׼ʹ�ܣ�RC64K/RC13M/PLL/ADC/IMAGE��
 *
 * \param[in] am_zsl42x_lora_dev_t   :lora�豸
 * \param[in] flag  :AM_ZSL42X_LORA_SETCALIBRATE_ENABLE_xx�궨��ʹ�ܣ���ʹ�û������
 *
 * \note ��Դ����ʱ�����RC64K/RC13M/PLL/ADC����У׼����STDBY_RCģʽ�£���ͨ�������һ������ģ��У׼��
 *       ������Ϊ����ʹ�ܣ�����������calibparam���塣
 *
 *       ���У׼����ģ�飬���ܹ���ʱ3.5ms��BUSY�Ż��ٴα�͡�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setcalibratefunction (am_zsl42x_lora_dev_t *p_dev,
                                         uint8_t               flag);

/**
 * \brief LoRa calibrateimage �ض�Ƶ�εľ�ƵУ׼��Χö��
 */
typedef enum {
    AM_ZSL42X_LORA_CALIBRATE_IMAGE_430MHz_440MHz = 0,
    AM_ZSL42X_LORA_CALIBRATE_IMAGE_470MHz_510MHz = 1,
    AM_ZSL42X_LORA_CALIBRATE_IMAGE_779MHz_787MHz = 2,
    AM_ZSL42X_LORA_CALIBRATE_IMAGE_863MHz_870MHz = 3,
    AM_ZSL42X_LORA_CALIBRATE_IMAGE_902MHz_928MHz = 4,
} am_zsl42x_lora_calibrate_image_t;

/**
 * \brief calibrateimage�ض�Ƶ�εľ�ƵУ׼
 *
 * \param[in] am_zsl42x_lora_dev_t             : lora�豸
 * \param[in] am_zsl42x_lora_calibrate_image_t : Ƶ��ö�٣�����Ƶ����Ҫ��ϵоƬ������ѯ��
 *
 * \note �û�����ѡ�������������������е�ISMƵ�Ρ�
 *
 *       ��POR�����豸��˯��ģʽ������ʱ����ƵУ׼��Ϊ��ʼУ׼��һ���֣�����Ĭ��902MHz_928MHz����У׼������
 *       �ڴ˽׶��豸�ڲ���֪���Ƿ�װ��XTAL��TCXO������У׼��ʧ�ܣ�Ӧ���ڵ���setdio3astcxoctrl������
 *       ��һ�������ľ�ƵУ׼��
 *
 *       Ĭ�Ͼ�ƵУ׼��Ƶ��902MHz_928MHz������������Ƶ�Σ�������ѯ���̻�ø���Ƶ�β�����
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_calibrateimage (am_zsl42x_lora_dev_t             *p_dev,
                                   am_zsl42x_lora_calibrate_image_t  type);

/** \brief sx1261�Ƽ�PA���ã�15dBm��14dBm��10dBm��  */
#define AM_ZSL42X_LORA_PACONFIG_SX1261_15dBm_paDutyCycle   0x06   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1261_15dBm_hpMax         0x00   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1261_15dBm_devieSel      0x01   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1261_15dBm_paLut         0x01   /* ����Ϊ1 */

#define AM_ZSL42X_LORA_PACONFIG_SX1261_14dBm_paDutyCycle   0x04   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1261_14dBm_hpMax         0x00
#define AM_ZSL42X_LORA_PACONFIG_SX1261_14dBm_devieSel      0x01
#define AM_ZSL42X_LORA_PACONFIG_SX1261_14dBm_paLut         0x01

#define AM_ZSL42X_LORA_PACONFIG_SX1261_10dBm_paDutyCycle   0x04   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1261_10dBm_hpMax         0x00   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1261_10dBm_devieSel      0x01   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1261_10dBm_paLut         0x01   /* ����Ϊ1 */

/** \brief sx1262�Ƽ�PA���ã�22dBm��20dBm��17dBm��14dBm��  */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_22dBm_paDutyCycle   0x04   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1262_22dBm_hpMax         0x07   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_22dBm_devieSel      0x00   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_22dBm_paLut         0x01   /* ����Ϊ1 */

#define AM_ZSL42X_LORA_PACONFIG_SX1262_20dBm_paDutyCycle   0x03   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1262_20dBm_hpMax         0x05   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_20dBm_devieSel      0x00   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_20dBm_paLut         0x01   /* ����Ϊ1 */

#define AM_ZSL42X_LORA_PACONFIG_SX1262_17dBm_paDutyCycle   0x02   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1262_17dBm_hpMax         0x03   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_17dBm_devieSel      0x00   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_17dBm_paLut         0x01   /* ����Ϊ1 */

#define AM_ZSL42X_LORA_PACONFIG_SX1262_14dBm_paDutyCycle   0x02   /* PASռ�ձȣ���ͨ�ǣ�*/
#define AM_ZSL42X_LORA_PACONFIG_SX1262_14dBm_hpMax         0x02   /* PA��С */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_14dBm_devieSel      0x00   /* 1261/1262ѡ�� */
#define AM_ZSL42X_LORA_PACONFIG_SX1262_14dBm_paLut         0x01   /* ����Ϊ1 */

/**
 * \brief setpaconfig PA����
 *
 * \param[in] am_zsl42x_lora_dev_t      : lora�豸
 * \param[in] paDutyCycle               : PASռ�ձȣ���ͨ��
 * \param[in] hpMax                     : PA��С
 * \param[in] devieSel                  : 1261/1262ѡ��(0:1262   1:1261)
 * \param[in] paLut                     : ����Ϊ1
 *
 * \note  paDutyCycle: PASռ�ձȣ���ͨ�ǣ������������ʡ����ġ�г��������paDutyCycle�仯�����Ӧ��ѡ
 *                     ���������ƥ������Эͬ������
 *        hpMax      : PA��С��ֻ��1262��Ч�����������ʿ���ͨ������hpMax��ֵ�����͡���ֵ�÷�ΧΪ
 *                     0x07--0x00֮�䡣��ֵ����0x07���Ͻ������豸�ϻ����ڼ����¶���ʹ�ý����豸��
 *
 *        �ر�ע�⣺
 *           ����1261���ϳ�Ƶ�ʵ���400MHz��paDutyCycle��Ӧ����0x04
 *                   �ϳ�Ƶ�ʴ���400MHz��paDutyCycle��Ӧ����0x07
 *
 *           ����1262��paDutyCycle��Ӧ����0x04
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setpaconfig (am_zsl42x_lora_dev_t *p_dev,
                                uint8_t               paDutyCycle,
                                uint8_t               hpMax,
                                uint8_t               devieSel,
                                uint8_t               paLut);

/**
 * \brief LoRa setrxtxfallbackmode ������ɡ�������ɣ��˻ص���ģʽö��
 */
typedef enum {
    AM_ZSL42X_LORA_RXTXFALLBACKMODE_FS         = 0x40,
    AM_ZSL42X_LORA_RXTXFALLBACKMODE_STDBY_XOSC = 0x30,
    AM_ZSL42X_LORA_RXTXFALLBACKMODE_STDBY_RC   = 0x20,
} am_zsl42x_lora_rxtxfallbackmode_t;

/**
 * \brief setrxtxfallbackmode������ɡ�������ɣ��˻ص���ģʽ����
 *
 * \param[in] am_zsl42x_lora_dev_t              : lora�豸
 * \param[in] am_zsl42x_lora_rxtxfallbackmode_t : ������ɡ�������ɣ��˻ص���ģʽ
 *
 * \note Ĭ��ΪSTDBY_RC
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setrxtxfallbackmode (am_zsl42x_lora_dev_t *p_dev,
                                        uint8_t               type);

/**
 * \brief LoRa �Ĵ�����ַö��
 */
typedef enum {

    /** \brief DIO��ؼĴ��� */
    AM_ZSL42X_LORA_REGADDR_DIOX_OUT_ENABLE     = 0x0580,   /**< \brief DIOx���ʹ�� */
    AM_ZSL42X_LORA_REGADDR_DIOX_IN_ENABLE      = 0x0583,   /**< \brief DIOx����ʹ�� */
    AM_ZSL42X_LORA_REGADDR_DIOX_PU_CTRL        = 0x0584,   /**< \brief DIOx�������� */
    AM_ZSL42X_LORA_REGADDR_DIOX_PD_CTRL        = 0x0585,   /**< \brief DIOx�������� */

    /** \brief FSKģʽ����ؼĴ��� */
    AM_ZSL42X_LORA_REGADDR_FSK_WHITEN_INIT_MSB = 0x06B8, /**< \brief CRC�׻���ʼֵ MSB */
    AM_ZSL42X_LORA_REGADDR_FSK_WHITEN_INIT_LSB = 0x06B9, /**< \brief CRC�׻���ʼֵ LSB */
    AM_ZSL42X_LORA_REGADDR_FSK_CRC_INIT_MSB    = 0x06BC, /**< \brief CRC��ʼֵ MSB */
    AM_ZSL42X_LORA_REGADDR_FSK_CRC_INIT_LSB    = 0x06BD, /**< \brief CRC��ʼֵ LSB */
    AM_ZSL42X_LORA_REGADDR_FSK_CRC_POLY_MSB    = 0x06BE, /**< \brief ����ʽֵMSB */
    AM_ZSL42X_LORA_REGADDR_FSK_CRC_POLY_LSB    = 0x06BF, /**< \brief ����ʽֵLSB */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD0       = 0x06C0, /**< \brief ͬ����0 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD1       = 0x06C1, /**< \brief ͬ����1 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD2       = 0x06C2, /**< \brief ͬ����2 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD3       = 0x06C3, /**< \brief ͬ����3 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD4       = 0x06C4, /**< \brief ͬ����4 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD5       = 0x06C5, /**< \brief ͬ����5 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD6       = 0x06C6, /**< \brief ͬ����6 */
    AM_ZSL42X_LORA_REGADDR_FSK_SYNCWORD7       = 0x06C7, /**< \brief ͬ����7 */
    AM_ZSL42X_LORA_REGADDR_FSK_NODE_ADDR       = 0x06CD, /**< \brief �ڵ��ַ */
    AM_ZSL42X_LORA_REGADDR_FSK_BROADCAST_ADDR  = 0x06CE, /**< \brief �㲥��ַ */

    /** \brief loraģʽ����ؼĴ��� */
    AM_ZSL42X_LORA_REGADDR_LORA_SYNCWORD_MSB   = 0x0740,   /**< \brief ͬ����MSB */
    AM_ZSL42X_LORA_REGADDR_LORA_SYNCWORD_LSB   = 0x0741,   /**< \brief ͬ����LSB */

    /** \brief �����Ĵ��� */
    AM_ZSL42X_LORA_REGADDR_RANDOMNUMBERGEN0    = 0x0819,   /**< \brief �����0 */
    AM_ZSL42X_LORA_REGADDR_RANDOMNUMBERGEN1    = 0x081A,   /**< \brief �����1 */
    AM_ZSL42X_LORA_REGADDR_RANDOMNUMBERGEN2    = 0x081B,   /**< \brief �����2 */
    AM_ZSL42X_LORA_REGADDR_RANDOMNUMBERGEN3    = 0x081C,   /**< \brief �����3 */
    AM_ZSL42X_LORA_REGADDR_RX_GAIN             = 0x08AC,   /**< \brief ��������   */
    AM_ZSL42X_LORA_REGADDR_OCP_CONFIG          = 0x08E7,   /**< \brief ��������������  */
    AM_ZSL42X_LORA_REGADDR_XTA_TRIM            = 0x0911,   /**< \brief XTA���ŵ��� */
    AM_ZSL42X_LORA_REGADDR_XTB_TRIM            = 0x0912,   /**< \brief XTB���ŵ��� */
    AM_ZSL42X_LORA_REGADDR_RTC_CTRL            = 0x0902,   /**< \brief RTC���� */
    AM_ZSL42X_LORA_REGADDR_IQ_POLARITY_SETUP   = 0x0736,   /**< \brief IQ�ź����� */

    AM_ZSL42X_LORA_REGADDR_TX_MODULATION    = 0x0889, /**< \brief ����500kHz������������ */
    AM_ZSL42X_LORA_REGADDR_TX_CLAMPCONFIG   = 0x08D8, /**< \brief ���������ƥ��Ĵ��� */
    AM_ZSL42X_LORA_REGADDR_DIO3_OUT_VOLTAGE = 0x0920, /**< \brief DIO3�����ѹ����*/
    AM_ZSL42X_LORA_REGADDR_EVENT_MASK       = 0x0944, /**< \brief �¼���� */

    /* �ֲ�δδ�����ļĴ��� */
    AM_ZSL42X_LORA_REGADDR_PACKETPARAMS  = 0x0704, /**< \brief �������ݰ����õļĴ�����ַ */
    AM_ZSL42X_LORA_REGADDR_PAYLOADLENGTH = 0x0702, /**< \brief ������Ч���س��ȵļĴ�����ַ  */
} am_zsl42x_lora_regaddr_t;

/**
 * \brief write register д�Ĵ���
 *
 * \param[in] am_zsl42x_lora_dev_t        : lora�豸
 * \param[in] am_zsl42x_lora_regaddr_t    : �Ĵ�����ַ
 * \param[in] data                        : ��д��Ĵ�������
 * \param[in] len                         : ��д�����ݳ���
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_write_register (am_zsl42x_lora_dev_t     *p_dev,
                                   am_zsl42x_lora_regaddr_t  reg_addr,
                                   uint8_t                  *p_data,
                                   uint32_t                  len);

/**
 * \brief read register ���Ĵ���
 *
 * \param[in] am_zsl42x_lora_dev_t        : lora�豸
 * \param[in] am_zsl42x_lora_regaddr_t    : �Ĵ�����ַ
 * \param[in] data                        : �������ݻ����ַָ��
 * \param[in] len                         : �������ݳ���
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_read_register (am_zsl42x_lora_dev_t      *p_dev,
                                  am_zsl42x_lora_regaddr_t   reg_addr,
                                  uint8_t                   *p_data,
                                  uint32_t                   len);

/**
 * \brief write buffer дFIFO
 *
 * \param[in] am_zsl42x_lora_dev_t        : lora�豸
 * \param[in] offset                      : ƫ�Ƶ�ַ��0����255��
 * \param[in] data                        : ��д��Ĵ�������
 * \param[in] len                         : ��д�����ݳ��ȣ�256����1��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_write_buffer (am_zsl42x_lora_dev_t  *p_dev,
                                 uint8_t                offset,
                                 uint8_t               *p_data,
                                 uint32_t               len);

/**
 * \brief write register ��FIFO
 *
 * \param[in] am_zsl42x_lora_dev_t        : lora�豸
 * \param[in] offset                      : ƫ�Ƶ�ַ��0����255��
 * \param[in] len                         : �������ݳ���(256����1)
 * \param[in] data                        : �������ݻ����ַָ��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_read_buffer (am_zsl42x_lora_dev_t  *p_dev,
                                uint8_t                offset,
                                uint32_t               len,
                                uint8_t               *p_data);

/** \brief setdioirqparams dio�ж�ʹ�ܺ궨�壨����ʹ�û�������ʹ�ܣ�*/
#define AM_ZSL42X_LORA_IRQ_MASK_TX_DONE        (1 << 0) /**< \brief ������� */
#define AM_ZSL42X_LORA_IRQ_MASK_RX_DONE        (1 << 1) /**< \brief ������� */
#define AM_ZSL42X_LORA_IRQ_MASK_PREAMBLE_DET   (1 << 2) /**< \brief ��⵽ǰ���� */
#define AM_ZSL42X_LORA_IRQ_MASK_SYNCWORD_VALID (1 << 3) /**< \brief ͬ������Ч(FSK) */
#define AM_ZSL42X_LORA_IRQ_MASK_HEADER_VALID   (1 << 4) /**< \brief ��ͷ��Ч(LoRa) */
#define AM_ZSL42X_LORA_IRQ_MASK_HEADER_ERR     (1 << 5) /**< \brief ��ͷ����(LoRa) */
#define AM_ZSL42X_LORA_IRQ_MASK_CRC_ERR        (1 << 6) /**< \brief CRCУ����� */
#define AM_ZSL42X_LORA_IRQ_MASK_CAD_DONE       (1 << 7) /**< \brief CAD���(LoRa) */
#define AM_ZSL42X_LORA_IRQ_MASK_CAD_DET        (1 << 8) /**< \brief CAD��⵽�ź�(LoRa)*/
#define AM_ZSL42X_LORA_IRQ_MASK_TIMEOUT        (1 << 9) /**< \brief ��ʱ */
#define AM_ZSL42X_LORA_IRQ_MASK_ALL_DISABLE    (0x000)  /**< \brief �ر����� */
#define AM_ZSL42X_LORA_IRQ_MASK_ALL_ENABLE     (0xFFFF) /**< \brief �������� */

/**
 * \brief setdioirqparams ����DIO�жϣ�����ʹ�û�������ʹ�ܣ�
 *
 * \param[in] am_zsl42x_lora_dev_t   : lora�豸
 * \param[in] irq_mask               : �ж�ʹ��
 * \param[in] dio1_mask              : DIO1�ж�ѡ��irq_mask��dio1_mask��Ӧλͬʱ��1�����ж���Ч��
 * \param[in] dio2_mask              : DIO2�ж�ѡ��
 * \param[in] dio3_mask              : DIO3�ж�ѡ��
 *
 * \note  dio2��dio3��ΪRF SW��TCXOʱ����ʹ������dio2_mask��dio3_maskҲ�������ж��ź������
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setdioirqparams (am_zsl42x_lora_dev_t *p_dev,
                                    uint16_t              irq_mask,
                                    uint16_t              dio1_mask,
                                    uint16_t              dio2_mask,
                                    uint16_t              dio3_mask);

/**
 * \brief getirqstatus ��ȡ�ж�״̬��־
 *
 * \param[in] am_zsl42x_lora_dev_t        : lora�豸
 * \param[in] p_status                    : �ж�״̬��־��OUT��
 *
 * \note  status & AM_ZSL42X_LORA_SETDIO_IRQ_MASK_xx �ɵó�ĳһ�жϱ�־�Ƿ���Ч
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getirqstatus (am_zsl42x_lora_dev_t *p_dev,
                                 uint16_t             *p_status);

/**
 * \brief clearirqstatus ����ж�״̬��־������ʹ�û�������ʹ�ܣ�
 *
 * \param[in] am_zsl42x_lora_dev_t    : lora�豸
 * \param[in] clear_mask              : ����ж�״̬��1�������0�����֣�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_clearirqstatus (am_zsl42x_lora_dev_t *p_dev,
                                   uint16_t              clear_mask);

/**
 * \brief setdio2rfswitch DIO2��ΪRF���ƿ���
 *
 * \param[in] am_lora_p_dev_t  : lora�豸
 * \param[in] enable           : AM_TRUE  ��RF���ƿ���
 *                               AM_FALSE ������IRQ��DIO
 *
 * \note DIO2��ΪRF���ƿ���ʱ����Ҫע��DIO2�������ƽ��ϵ��
 *           ��SLEEP��STDBY_RC��STDBY_XOSC��FS��RXģʽ�£�DIO2 = 0��
 *           ��TXģʽ�£�DIO2 = 1��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setdio2rfswitch (am_zsl42x_lora_dev_t *p_dev,
                                    uint8_t               enable);

/**
 * \brief LoRa setdio3tcxoctrl DIO3��Ϊ�ⲿTCXO���õ�ѹ����ö��
 */
typedef enum {
    AM_ZSL42X_LORA_DIO3TCXOCTRL_1600MV = 0x00,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_1700MV = 0x01,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_1800MV = 0x02,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_2200MV = 0x03,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_2400MV = 0x04,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_2700MV = 0x05,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_3000MV = 0x06,
    AM_ZSL42X_LORA_DIO3TCXOCTRL_3300MV = 0x07,
} am_zsl42x_lora_dio3tcxoctrl_t;

/**
 * \brief setdio3tcxoctrl DIO3��Ϊ�ⲿTCXO���õ�ѹ����
 *
 * \param[in] am_lora_p_dev_t    : lora�豸
 * \param[in] voltage            : ��ѹѡ��
 * \param[in] data               : 24bit����ʱʱ���趨ֵ����ʱʱ�� = �趨ֵ * 15.625us��
 *
 * \note ʹ�ô�����ʱ���豸ͨ��DIO3����TCXO����Ҫʱ������STDBY_XOSC��FS��TX��RX�����ڲ�״̬������DIO3
 *       Ԥ��ĵ�ѹֵ�����ڲ���ʱ�ӿ������ȴ�32MHz���֣�Ȼ�����ͷ��ڲ�״̬����32MHz���ֺ��ȶ�ʱ�����ͨ��data
 *       ���á������ʱ����ʱ��δ����32MHz��XOSC_START_ERR���󽫱�����ڴ���������С����豸��POR��������
 *       �������´�˯��ģʽ���ѣ���ʹ����TCXO��XOSC_START_ERR��־������Ч���û�Ӧ��ʹ��cleardeviceer
 *       rorsָ������������־��
 *
 *       voltage�����óɵ��ڵ�ѹ��ѹ200mV����ʹ���õ�ѹ���ڵ�Դ��ѹ��Ҳ�ᱻ������ Vdd > Vtcxo + 200mv
 *
 *       ��ʱʱ�� = �趨ֵ * 15.625us
 *
 *       �����TCXO������������Ҫ��Ƶ��׼���ã����һ�������ʼ����ʱ�����⣬��������Ҫ��Ƶ�ʿ�������ʱ�������ڲ�
 *       ��ֹͣ����ʱ�ӣ����ߵ����������
 *
 *       �ر�ע�⣺
 *          ��STDBY_RCģʽ�л���RX��TXģʽʱ����Ҫ�����ӳ�ʱ�����⡣
 *          Ϊ��������ģʽ�л���ʱ�䡣�û���������STDBY_RCģʽ�����豸����TCXO���ȴ���ʱ��
 *          ���л���RX��TXģʽ��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setdio3tcxoctrl (am_zsl42x_lora_dev_t          *p_dev,
                                    am_zsl42x_lora_dio3tcxoctrl_t  voltage,
                                    uint32_t                       data);

/**
 * \brief setrffrequency ����RFƵ��
 *
 * \param[in] am_lora_p_dev_t  : lora�豸
 * \param[in] rffreq           : RFƵ�ʣ�Hz��
 * \param[in] fxtal            : ����Ƶ�ʣ�Hz��
 *
 * \note ������FS��TX��RX�ľ�ƬƵ�ʡ�
 *       ��RXģʽ�£��Զ���������Ƶ�ʵ�ƫ����
 *
 *       ����ʽ     RF��Ƶ�ʣ� = (�趨ֵ * Fxtal) / 2^25
 *
 *             �趨ֵ =  RF��Ƶ�ʣ�* 2^25 / Fxtal
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setrffrequency (am_zsl42x_lora_dev_t *p_dev,
                                   uint32_t              rffreq,
                                   uint32_t              fxtal);

/**
 * \brief setpackettype ����֡���ͣ�FKS��LoRa��
 *
 * \param[in] am_lora_p_dev_t    : lora�豸
 * \param[in] type               : 0��FKS      1�� LoRa
 *
 * \note ǰһģʽ�����ò�������������STDBY_RCģʽ���л�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setpackettype (am_zsl42x_lora_dev_t *p_dev,
                                  uint8_t               type);

/**
 * \brief setpackettype ��ȡ֡���ͣ�FKS��LoRa��
 *
 * \param[in] am_lora_p_dev_t    : lora�豸
 * \param[in] type               : 0��FKS  1�� LoRa
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getpackettype (am_zsl42x_lora_dev_t *p_dev,
                                  uint8_t              *p_type);

/**
 * \brief LoRa settxparams TXб��ʱ��(us)
 */
typedef enum {
    AM_ZSL42X_LORA_RAMPTIME_10US   = 0x00,
    AM_ZSL42X_LORA_RAMPTIME_20US   = 0x01,
    AM_ZSL42X_LORA_RAMPTIME_40US   = 0x02,
    AM_ZSL42X_LORA_RAMPTIME_80US   = 0x03,
    AM_ZSL42X_LORA_RAMPTIME_200US  = 0x04,
    AM_ZSL42X_LORA_RAMPTIME_800US  = 0x05,
    AM_ZSL42X_LORA_RAMPTIME_1700US = 0x06,
    AM_ZSL42X_LORA_RAMPTIME_3400US = 0x07,
} am_zsl42x_lora_ramptime_t;

/**
 * \brief settxpower ����TX����
 *
 * \param[in] am_zsl42x_lora_dev_t    : lora�豸
 * \param[in] power                   : �������
 * \param[in] ramptime                : TXб��ʱ��
 *
 * \note �͹���PAʱ��power��ΧΪ   -17  �������� +14dBm  �� ����1dBm
 *       �߹���PAʱ��power��ΧΪ   -9   �������� +22dBm  �� ����1dBm
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_settxparam (am_zsl42x_lora_dev_t     *p_dev,
                               int8_t                    power,
                               am_zsl42x_lora_ramptime_t ramptime );

/**
 * \brief LoRa setmodulationparams_fsk �˲�ѡ��ö��
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_FILTER_NO       = 0x00,   /**< \brief ���˲� */
    AM_ZSL42X_LORA_FSK_FILTER_GS_BT_03 = 0x08,   /**< \brief ��˹��������˲��� BT=0.3*/
    AM_ZSL42X_LORA_FSK_FILTER_GS_BT_05 = 0x09,   /**< \brief ��˹��������˲��� BT=0.5*/
    AM_ZSL42X_LORA_FSK_FILTER_GS_BT_07 = 0x0A,   /**< \brief ��˹��������˲��� BT=0.7*/
    AM_ZSL42X_LORA_FSK_FILTER_GS_BT_10 = 0x0B,   /**< \brief ��˹��������˲��� BT=1.0*/
} am_zsl42x_lora_fsk_filter_t;

/**
 * \brief LoRa setmodulationparams_fsk ����ö��
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_RX_BW_4800   = 0x1F,   /**< \brief ���մ���4.8kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_5800   = 0x17,   /**< \brief ���մ���5.8kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_7300   = 0x0F,   /**< \brief ���մ���7.3Hz */
    AM_ZSL42X_LORA_FSK_RX_BW_9700   = 0x1E,   /**< \brief ���մ���9.7kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_11700  = 0x16,   /**< \brief ���մ���11.7kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_14600  = 0x0E,   /**< \brief ���մ���14.6kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_19500  = 0x1D,   /**< \brief ���մ���19.5kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_23400  = 0x15,   /**< \brief ���մ���23.4kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_29300  = 0x0D,   /**< \brief ���մ���29.3kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_39000  = 0x1C,   /**< \brief ���մ���39.0kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_46900  = 0x14,   /**< \brief ���մ���46.9kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_58600  = 0x0C,   /**< \brief ���մ���58.6kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_78200  = 0x1B,   /**< \brief ���մ���78.2kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_93800  = 0x13,   /**< \brief ���մ���93.8kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_117300 = 0x0B,   /**< \brief ���մ���117.3kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_156200 = 0x1A,   /**< \brief ���մ���156.2kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_187200 = 0x12,   /**< \brief ���մ���187.2kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_234300 = 0x0A,   /**< \brief ���մ���234.3kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_312000 = 0x19,   /**< \brief ���մ���312.0kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_373600 = 0x11,   /**< \brief ���մ���373.6kHz */
    AM_ZSL42X_LORA_FSK_RX_BW_467000 = 0x09,   /**< \brief ���մ���467.0kHz */
} am_zsl42x_lora_fsk_bandwidth_t;

/**
 * \brief setmodulationparams_fsk ����FSK���Ʋ���
 *
 * \param[in] p_dev          : lora�豸
 * \param[in] bitrate        : Ŀ������ʣ�600bps--300kbps��
 * \param[in] filter_type    : �˲�ѡ��
 * \param[in] bandwidth      : ����ѡ��
 * \param[in] freq_deviation : Ŀ��ƫ��Ƶ�ʣ�Hz��
 * \param[in] fxtal          : ����Ƶ�ʣ�Hz��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setmodulationparams_fsk (
                                am_zsl42x_lora_dev_t        *p_dev,
                                uint32_t                     bitrate,
                                am_zsl42x_lora_fsk_filter_t  filter_type,
                                uint8_t                      bandwidth,
                                uint32_t                     freq_deviation,
                                uint32_t                     fxtal);

/**
 * \brief LoRa setmodulationparams_zsl42x_lora ��Ƶ����ö��
 */
typedef enum {
    AM_ZSL42X_LORA_SF5  = 0x05,
    AM_ZSL42X_LORA_SF6  = 0x06,
    AM_ZSL42X_LORA_SF7  = 0x07,
    AM_ZSL42X_LORA_SF8  = 0x08,
    AM_ZSL42X_LORA_SF9  = 0x09,
    AM_ZSL42X_LORA_SF10 = 0x0A,
    AM_ZSL42X_LORA_SF11 = 0x0B,
    AM_ZSL42X_LORA_SF12 = 0x0C,
} am_zsl42x_lora_sf_t;

/**
 * \brief LoRa setmodulationparams_zsl42x_lora ����ö��
 */
typedef enum {
    AM_ZSL42X_LORA_BW_125000 = 0x04,  /**< \brief 125.0kHz */
    AM_ZSL42X_LORA_BW_250000 = 0x05,  /**< \brief 250.0kHz */
    AM_ZSL42X_LORA_BW_500000 = 0x06,  /**< \brief 500.0kHz */
} am_zsl42x_lora_bw_t;

/**
 * \brief LoRa setmodulationparams_zsl42x_lora ������ö��
 */
typedef enum {
    AM_ZSL42X_LORA_CR_4_5  = 0x01,  /**< \brief 4/5  1.25 */
    AM_ZSL42X_LORA_CR_4_6  = 0x02,  /**< \brief 4/6  1.5  */
    AM_ZSL42X_LORA_CR_4_7  = 0x03,  /**< \brief 4/7  1.75 */
    AM_ZSL42X_LORA_CR_4_8  = 0x04,  /**< \brief 4/8  2.0  */
} am_zsl42x_lora_cr_t;

/**
 * \brief setmodulationparams_lora ����LoRa���Ʋ���
 *
 * \param[in] p_dev              : lora�豸
 * \param[in] sf_type            : ��Ƶ����
 * \param[in] bw_type            : ����
 * \param[in] cr_type            : ������
 * \param[in] lowdatarate_enable : �����������Ż�ʹ�ܣ�AM_TRUE:ʹ��, AM_FALSE:���ܣ�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setmodulationparams_lora (
                               am_zsl42x_lora_dev_t   *p_dev,
                               am_zsl42x_lora_sf_t     sf_type,
                               am_zsl42x_lora_bw_t     bw_type,
                               am_zsl42x_lora_cr_t     cr_type,
                               am_bool_t               lowdatarate_enable);

/**
 * \brief LoRa setpacketparams_fsk ǰ�������������
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_PREAMBLE_DETECTOR_OFF     = 0x00, /**< \brief  �ر� */
    AM_ZSL42X_LORA_FSK_PREAMBLE_DETECTOR_BITS_8  = 0x04, /**< \brief 8 bits */
    AM_ZSL42X_LORA_FSK_PREAMBLE_DETECTOR_BITS_16 = 0x05, /**< \brief 16 bits */
    AM_ZSL42X_LORA_FSK_PREAMBLE_DETECTOR_BITS_24 = 0x06, /**< \brief 24 bits */
    AM_ZSL42X_LORA_FSK_PREAMBLE_DETECTOR_BITS_32 = 0x07, /**< \brief 32 bits */
} am_zsl42x_lora_fsk_detector_length_t;

/**
 * \brief LoRa setpacketparams_fsk ǰ������������ȱ�
 */
typedef struct {
    uint32_t                             data;
    am_zsl42x_lora_fsk_detector_length_t detector_length;
} zsl42x_lora_fsk_detector_length_find_table_t;

/**
 * \brief LoRa setpacketparams_fsk ��ַ���˹���ѡ��
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_ADDR_FILTER_DISABLE        = 0x00, /**< \brief �ر� */
    AM_ZSL42X_LORA_FSK_ADDR_FILTER_NODE           = 0x01, /**< \brief ����--�ڵ��ַ  */
    AM_ZSL42X_LORA_FSK_ADDR_FILTER_NODE_BROADCAST = 0x02, /**< \brief ����--�ڵ㡢�㲥��ַ */
} am_zsl42x_lora_fsk_addr_filter_t;

/**
 * \brief LoRa setpacketparams_fsk ���ݰ������Ƿ�ɱ䣬�Ƿ񽫰�����Ϣ���ص����ṹ��
 */
typedef enum {

    /** \brief ��Ч���ش�С�̶���˫����֪ */
    AM_ZSL42X_LORA_FSK_PACKET_FIXED_LENGTH     = 0x00,

    /** \brief ��Ч���ش�С���̶���˫��δ֪����Ч���ش�С��Ϣ���ص���Ч���صĵ�һ�ֽ� */
    AM_ZSL42X_LORA_FSK_PACKET_VARIABLE_LENGTH  = 0x01,
} am_zsl42x_lora_fsk_packetsize_info_t;

/**
 * \brief LoRa setpacketparams_fsk CRC����ѡ��
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_CRC_OFF          = 0x01, /**< \brief CRC���ܹر� */
    AM_ZSL42X_LORA_FSK_CRC_1_BYTE       = 0x00, /**< \brief 1�ֽڵ�CRC���� */
    AM_ZSL42X_LORA_FSK_CRC_2_BYTE       = 0x02, /**< \brief 2�ֽڵ�CRC���� */
    AM_ZSL42X_LORA_FSK_CRC_1_BYTE_INV   = 0x04, /**< \brief 1�ֽڵ�CRC���㲢��ת���� */
    AM_ZSL42X_LORA_FSK_CRC_2_BYTE_INV   = 0x06, /**< \brief 2�ֽڵ�CRC���㲢��ת���� */
    AM_ZSL42X_LORA_FSK_CRC_2_BYTES_IBM  = 0xF1,
    AM_ZSL42X_LORA_FSK_CRC_2_BYTES_CCIT = 0xF2,
} am_zsl42x_lora_fsk_crc_type_t;

/**
 * \brief setpacketparams_fsk ����FSK���ݰ���ز���
 *
 * \param[in] p_dev           : lora�豸
 * \param[in] preamble_length : ǰ�������ȣ�0-65535��
 * \param[in] detector_length : ǰ�������������
 * \param[in] syncword_number : ͬ���ָ���
 * \param[in] addr_filter     : ��ַ����ѡ��
 * \param[in] sizeinfo_add    : ���ݰ�������Ϣ���Ƿ���֪���Ƿ���Ч���ش�С��Ϣ��ӵ���Ч���صĵ�һ�ֽڣ�
 * \param[in] payloadlength   : ��Ч���ش�С��0-255��
 * \param[in] crc_type        : CRC����ѡ��
 * \param[in] whiteng_enable  : whiteng����ʹ�ܣ�AM_TRUE��ʹ��       AM_FALSE�����ܣ�
 *
 * \note preamble_length---��ʾ���ߵ緢�����Ե��ֽ�����ÿ���ֽڱ���0x55��
 *       detector_length---������ɹ����յ����ó��ȵ�ǰ����bit���Żἤ�����������
 *       syncword_number---0-8��ͬ���֡����⣬��Ҫͬ����д���ƶ��Ĵ����С�
 *       addr_filter    ---��Ҫ8bit��ַд���ƶ��Ĵ������ڵ㡢�㲥���С�
 *       sizeinfo_add   ---˫����֪����Ч���صĴ�С���������Ч���ش�С��Ϣ����Ч���صĵ�һ�ֽڡ�
 *                         ��Ч���صĴ�С���̶����������Ч���ش�С��Ϣ����Ч���صĵ�һ�ֽڡ�
 *       payloadlength  ---��Ч���ش�С��0-255��
 *       crc_type       ---����ʹ��Ĭ�ϵ�CRC����ֵ��Ҳ����ͨ��д�Ĵ����ֶ����á�
 *       whiteng_enable ---whiteng����ʹ�ܣ�ͨ��д�Ĵ����ֶ����û�ʹ��Ĭ�����á�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setpacketparams_fsk (
                    am_zsl42x_lora_dev_t                  *p_dev,
                    uint16_t                               preamble_length,
                    am_zsl42x_lora_fsk_detector_length_t   detector_length,
                    uint8_t                                syncword_number,
                    am_zsl42x_lora_fsk_addr_filter_t       addr_filter,
                    am_zsl42x_lora_fsk_packetsize_info_t   sizeinfo_add,
                    uint8_t                                payloadlength,
                    am_zsl42x_lora_fsk_crc_type_t          crc_type,
                    am_bool_t                              whiteng_enable);

/**
 * \brief LoRa setpacketparams_lora ��ͷ����ö��
 */
typedef enum {
    AM_ZSL42X_LORA_PACKET_VARIABLE_LENGTH = 0x00,  /**< \brief �ɱ������ */
    AM_ZSL42X_LORA_PACKET_FIXED_LENGTH    = 0x01,  /**< \brief �̶������� */
} am_zsl42x_lora_header_type_t;

/**
 * \brief LoRa setpacketparams_lora CRCѡ��
 */
typedef enum {
    AM_ZSL42X_LORA_CRC_OFF = 0x00,
    AM_ZSL42X_LORA_CRC_ON  = 0x01,
} am_zsl42x_lora_crc_type_t;

/**
 * \brief LoRa setpacketparams_lora CRCѡ��
 */
typedef enum {
    AM_ZSL42X_LORA_IQ_STANDARD = 0x00,    /**< \brief ��׼IQ���� */
    AM_ZSL42X_LORA_IQ_INVERTED = 0x01,    /**< \brief ��תIQ���� */
} am_zsl42x_lora_iq_type_t;

/**
 * \brief setpacketparams_fsk ����FSK���ݰ���ز���
 *
 * \param[in] p_dev           : lora�豸
 * \param[in] preamble_length : ǰ�������ȣ�0-65535��
 * \param[in] header_type     : ͷ����
 * \param[in] payloadlength   : ��Ч���ش�С��0-255��
 * \param[in] crc_type        : CRCʹ��
 * \param[in] iq_type         : IQ����
 *
 * \note preamble_length---��ʾ���ߵ緢�����Ե��ֽ�����
 *       detector_length---������ɹ����յ����ó��ȵ�ǰ����bit���Żἤ�����������
 *       header_type    ---��ʽͷ���ɱ䳤�Ȱ������������Ч���ش�С���������ʡ�CRC��ʽ��ӵ���ͷ�С�
 *       payloadlength  ---��Ч���ش�С��0-255��
 *       crc_type       ---������رա�
 *       iq_type        ---��׼IQ�ź����á���תIQ�ź����á�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setpacketparams_lora (
                           am_zsl42x_lora_dev_t        *p_dev,
                           uint16_t                     preamble_length,
                           am_zsl42x_lora_header_type_t header_type,
                           uint8_t                      payloadlength,
                           am_zsl42x_lora_crc_type_t    crc_type,
                           am_zsl42x_lora_iq_type_t     iq_type);

/**
 * \brief LoRa setcadparams_lora ��������
 */
typedef enum {
    AM_ZSL42X_LORA_CAD_SYMBOLNUM_1  = 0x00,
    AM_ZSL42X_LORA_CAD_SYMBOLNUM_2  = 0x01,
    AM_ZSL42X_LORA_CAD_SYMBOLNUM_4  = 0x02,
    AM_ZSL42X_LORA_CAD_SYMBOLNUM_8  = 0x03,
    AM_ZSL42X_LORA_CAD_SYMBOLNUM_16 = 0x04,
} am_zsl42x_lora_cad_symbolnum_t;

/**
 * \brief LoRa setcadparams_lora CAD��⵽�ʱ�˻ص�ģʽ
 */
typedef enum {

    /** \brief CAD��ɣ�ֱ���˻ص�STDBY_RCģʽ */
    AM_ZSL42X_LORA_CAD_EXTIMODE_ONLY = 0x00,

    /** \brief CAD��⵽���ͣ����RXģʽ��ֱ�����ݽ�����ɻ�ʱ�����˻ص�STDBY_RCģʽ */
    AM_ZSL42X_LORA_CAD_EXTIMODE_RX   = 0x01,
} am_zsl42x_lora_cad_extimode_t;

typedef struct {
    uint8_t  sf;
    uint8_t  detmin;
    uint8_t  detpeak;
    am_zsl42x_lora_cad_symbolnum_t  symbolnum;
} zsl42x_lora_cad_set_t;

/**
 * \brief setcadparams_lora ����CAD��ز���
 *
 * \param[in] p_dev     : lora�豸
 * \param[in] symbolnum : ��������
 * \param[in] detpeak   :
 * \param[in] detmin    :
 * \param[in] extimode  : CAD��⵽�ʱ�˻ص�ģʽѡ��
 * \param[in] data      : ��ʱʱ���趨ֵ ��ʵ�ʳ�ʱʱ��  = �趨ֵ  *15.625us��
 *
 * \note detpeak��detmin---������LoRa���ƽ�����ڳ��Թ�����ʵ�ʵ�LoRa���Է��ŵ������ȡ�����������ȡ����
 *                        ��Ƶ���Ӻʹ���Ҳȡ����������֤�򲻼��ķ�����������ѡ��ֵ��Ҫ������ϸ�Ĳ��ԣ�
 *                        ��ȷ���������ȽϺõ�������������ü�⣬�����ƴ������������Ӧ�ñʼ�AN1200.
 *                        48�ṩ����Щ�������õ�ָ��
 *
 *       data          ---��extimodeѡ��AM_ZSL42X_LORA_LORA_CAD_EXTIMODE_RXʱ��CAD������
 *                        ����뵥�ν���ģʽ��data��Ϊ���ν���ģʽ��ͣ���ĵĳ�ʱʱ�䡣
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setcadparams_lora (
                                am_zsl42x_lora_dev_t          *p_dev,
                                am_zsl42x_lora_cad_symbolnum_t symbolnum,
                                uint8_t                        detpeak,
                                uint8_t                        detmin,
                                am_zsl42x_lora_cad_extimode_t  extimode,
                                uint32_t                       data);

/**
 * \brief setbufferbaseaddress ���ý��ա����ͻ������Ļ���ַ
 *
 * \param[in] p_dev          : lora�豸
 * \param[in] tx_baseaddress : ���ݷ��͵�ַ
 * \param[in] rx_baseaddress : ���ݽ��յ�ַ
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setbufferbaseaddress (am_zsl42x_lora_dev_t *p_dev,
                                         uint8_t               tx_baseaddress,
                                         uint8_t               rx_baseaddress);

/**
 * \brief setsymbolnumtimeout_lora ���õ��ƽ����������֤�ɹ����յķ�������
 *
 * \param[in] p_dev     : lora�豸
 * \param[in] symbolnum : ��������
 *
 * \note ��loraģʽ�£�����RXʱ��һ����⵽LoRa���ţ����ƽ������������������ܵ��´����⡣�������������֤��
 *       ��ȷ���յķ���������
 *
 *       symbolnum����Ϊ0�����ƽ�����ڼ�⵽lora���ź�������֤���ա�
 *
 *       symbolnum���ò�Ϊ0�����ȴ��ܹ�symbolnum�����ķ�����ȷ��֤�������ȷ��֤�ķ������������㣬������RX
 *       ��ʱIRQ�źš�
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_setsymbolnumtimeout_lora (am_zsl42x_lora_dev_t *p_dev,
                                             uint8_t               symbolnum);

/**
 * \brief LoRa getstatus ��ȡоƬ״̬����������ʱ�򷢳���
 * @{
 */

/** \brief �ɹ����յ����ݰ����ҿɶ�ȡ */
#define AM_ZSL42X_LORA_STATUS_FLAG_DATA_AVAILABLE       0x04

/** \brief ���������ʱ̫��������ʧ�� */
#define AM_ZSL42X_LORA_STATUS_FLAG_COMMAND_TIMEOUT      0x06

/** \brief ����������󣬻�������� */
#define AM_ZSL42X_LORA_STATUS_FLAG_COMMAND_ERROR        0x08

/** \brief ����������Ч�����޷�ִ������ */
#define AM_ZSL42X_LORA_STATUS_FLAG_COMMAND_NOT_EXECUTE  0x0A

/** \brief ������������ */
#define AM_ZSL42X_LORA_STATUS_FLAG_COMMAND_TX_DONE      0x0C

/** \brief ��ǰ����STBY_RCģʽ  */
#define AM_ZSL42X_LORA_STATUS_MODE_STBY_RC              0x20

/** \brief ��ǰ����STBY_XOSCģʽ  */
#define AM_ZSL42X_LORA_STATUS_MODE_STBY_XOSC            0x30

/** \brief ��ǰ����FSģʽ  */
#define AM_ZSL42X_LORA_STATUS_MODE_FS                   0x40

/** \brief ��ǰ����RXģʽ  */
#define AM_ZSL42X_LORA_STATUS_MODE_RX                   0x50

/** \brief ��ǰ����TXģʽ  */
#define AM_ZSL42X_LORA_STATUS_MODE_TX                   0x60
/** @} */

/**
 * \brief getstatus ��ȡоƬ״̬����������ʱ�򷢳���
 *
 * \param[in] p_dev  : lora�豸
 * \param[in] status : ״̬����
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getstatus (am_zsl42x_lora_dev_t *p_dev,
                              uint8_t              *p_status);

/**
 * \brief getrxbufferstatus ��ȡ����buffer��Ϣ
 *
 * \param[in] p_dev                : lora�豸
 * \param[in] rxstartbufferpointer : �������ݵ���ʼָ�루OUT��
 * \param[in] payloadlength        : �������ݳ��ȣ�OUT��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getrxbufferstatus (am_zsl42x_lora_dev_t *p_dev,
                                      uint8_t              *p_rxstartbufferpointer,
                                      uint8_t              *p_payloadlength);


/**
 * \brief LoRa getpacketstatus_fsk ��ȡFSK״̬
 */
typedef enum {
    AM_ZSL42X_LORA_FSK_STATUS_PREAMBLE_ERR = 0x80, /**< \brief ǰ�������� */
    AM_ZSL42X_LORA_FSK_STATUS_SYNC_ERR     = 0x40, /**< \brief ͬ������ */
    AM_ZSL42X_LORA_FSK_STATUS_ADRS_ERR     = 0x20, /**< \brief ��ַ���� */
    AM_ZSL42X_LORA_FSK_STATUS_CRC_ERR      = 0x10, /**< \brief CRC���� */
    AM_ZSL42X_LORA_FSK_STATUS_LENGTH_ERR   = 0x08, /**< \brief ���ȴ��� */
    AM_ZSL42X_LORA_FSK_STATUS_ABORT_ERR    = 0x04, /**< \brief ֹͣ���� */
    AM_ZSL42X_LORA_FSK_STATUS_PKT_RECEIVED = 0x02, /**< \brief ���ѽ��� */
    AM_ZSL42X_LORA_FSK_STATUS_PKT_SENT     = 0x01, /**< \brief ���ѷ��� */
} am_zsl42x_lora_fsk_status_t;

/**
 * \brief ���ݰ��ŵ�״̬��Ϣ
 */
typedef struct {
    uint8_t   packettype;

    struct {
        struct {
            uint8_t rxstatus;
            int8_t rssiavg;      /**< \brief The averaged RSSI */
            int8_t rssisync;     /**< \brief The RSSI measured on last packet */
            uint32_t freqerror;
        } fsk;

        struct {
            int8_t rssipkt;        /**< \brief The RSSI of the last packet */
            int8_t snrpkt;         /**< \brief The SNR of the last packet */
            int8_t signalrssipkt;
            uint32_t freqerror;
        } lora;
    } params;
} am_radio_packet_status_t;

/**
 * \brief getpacketstatus_lora ��ȡlora����Ϣ
 *
 * \param[in] p_dev         : lora�豸
 * \param[in] p_pktstate    : ���ݰ��ź�״̬��Ϣ��OUT��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getpacketstatus (am_zsl42x_lora_dev_t       *p_dev,
                                    am_radio_packet_status_t   *p_pktstate);

/**
 * \brief getrssiinst ���ڽ���ģʽʱ����ȡRSSI��˲��ֵ
 *
 * \param[in] p_dev      : lora�豸
 * \param[in] p_rssiinst : ���ڽ���ģʽʱ����ȡRSSI��˲��ֵ��OUT��
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getrssiinst (am_zsl42x_lora_dev_t *p_dev,
                                int8_t               *p_rssiinst);

/**
 * \brief getstats ��ȡ��󼸸����ݰ����յ�����Ϣ����
 *
 * \param[in] p_dev                        : lora�豸
 * \param[in] nbpkt_received               : nbpkt_received
 * \param[in] nbpkt_crcerror               : nbpkt_crcerror
 * \param[in] nbpkt_length_header_err      : nbpkt_length_err
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getstats (am_zsl42x_lora_dev_t *p_dev,
                             uint8_t              *nbpkt_received,
                             uint8_t              *nbpkt_crcerror,
                             uint8_t              *nbpkt_length_header_err);

/**
 * \brief resetstats ����getstats�����ȡ������
 *
 * \param[in] p_dev : lora�豸
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_resetstats (am_zsl42x_lora_dev_t *p_dev);

/**
 * \brief LoRa getdeviceerrors ��ȡӲ������״̬
 */
typedef enum {

    AM_ZSL42X_LORA_DEVICE_ERROR_RC64K_CALIB = 0x001, /**< \brief RC64KУ׼ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_RC13M_CALIB = 0x002, /**< \brief RC13MУ׼ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_PLL_CALIB   = 0x004, /**< \brief PLLУ׼ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_ADC_CALIB   = 0x008, /**< \brief ADCУ׼ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_IMG_CALIB   = 0x010, /**< \brief IMGУ׼ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_XOSC_START  = 0x020, /**< \brief XOSC����ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_PLL_LOCK    = 0x040, /**< \brief PLL����ʧ�� */
    AM_ZSL42X_LORA_DEVICE_ERROR_PA_RAMP     = 0x100, /**< \brief PA����ʧ��*/
} am_zsl42x_lora_getdeviceerrors_t;

/**
 * \brief getdeviceerrors ��ȡӲ������״̬
 *
 * \param[in] p_dev  : lora�豸
 * \param[in] status : ״̬���ݣ�OUT��--������am_zsl42x_lora_getdeviceerrors_tö�������жϾ������
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_getdeviceerrors (am_zsl42x_lora_dev_t *p_dev,
                                    uint16_t             *p_status);

/**
 * \brief resetstats ����getstats�����ȡ������
 *
 * \param[in] p_dev : lora�豸
 *
 * \return �ɹ����� AW_OK, ����ֵ��ʾʧ��
 */
int am_zsl42x_lora_cleardeviceerrors (am_zsl42x_lora_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZSL42X_LORA_REG_H */

/* end of file */
