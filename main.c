#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "inc/wifi/wifi_driver.h"
#include "inc/mqtt/mqtt_client.h"
#include "secrets.h"


int main() {
    stdio_init_all();
    sleep_ms(5000);

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

    while (true) {
        if (to_ms_since_boot(get_absolute_time()) - start > 10000) {
            mqtt_client_publish(MQTT_TOPIC, "Olá, Mundo!");
            start = to_ms_since_boot(get_absolute_time());
        }
        wifi_driver_poll();
        sleep_ms(100);
    }

    wifi_driver_deinit();
    return 0;
}