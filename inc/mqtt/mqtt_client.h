#pragma once

/**
 * @brief Inicializa o cliente MQTT.
 *
 * Esta função configura e inicializa o cliente MQTT, preparando-o para
 * estabelecer conexões e realizar operações de publicação e assinatura.
 */
void mqtt_init();

/**
 * @brief Publica uma mensagem em um tópico MQTT.
 *
 * Esta função envia uma mensagem para o tópico especificado no broker MQTT.
 *
 * @param topic O tópico no qual a mensagem será publicada.
 * @param data A mensagem a ser publicada no tópico.
 */
void mqtt_client_publish(char *topic, char *data);