/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/display.h>
#include <drivers/uart.h>
#include "dfr0299.h"

/* LCD */
#if DT_NODE_HAS_STATUS(DT_INST(0, sitronix_st7735r), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, sitronix_st7735r))
#endif

#ifdef CONFIG_SDL_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_SDL_DISPLAY_DEV_NAME
#endif

#ifdef CONFIG_DUMMY_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_DUMMY_DISPLAY_DEV_NAME
#endif
#ifdef CONFIG_ARCH_POSIX
#include "posix_board_if.h"
#endif

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000


#define UART2_NODE DT_ALIAS(uart_2)

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0  DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN   DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0    ""
#define PIN    0
#define FLAGS    0
#endif

/* uart fonctions */
void init_uart2(void)
{
//    /* enable GPIO clock */
//    rcu_periph_clock_enable(RCU_GPIOB);
//    /* enable USART clock */
//    rcu_periph_clock_enable(RCU_USART2);
//    /* connect port to USARTx_Tx */
//    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
//    /* connect port to USARTx_Rx */
//    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
//
//    /* USART configure */
//    usart_deinit(USART2);
//    usart_baudrate_set(USART2, 9600U);
//    usart_word_length_set(USART2, USART_WL_8BIT);
//    usart_stop_bit_set(USART2, USART_STB_1BIT);
//    usart_parity_config(USART2, USART_PM_NONE);
//    usart_hardware_flow_rts_config(USART2, USART_RTS_DISABLE);
//    usart_hardware_flow_cts_config(USART2, USART_CTS_DISABLE);
//    usart_receive_config(USART2, USART_RECEIVE_ENABLE);
//    usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
//    usart_enable(USART2);
//
//    usart_interrupt_enable(USART2, USART_INT_RBNE);
}





/* LCD function */
static inline uint32_t get_pixel_depth(
                            const enum display_pixel_format pixel_format)
{
    switch (pixel_format) {
    case PIXEL_FORMAT_ARGB_8888:
        return 4;
    case PIXEL_FORMAT_RGB_888:
        return 3;
    case PIXEL_FORMAT_RGB_565:
    case PIXEL_FORMAT_BGR_565:
        return 2;
    case PIXEL_FORMAT_MONO01:
    case PIXEL_FORMAT_MONO10:
        return 1;
    }

    return 0;
}

void main(void)
{
    const struct device *led_dev;
    const struct device *display_dev;
    const struct device *uart2_dev;
    struct display_capabilities capabilities;
    bool led_is_on = true;
    int ret;

    const struct uart_config uart2_cfg;

    /* test uart2 */
    uart2_dev = device_get_binding("UART_2");
	uart_config_get(uart2_dev, &uart2_cfg);

    /* init led */
    led_dev = device_get_binding(LED0);
    if (led_dev == NULL) {
        return;
    }
    ret = gpio_pin_configure(led_dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
    if (ret < 0) {
        return;
    }

    /* init lcd */
    display_dev = device_get_binding(DISPLAY_DEV_NAME);
    if (display_dev == NULL) {
        return;
    }
    display_get_capabilities(display_dev, &capabilities);
    uint32_t bufsize = capabilities.x_resolution \
               * capabilities.y_resolution \
               * get_pixel_depth(capabilities.current_pixel_format);
    bufsize = 12800;
    printk("display buffer size = %d\n", bufsize);



    while (1) {
        gpio_pin_set(led_dev, PIN, (int)led_is_on);
        led_is_on = !led_is_on;
        k_msleep(SLEEP_TIME_MS);
    }
}
