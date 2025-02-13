#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "inc/aht10/aht.h"
#include "inc/alarm/alarm.h"
#include "inc/led_rgb/led.h"

#define POWER_METER_PIN 28
#define POWER_METER_ADC 2

void sensor_task(void *pvParameters)
{
    aht_dev_t aht;
    aht_init(&aht, i2c0, AHT10_ADDRESS, 16, 17);

    adc_init();
    adc_gpio_init(POWER_METER_PIN);

    uint16_t power_draw;
    aht_data_t data;

    for (;;) {
        adc_select_input(POWER_METER_ADC);
        power_draw = adc_read() / 1.3;

        if (aht_read_data(&aht, &data) == PICO_ERROR_NONE) {
            printf("Temperature: %.2f C\n", data.temperature);
            printf("Humidity: %.2f %%\n", data.humidity);
            printf("Power: %d\n", power_draw);
            if (data.temperature >= 40 || data.humidity >= 90 || power_draw >= 2800) {
                alarm_trigger(true, false, false, 300);
            } else if ((data.temperature >= 30 && data.temperature < 40) || (data.humidity < 90 && data.humidity >= 80) || (power_draw >= 2000 && power_draw < 2800)) {
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

    sensor_task(NULL);
}
