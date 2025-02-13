#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/aht10/aht.h"
#include "inc/alarm/alarm.h"
#include "inc/led_rgb/led.h"

void termo_task(void *pvParameters)
{
    aht_dev_t aht;
    aht_init(&aht, i2c0, AHT10_ADDRESS, 16, 17);

    aht_data_t data;
    for (;;) {
        if (aht_read_data(&aht, &data) == PICO_ERROR_NONE) {
            printf("Temperature: %.2f C\n", data.temperature);
            printf("Humidity: %.2f %%\n", data.humidity);
            if (data.temperature >= 40 || data.humidity >= 90) {
                alarm_trigger(true, false, false, 300);
            } else if ((data.temperature >= 30 && data.temperature < 40) || (data.humidity < 90 && data.humidity >= 80)) {
                led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, true, true, false);
            } else {
                led_set_color(LED_R_PIN, LED_G_PIN, LED_B_PIN, false, true, false);
            }
        }
        sleep_ms(1000);
    }
}

int main()
{
    stdio_init_all();

    alarm_init();
    alarm_arm();

    termo_task(NULL);
}
