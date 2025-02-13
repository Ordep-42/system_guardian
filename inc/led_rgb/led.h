#pragma once

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12

void led_init(uint8_t pin);
void led_set_color(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, bool red_state, bool green_state, bool blue_state);