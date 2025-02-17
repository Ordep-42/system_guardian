#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../buzzer/buzzer.h"
#include "../led_rgb/led.h"
#include "alarm.h"

bool _alarm_armed = false;
bool _alarm_triggered = false;
uint32_t _ms_since_last_alarm_IRQ = 0;
uint8_t _alarm_IRQ_delay = 60;

void _IRQ_alarm_callback() {
    if ((uint32_t)(to_ms_since_boot(get_absolute_time()) - _ms_since_last_alarm_IRQ) >= _alarm_IRQ_delay) {
        alarm_disable();
        _ms_since_last_alarm_IRQ = to_ms_since_boot(get_absolute_time());
    }
}

void alarm_init() {
    led_init(LED_R_PIN);
    led_init(LED_G_PIN);
    led_init(LED_B_PIN);
    buzzer_init(ALARM_BUZZER_PIN);
    led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, true, false, false);

    gpio_init(ALARM_BUTTON_PIN);
    gpio_set_dir(ALARM_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(ALARM_BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(ALARM_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &_IRQ_alarm_callback);
}

void alarm_arm() {
    _alarm_armed = true;
}

void alarm_trigger(bool red_state, bool green_state, bool blue_state, uint duration_ms) {
    _alarm_triggered = true;
    if (_alarm_armed) {
        while (_alarm_triggered) {
            led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, red_state, green_state, blue_state);
            beep(ALARM_BUZZER_PIN, duration_ms);
            sleep_ms(duration_ms);
        }
    }
}

void alarm_disable() {
    _alarm_triggered = false;
}


