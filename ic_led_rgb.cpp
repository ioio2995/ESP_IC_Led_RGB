/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_check.h"
#include "ic_led_rgb.hpp"


const char* IC_Led_RGB::TAG = "IC_Led_RGB";

IC_Led_RGB::IC_Led_RGB( gpio_num_t gpio_num, uint32_t resolution_hz)
{
    ESP_LOGI(TAG, "Create RMT TX channel");
    led_chan = NULL;
    tx_chan_config = {
        .gpio_num = gpio_num,
        .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
        .resolution_hz = resolution_hz,
        .mem_block_symbols = 64, // increase the block size can make the LED less flickering
        .trans_queue_depth = 4, // set the number of transactions that can be pending in the background
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &led_chan));

    ESP_LOGI(TAG, "Install led strip encoder");
    led_encoder = NULL;
    encoder_config = {
        .resolution = resolution_hz,
    };
    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&encoder_config, &led_encoder));

    ESP_LOGI(TAG, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(led_chan));
    tx_config = {
        .loop_count = 0, // no transfer loop
    };

}

void IC_Led_RGB::set(uint8_t* led_strip_pixels, size_t length)
{
    ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, length, &tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
}