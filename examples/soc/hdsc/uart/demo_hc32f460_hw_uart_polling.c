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
 * \brief UART 轮询方式例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. 指定串口输出 "HW example---UART test in polling mode:"；
 *   2. 指定串口输出接收到的字符串。
 *
 * \par 源代码
 * \snippet demo_hc32_hw_uart_polling.c src_hc32_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-11  cds, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_hc32f460_hw_uart_polling
 * \copydoc demo_hc32f460_hw_uart_polling.c
 */

/** [src_hc32f460_hw_uart_polling] */
#include "ametal.h"
#include "hw/amhw_hc32f460_uart.h"

/*******************************************************************************
  宏定义
*******************************************************************************/
#define UART_BAUDRATE     (115200)              /** <\brief 波特率 */

/*******************************************************************************
  全局变量
*******************************************************************************/
static const uint8_t uart_hw_str[] =
                                {"HW example---UART test in polling mode:\r\n"};

/**
 * \brief UART HW 查询收发初始化
 */
static void uart_polling_init (amhw_hc32f460_uart_t *p_hw_uart, uint32_t clk_rate)
{

    /* 等待发送完成 */
    while (amhw_hc32f460_uart_status_flag_check(p_hw_uart,
    		                                    AMHW_HC32F460_UART_TX_COMPLETE_FALG) ==
                                                AM_FALSE);

    /* 停止位设置 */
    amhw_hc32f460_uart_stop_bit_sel(p_hw_uart  , AMHW_HC32F460_UART_STOP_1BIT);

    /* 校验设置 */
    amhw_hc32f460_uart_parity_bit_sel(p_hw_uart, AMHW_HC32F460_UART_PARITY_NO);

    /* 波特率设置 */
    amhw_hc32f460_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    /* 禁能串口所有中断 */
    amhw_hc32f460_uart_int_disable(p_hw_uart, AMHW_HC32F460_UART_INT_ALL_ENABLE_MASK);

    /* 使能串口收发功能 */
    amhw_hc32f460_uart_rx_enable (p_hw_uart, AM_TRUE);
    amhw_hc32f460_uart_tx_enable (p_hw_uart, AM_TRUE);
}

/**
 * \brief 例程入口
 */
void demo_hc32f460_hw_uart_polling_entry (void     *p_hw_uart,
                                          uint32_t  clk_rate)
{

    /* 数据缓冲区 */
    uint8_t buf_src[256];
    amhw_hc32f460_uart_t * p_uart = (amhw_hc32f460_uart_t * )p_hw_uart;

    /* UART查询初始化 */
    uart_polling_init(p_uart, clk_rate);

    amhw_hc32f460_uart_poll_send(p_uart, uart_hw_str, sizeof(uart_hw_str));

    while (1) {

        /* 接收字符 */
        amhw_hc32f460_uart_poll_receive(p_uart, buf_src, 1);

        /* 发送刚刚接收的字符 */
        amhw_hc32f460_uart_poll_send(p_uart, buf_src, 1);
    }
}
/** [src_hc32f460_hw_uart_polling] */

/* end of file */
