/**
 * @file secrets.example.h
 * @brief Arquivo de exemplo para configuração de credenciais.
 *
 * Este arquivo contém definições de macros para as credenciais de conexão
 * com a rede Wi-Fi e o servidor MQTT. As credenciais reais devem ser
 * substituídas no arquivo de configuração final.
 *
 * @note Renomeie este arquivo para `secrets.h` e substitua os valores
 *       de exemplo pelas suas credenciais reais antes de compilar o projeto.
*/
#pragma once

/**
 * @def MQTT_USER
 * @brief Nome de usuário para autenticação no servidor MQTT.
 */
#define MQTT_USER "username"

/**
 * @def MQTT_PASS
 * @brief Chave de acesso para autenticação no servidor MQTT.
 */
#define MQTT_PASS "passkey"

/**
 * @def WIFI_SSID
 * @brief Nome da rede Wi-Fi à qual o dispositivo deve se conectar.
 */
#define WIFI_SSID "seu_ssid"

/**
 * @def WIFI_PASS
 * @brief Senha da rede Wi-Fi à qual o dispositivo deve se conectar.
 */
#define WIFI_PASS "sua_senha"