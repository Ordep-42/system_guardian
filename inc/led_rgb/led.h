#pragma once

void led_init(uint8_t pin);
void led_set_color(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, bool red_state, bool green_state, bool blue_state);