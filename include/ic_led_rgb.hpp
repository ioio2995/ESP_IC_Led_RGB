#ifndef LED_RGB_HPP
#define LED_RGB_HPP

#include "freertos/FreeRTOS.h"
#include "driver/rmt_tx.h"

#include "led_encoder.h"


class IC_Led_RGB
{
public:
    IC_Led_RGB( gpio_num_t gpio_num, uint32_t resolution_hz);
    void set(uint8_t* led_strip_pixels, size_t length);

private:
    rmt_channel_handle_t led_chan;
    rmt_tx_channel_config_t tx_chan_config;
    rmt_encoder_handle_t led_encoder;
    led_strip_encoder_config_t encoder_config;
    rmt_transmit_config_t tx_config;
    static const char *TAG;
};
#endif // LED_RGB_HPP