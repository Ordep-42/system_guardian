#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "led.h"

void led_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void led_set_color(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, bool red_state, bool green_state, bool blue_state) {
    gpio_put(red_pin, red_state);
    gpio_put(green_pin, green_state);
    gpio_put(blue_pin, blue_state);
}