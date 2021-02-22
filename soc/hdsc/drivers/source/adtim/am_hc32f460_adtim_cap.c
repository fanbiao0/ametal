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
 * \brief ADTIM���������벶��������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-08  zp, first implementation
 * \endinternal
 */
#include "hc32f460_clk.h"
#include "am_hc32f460_adtim_cap.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_clk.h"
#include "hc32f460_irq_handle.h"
#include "hc32f460_intctrl.h"
#include "am_vdebug.h"
/*******************************************************************************
* ˽�ж���
*******************************************************************************/
static uint16_t  __update_num = 0;

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����������� */
static int __hc32f460_adtim_cap_config (void              *p_cookie,
                                      int                chan,
                                      unsigned int       flags,
                                      am_cap_callback_t  pfn_callback,
                                      void              *p_arg);

/** \brief ʹ�ܲ���ͨ�� */
static int __hc32f460_adtim_cap_enable (void *p_drv, int chan);

/** \brief ���ܲ���ͨ�� */
static int __hc32f460_adtim_cap_disable (void *p_drv, int chan);

/** \brief ��λ����ͨ������ֵ */
static int __hc32f460_adtim_cap_reset (void *p_drv, int chan);

static int __hc32f460_adtim_cap_count_to_adtime (void         *p_drv,
                                                 int           chan,
                                                 unsigned int  count1,
                                                 unsigned int  count2,
                                                 unsigned int *p_adtime_ns);

static void __hc32f460_adtim_cap_irq_handler (void *p_arg);

#define TMR6x_GCMA    (1 << 0)
#define TMR6x_GCMB    (1 << 1)
#define TMR6x_GCMC    (1 << 2)
#define TMR6x_GCMD    (1 << 3)
#define TMR6x_GCME    (1 << 4)
#define TMR6x_GCMF    (1 << 5)
#define TMR6x_GOVF    (1 << 6)
#define TMR6x_GUDF    (1 << 7)
#define TMR6x_GDTE    (1 << 8)
#define TMR6x_SCMA    (1 << 11)
#define TMR6x_SCMB    (1 << 12)


/** \brief ��������������� */
static const struct am_cap_drv_funcs __g_adtim_cap_drv_funcs = {
    __hc32f460_adtim_cap_config,
    __hc32f460_adtim_cap_enable,
    __hc32f460_adtim_cap_disable,
    __hc32f460_adtim_cap_reset,
    __hc32f460_adtim_cap_count_to_adtime,
};

/******************************************************************************/

/** \brief ����һ�����벶��ͨ�� */
static int __hc32f460_adtim_cap_config (void              *p_drv,
                                        int                chan,
                                        unsigned int       options,
                                        am_cap_callback_t  pfn_callback,
                                        void              *p_arg)
{
    am_hc32f460_adtim_cap_dev_t *p_dev      = (am_hc32f460_adtim_cap_dev_t *)p_drv;
    amhw_hc32f460_adtim_t       *p_hw_adtim = (amhw_hc32f460_adtim_t *)
                                              p_dev->p_devinfo->tim_regbase;

    amhw_hc32f460_adtim_timx_chx_port_cfg_t portcfg;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->chan_max) {
        return -AM_EINVAL;
    }

    portcfg.portmode  = AMHW_HC32F460_ADTIM_PORT_MODE_CAP_INPUT;
    portcfg.outenable = AM_FALSE;
    portcfg.perc      = AMHW_HC32F460_ADTIM_PERIOD_LOW;
    portcfg.cmpc      = AMHW_HC32F460_ADTIM_COMPARE_LOW;
    portcfg.stastps   = AMHW_HC32F460_ADTIM_STATE_SEL_SS;
    portcfg.staout    = AMHW_HC32F460_ADTIM_PORT_OUT_LOW;
    portcfg.stpout    = AMHW_HC32F460_ADTIM_PORT_OUT_LOW;
    portcfg.disval    = AMHW_HC32F460_ADTIM_DISVAL_NORM;
    portcfg.dissel    = AMHW_HC32F460_ADTIM_DISSEL0;
    portcfg.fltenable = AM_FALSE;
    portcfg.fltclk    = AMHW_HC32F460_ADTIM_FLTCLK_PCLK_DIV1;

    /* �˿����� */
    amhw_hc32f460_adtim_timxchxportcfg(p_hw_adtim, 
                                       (amhw_hc32f460_adtim_chx_t)chan,
                                       &portcfg);

    /*  ѡ�������ش��� */
    if ((options & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {
        if(chan == 0) {
            amhw_hc32f460_adtim_cfghwcaptureA(p_hw_adtim,
                                              AMHW_HC32F460_ADTIM_HwTrigCHxARise);
        } else {
            amhw_hc32f460_adtim_cfghwcaptureB(p_hw_adtim,
                                              AMHW_HC32F460_ADTIM_HwTrigCHxBRise);
        }
    }

    /*  ѡ���½��ش��� */
    if ((options & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {
        if(chan == 0) {
            amhw_hc32f460_adtim_cfghwcaptureA(p_hw_adtim,
                                              AMHW_HC32F460_ADTIM_HwTrigCHxAFall);
        } else {
            amhw_hc32f460_adtim_cfghwcaptureB(p_hw_adtim,
                                              AMHW_HC32F460_ADTIM_HwTrigCHxBFall);
        }
    }

    p_dev->adtim_callback_info[chan].callback_func = pfn_callback;
    p_dev->adtim_callback_info[chan].p_arg         = p_arg;

    return AM_OK;
}

/** \brief ����ʹ�� */
static int __hc32f460_adtim_cap_enable (void *p_drv, int chan)
{
    int i = 0, enable_flag = 0, tmr6x_gcmx = 0, adtim_period = 0;

    am_hc32f460_adtim_cap_dev_t    *p_dev      = (am_hc32f460_adtim_cap_dev_t *)
                                                  p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim = (amhw_hc32f460_adtim_t *)
                                                  p_dev->p_devinfo->tim_regbase;
    am_hc32f460_adtim_cap_ioinfo_t *p_ioinfo   = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->chan_max) {
        return -AM_EINVAL;
    }

    /* �������� */
    for(i = 0; i < p_dev->p_devinfo->channels_num; i++) {
        if((p_ioinfo[i].channel & 0x7f) ==  chan){
            am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].func);
            enable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(enable_flag == 0){
        return -AM_EINVAL;
    }

    if (AMHW_HC32F460_ADTIM_CHX_A == chan)
    {
        tmr6x_gcmx = TMR6x_GCMA;
        adtim_period = ADTIM_PERIODA;
    } else if (AMHW_HC32F460_ADTIM_CHX_B == chan) {
        tmr6x_gcmx = TMR6x_GCMB;        
        adtim_period = ADTIM_PERIODB;
    } else {
        ;
    }

    /* �ж����Ӳ�ʹ�� */
    if ((amhw_hc32f460_adtim_t *)HC32F460_TMR61_BASE == p_hw_adtim)
    {    
        am_int_connect(p_dev->p_devinfo->inum, IRQ131_Handler, NULL);
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (tmr6x_gcmx) << 0);
    }else if ((amhw_hc32f460_adtim_t *)HC32F460_TMR62_BASE == p_hw_adtim)
    {    
        am_int_connect(p_dev->p_devinfo->inum, IRQ131_Handler, NULL);      
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (tmr6x_gcmx) << 16);
    }else if ((amhw_hc32f460_adtim_t *)HC32F460_TMR63_BASE == p_hw_adtim)
    {
        am_int_connect(p_dev->p_devinfo->inum, IRQ132_Handler, NULL);    
        amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, (tmr6x_gcmx) << 0);
    }else {
        ;
    }  

    /* �жϺ�ʹ�� */
    am_int_enable(p_dev->p_devinfo->inum);

    /* ���ü������� */
    amhw_hc32f460_adtim_setperiod(p_hw_adtim, (adtim_period_x_t)adtim_period, 0xffff);
    
    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    /* ���������ж� */
    amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFIrq, AM_TRUE);

    /* �����ж�ʹ�� */
    if(chan == 0) {
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_CMAIrq, AM_TRUE);
    } else {
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_CMBIrq, AM_TRUE);
    }

    /* ��������жϱ�־ */
    amhw_hc32f460_adtim_clearallirqflag(p_hw_adtim);

    /* ��ʱ������ */
    amhw_hc32f460_adtim_startcount(p_hw_adtim);

    return AM_OK;
}

/** \brief ������� */
static int __hc32f460_adtim_cap_disable (void *p_drv, int chan)
{
    int i = 0, disable_flag = 0;
    am_hc32f460_adtim_cap_dev_t    *p_dev      = (am_hc32f460_adtim_cap_dev_t *)
                                                  p_drv;
    amhw_hc32f460_adtim_t          *p_hw_adtim = (amhw_hc32f460_adtim_t *)
                                                  p_dev->p_devinfo->tim_regbase;
    am_hc32f460_adtim_cap_ioinfo_t *p_ioinfo   = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ���ŷ�Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* ��ԭ�������� */
    for(i = 0; i < p_dev->p_devinfo->channels_num; i++) {
        if((p_ioinfo[i].channel & 0x7f) ==  chan){
            am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].dfunc);
            disable_flag = 1;
            break;
        }
    }

    /* ����ͨ������Ч */
    if(disable_flag == 0){
        return -AM_EINVAL;
    }

    /* �Ͽ�NVIC�жϻص����� */
    am_int_disconnect(p_dev->p_devinfo->inum,
                      __hc32f460_adtim_cap_irq_handler,
                      (void *)p_dev);

    /* �жϺŽ��� */
    am_int_disable(p_dev->p_devinfo->inum);

    /* ��ֹ�����ж� */
    amhw_hc32f460_adtim_cfgirq(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFIrq, AM_FALSE);

    /* �����жϽ��� */
    if(chan == 0) {
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim,
                                 AMHW_HC32F460_ADTIM_CMAIrq,
                                 AM_FALSE);
    } else {
        amhw_hc32f460_adtim_cfgirq(p_hw_adtim,
                                 AMHW_HC32F460_ADTIM_CMBIrq,
                                 AM_FALSE);
    }

    /* ��ʱ��ֹͣ */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    return AM_OK;
}

/**
  * \brief ��λ����ͨ������ֵ
  */
static int __hc32f460_adtim_cap_reset (void *p_drv, int chan)
{
    am_hc32f460_adtim_cap_dev_t *p_dev      = (am_hc32f460_adtim_cap_dev_t *)p_drv;
    amhw_hc32f460_adtim_t       *p_hw_adtim = (amhw_hc32f460_adtim_t *)
                                               p_dev->p_devinfo->tim_regbase;

    /* ��ʱ��ֹͣ */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    /* ��������жϱ�־ */
    amhw_hc32f460_adtim_clearallirqflag(p_hw_adtim);

    /* ��ʱ������ */
    amhw_hc32f460_adtim_startcount(p_hw_adtim);

    return AM_OK;
}

/**
  * \brief ת�����β���ֵΪʱ��ֵ
  */
static int __hc32f460_adtim_cap_count_to_adtime (void         *p_drv,
                                                 int           chan,
                                                 unsigned int  count1,
                                                 unsigned int  count2,
                                                 unsigned int *p_adtime_ns)
{
    am_hc32f460_adtim_cap_dev_t *p_dev      = (am_hc32f460_adtim_cap_dev_t *)p_drv;

    uint32_t count_err;
    uint64_t time_ns;
    uint16_t reg_pre = 1, pre = 1;

    uint32_t clkfreq  = am_clk_rate_get(CLK_TIMER6_1);

    reg_pre = (uint16_t)p_dev->p_devinfo->clk_div;

    if(reg_pre >= 5) {
        pre = 1 << (reg_pre * 2 - 4);
    } else {
        pre = 1 << reg_pre;
    }

    count_err =  count2 - count1;

    /* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
    time_ns = (uint64_t)1000000000 *
              (uint64_t)count_err  *
              pre                  /
              (uint64_t)clkfreq;

    *p_adtime_ns = time_ns;

    return AM_OK;
}

/**
  * \brief �жϷ�����
  */
static void __hc32f460_adtim_cap_irq_handler (void *p_arg)
{
    am_hc32f460_adtim_cap_dev_t *p_dev       = (am_hc32f460_adtim_cap_dev_t *)p_arg;
    amhw_hc32f460_adtim_t       *p_hw_adtim  = (amhw_hc32f460_adtim_t *)
                                                p_dev->p_devinfo->tim_regbase;

    am_cap_callback_t callback_func;
    uint32_t          value;
    
    if ((amhw_hc32f460_adtim_get_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFF_FLAG)) == AM_TRUE) {

        __update_num++;

        amhw_hc32f460_adtim_clearcount(p_hw_adtim);

        amhw_hc32f460_adtim_clear_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_OVFF_FLAG);
    }

    if (amhw_hc32f460_adtim_get_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_CMAF_FLAG) == AM_TRUE) {

        callback_func = p_dev->adtim_callback_info[0].callback_func;

        /* �õ�ͨ��A��ֵ */
        value = amhw_hc32f460_adtim_getcapturevalue(p_hw_adtim, AMHW_HC32F460_ADTIM_CHX_A) +
                (__update_num << 16ul);

        if (callback_func != NULL) {
            callback_func(p_dev->adtim_callback_info[0].p_arg, value);
        }

        /* ���ͨ��A��־ */
        amhw_hc32f460_adtim_clear_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_CMAF_FLAG);
    }

    if (amhw_hc32f460_adtim_get_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_CMBF_FLAG) == AM_TRUE) {

        callback_func = p_dev->adtim_callback_info[1].callback_func;

        /* �õ�ͨ��B��ֵ */
        value = amhw_hc32f460_adtim_getcapturevalue(p_hw_adtim, AMHW_HC32F460_ADTIM_CHX_B) +
                (__update_num << 16ul);

        if (callback_func != NULL) {
            callback_func(p_dev->adtim_callback_info[1].p_arg, value);
        }

        /* ���ͨ��B��־ */
        amhw_hc32f460_adtim_clear_status_flag(p_hw_adtim, AMHW_HC32F460_ADTIM_CMBF_FLAG);
    }
}

/**
  * \brief �����ʼ��
  */
void __hc32f460_adtim_cap_init (amhw_hc32f460_adtim_t       *p_hw_adtim,
                                am_hc32f460_adtim_cap_dev_t *p_dev)
{
    amhw_hc32f460_adtim_basecnt_cfg_t basecnt;

    basecnt.cntmode   = AMHW_HC32F460_ADTIM_CNT_MODE_SAWTOOTH;
    basecnt.cntdir    = AMHW_HC32F460_ADTIM_CNT_DIR_UP;
    basecnt.cntclkdiv = p_dev->p_devinfo->clk_div;

    /* ���ö�ʱ��ģʽ���������򡢼���ʱ�ӷ�Ƶϵ�� */
    amhw_hc32f460_adtim_init(p_hw_adtim, &basecnt);

    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    __update_num = 0;

}

am_cap_handle_t am_hc32f460_adtim_cap_init (
                    am_hc32f460_adtim_cap_dev_t           *p_dev,
                    const am_hc32f460_adtim_cap_devinfo_t *p_devinfo)
{
    amhw_hc32f460_adtim_t *p_hw_adtim = NULL;
    uint8_t    i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->chan_max = 2;

    if(p_dev->chan_max < p_devinfo->channels_num) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo        = p_devinfo;
    p_hw_adtim              = (amhw_hc32f460_adtim_t *)
                              p_dev->p_devinfo->tim_regbase;
    p_dev->cap_serv.p_funcs = (struct am_cap_drv_funcs *)
                              &__g_adtim_cap_drv_funcs;
    p_dev->cap_serv.p_drv   = p_dev;

    for (i = 0; i < p_devinfo->channels_num; i++) {
        p_dev->adtim_callback_info[i].callback_func = NULL;
    }

    /* �����ʼ�� */
    __hc32f460_adtim_cap_init(p_hw_adtim, p_dev);

    return &(p_dev->cap_serv);
}

void am_hc32f460_adtim_cap_deinit (am_cap_handle_t handle)
{
    uint8_t i = 0;

    am_hc32f460_adtim_cap_dev_t *p_dev      = (am_hc32f460_adtim_cap_dev_t *)handle;
    amhw_hc32f460_adtim_t       *p_hw_adtim = NULL;

    am_hc32f460_adtim_cap_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_adtim = (amhw_hc32f460_adtim_t *)p_dev->p_devinfo->tim_regbase;

    /* ��������� */
    amhw_hc32f460_adtim_clearcount(p_hw_adtim);

    __update_num = 0;

    /* �ر�TIMģ�� */
    amhw_hc32f460_adtim_stopcount(p_hw_adtim);

    /* �ֶ���λ�Ĵ��� */
    amhw_hc32f460_adtim_deinit(p_hw_adtim);

    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->cap_serv.p_drv = NULL;

    /* ��ԭGPIO���� */
    for (i = 0; i <p_dev->p_devinfo->channels_num; i++) {

        am_gpio_pin_cfg(p_ioinfo[i].gpio, p_ioinfo[i].dfunc);
    }

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

void Timer61GCMA_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer61GCMB_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer61GCMC_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer61GCMD_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer61GCME_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer61GCMF_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}


void Timer62GCMA_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer62GCMB_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer62GCMC_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer62GCMD_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer62GCME_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer62GCMF_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}


void Timer63GCMA_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer63GCMB_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer63GCMC_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer63GCMD_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer63GCME_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}
void Timer63GCMF_IrqHandler(void *p_arg)
{
    __hc32f460_adtim_cap_irq_handler(p_arg);
}

/* end of file */