#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lwip/apps/mqtt.h"
#include "../wifi/wifi_driver.h"
#include "mqtt_client.h"
#include "config.h"
#include "secrets.h"

mqtt_client_t *client;

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("Conectado ao servidor MQTT\n");
    }else {
        printf("Erro ao conectar ao servidor MQTT %d\n", status);
    }
}

void mqtt_init() {
    struct mqtt_connect_client_info_t client_info;
    memset(&client_info, 0, sizeof(client_info));
    
    client_info.client_id = MQTT_CLIENT_ID;
    client_info.client_user = MQTT_USER;
    client_info.client_pass = MQTT_PASS;
    client_info.keep_alive = 60;
    
    client = mqtt_client_new();

    ip_addr_t ipaddr;
    ip4addr_aton(MQTT_SERVER_IP, &ipaddr);
    err_t err;

    wifi_driver_lwip_begin();
    err = mqtt_client_connect(client, &ipaddr, MQTT_PORT, mqtt_connection_cb, &client, &client_info);
    wifi_driver_lwip_end();
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

void mqtt_client_publish(char *topic, char *data) {
    uint8_t qos = 1;
    uint8_t retain = 0;
    wifi_driver_lwip_begin();
    err_t err = mqtt_publish(client, topic, data, strlen(data), qos, retain, mqtt_pub_request_cb, NULL);
    wifi_driver_lwip_end();
    if (err != ERR_OK) {
        printf("Erro %d ao publicar no tópico %s\n", err, topic);
    }
}
