#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "inc/wifi/wifi_driver.h"
#include "lwip/apps/mqtt.h"
#include "secrets.h"

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("Conectado ao servidor MQTT\n");
    }else {
        printf("Erro ao conectar ao servidor MQTT %d\n", status);
    }
}

void mqtt_init(mqtt_client_t *client) {
    struct mqtt_connect_client_info_t client_info;
    memset(&client_info, 0, sizeof(client_info));
    
    client_info.client_id = MQTT_CLIENT_ID;
    client_info.client_user = MQTT_USER;
    client_info.client_pass = MQTT_PASS;
    client_info.keep_alive = 60;

    ip_addr_t ipaddr;
    IP4_ADDR(&ipaddr, IP_0, IP_1, IP_2, IP_3);

    err_t err = mqtt_client_connect(client, &ipaddr, MQTT_PORT, mqtt_connection_cb, client, &client_info);

    if (err != ERR_OK) {
        printf("Erro ao conectar ao servidor MQTT\n");
    }
}

void mqtt_pub_request_cb(void *arg, err_t result) {
    if (result == ERR_OK) {
        printf("Publicação realizada com sucesso\n");
    }else {
        printf("Erro ao publicar %d\n", result);
    }
}

void mqtt_example_publish(mqtt_client_t *client, char *topic, char *data) {
    uint8_t qos = 1;
    uint8_t retain = 0;
    err_t err = mqtt_publish(client, topic, data, strlen(data), qos, retain, mqtt_pub_request_cb, NULL);
    if (err != ERR_OK) {
        printf("Erro %d ao publicar no tópico %s\n", err, topic);
    }
}

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
    
    mqtt_client_t *client = mqtt_client_new();
    if (client == NULL) {
        printf("Erro ao criar o cliente MQTT\n");
        return 1;
    }
    mqtt_init(client);

    uint32_t start = to_ms_since_boot(get_absolute_time());

    while (true) {
        if (to_ms_since_boot(get_absolute_time()) - start > 10000) {
            mqtt_example_publish(client, MQTT_TOPIC, "Olá, Mundo!");
            start = to_ms_since_boot(get_absolute_time());
        }
        wifi_driver_poll();
        sleep_ms(100);
    }

    wifi_driver_deinit();
    return 0;
}