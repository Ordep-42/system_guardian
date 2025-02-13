#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "inc/alarm/alarm.h"
#include "inc/led_rgb/led.h"

int main()
{
    stdio_init_all();

    alarm_init();
    alarm_arm();

    while (true) {
        led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, false, true, false);
        sleep_ms(5000);
        led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, true, true, false);
        sleep_ms(5000);

        alarm_trigger(true, false, false, 300);
    }
}
