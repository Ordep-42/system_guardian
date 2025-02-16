#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "inc/wifi/wifi_driver.h"
#include "lwip/apps/mqtt.h"

#define WIFI_SSID "Amaral-2.4G"
#define WIFI_PASS "Tapi.Fred#142126712#AMARAL"

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
    
    uint8_t *ip_address = wifi_driver_get_ip_address();
    printf("Endereço IP %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    
    while (true) {
        wifi_driver_poll();
        sleep_ms(100);
    }

    wifi_driver_deinit();
    return 0;
}