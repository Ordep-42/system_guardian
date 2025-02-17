#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/aht10/aht.h"
#include "inc/alarm/alarm.h"
#include "inc/led_rgb/led.h"
#include "inc/wifi/wifi_driver.h"
#include "inc/mqtt/mqtt_client.h"
#include "lwipopts.h"
#include "config.h"
#include "secrets.h"


int main() {
    stdio_init_all();
    sleep_ms(5000);

    aht_dev_t aht;
    aht_init(&aht, i2c0, AHT10_ADDRESS, 16, 17);

    adc_init();
    adc_gpio_init(POWER_METER_PIN);

    alarm_init();
    alarm_arm();

    if (wifi_driver_init()) {
        printf("Erro ao inicializar o driver Wi-Fi\n");
        return 1;
    }
    printf("Conectando a rede Wi-Fi...\n");

    if (wifi_driver_connect(WIFI_SSID, WIFI_PASS, 10000)) {
        printf("Falha ao conectar ao Wi-Fi\n");
        return 1;
    }else {
        printf("Wi-Fi conectado!\n");
    }
    
    printf("Endereço IP %s\n", ip_ntoa(wifi_driver_get_ip_address()));
    
    mqtt_init();

    uint32_t start = to_ms_since_boot(get_absolute_time());

    aht_data_t data;
    uint16_t power_draw;

    while (true) {
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

        if (to_ms_since_boot(get_absolute_time()) - start > 10000) {
            char buffer[8];
            sprintf(buffer, "%d", power_draw);
            mqtt_client_publish(MQTT_POWER_TOPIC, buffer);

            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "%.2f", data.temperature);
            mqtt_client_publish(MQTT_TEMP_TOPIC, buffer);

            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "%.2f", data.humidity);
            mqtt_client_publish(MQTT_HUMI_TOPIC, buffer);
            start = to_ms_since_boot(get_absolute_time());
        }
        
        wifi_driver_poll();
        sleep_ms(1000);
    }

    wifi_driver_deinit();
    return 0;
}
