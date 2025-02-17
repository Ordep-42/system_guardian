#pragma once

#include "lwip/ip_addr.h"

/**
 * @brief Inicializa o driver Wi-Fi.
 *
 * Esta função configura e inicializa o driver Wi-Fi, preparando-o para uso.
 *
 * @return Retorna 0 em caso de sucesso, ou um valor negativo em caso de erro.
 */
int wifi_driver_init();

/**
 * @brief Desinicializa o driver Wi-Fi.
 *
 * Esta função libera todos os recursos alocados pelo driver Wi-Fi e 
 * desativa qualquer funcionalidade relacionada ao Wi-Fi.
 */
void wifi_driver_deinit();

/**
 * @brief Função para realizar a verificação periódica do driver Wi-Fi.
 *
 * Esta função deve ser chamada periodicamente para verificar o estado do driver Wi-Fi
 * e realizar as operações necessárias para manter a conexão e o funcionamento adequado.
 */
void wifi_driver_poll();

/**
 * @brief Conecta-se a uma rede Wi-Fi com as credenciais fornecidas.
 *
 * @param ssid O SSID (nome) da rede Wi-Fi à qual se deseja conectar.
 * @param pass A senha da rede Wi-Fi.
 * @param timeout_ms O tempo limite em milissegundos para tentar a conexão.
 *
 * @return Um inteiro indicando o sucesso ou falha da conexão.
 *         Retorna 0 em caso de sucesso, ou um valor negativo em caso de erro.
 */
int wifi_driver_connect(const char *ssid, const char *pass, uint32_t timeout_ms);

/**
 * @brief Obtém o endereço IP atual do driver Wi-Fi.
 *
 * @return Ponteiro para a estrutura ip_addr_t contendo o endereço IP.
 */
ip_addr_t* wifi_driver_get_ip_address();

/**
 * @brief Verifica se o driver Wi-Fi está conectado.
 *
 * Esta função verifica o estado atual da conexão do driver Wi-Fi.
 *
 * @return true se o driver Wi-Fi estiver conectado, false caso contrário.
 */
bool wifi_driver_is_connected();

/**
 * @brief Obtém o status do driver Wi-Fi.
 *
 * Esta função retorna o status atual do driver Wi-Fi.
 *
 * @return Um inteiro representando o status do driver Wi-Fi.
 */
int wifi_driver_status();

/**
 * @brief Inicializa o driver WiFi com a pilha lwIP.
 *
 * Esta função configura e inicia o driver WiFi utilizando a pilha de 
 * protocolos lwIP, permitindo a comunicação de rede.
 */
void wifi_driver_lwip_begin();

/**
 * @brief Finaliza a interface do driver WiFi com o lwIP.
 *
 * Esta função encerra a interface do driver WiFi com a pilha de protocolos lwIP,
 * liberando quaisquer recursos alocados e garantindo que todas as conexões sejam
 * encerradas corretamente.
 */
void wifi_driver_lwip_end();