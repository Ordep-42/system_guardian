#pragma once

#define ALARM_BUZZER_PIN 21
#define ALARM_BUTTON_PIN 5

/**
 * @brief Inicializa o sistema de alarme.
 *
 * Esta função configura e inicializa todos os componentes necessários
 * para o funcionamento do sistema de alarme.
 */
void alarm_init();

/**
 * @brief Ativa o alarme.
 * 
 * Esta função é responsável por armar o alarme, preparando-o para disparar
 * quando uma condição específica for atendida.
 */
void alarm_arm();

/**
 * @brief Aciona o alarme com base nos estados das cores e na duração especificada.
 *
 * Esta função aciona o alarme configurando os estados das cores (vermelho, verde e azul)
 * e a duração em milissegundos que o alarme deve permanecer ativo.
 *
 * @param red_state Estado da cor vermelha (true para ligado, false para desligado).
 * @param green_state Estado da cor verde (true para ligado, false para desligado).
 * @param blue_state Estado da cor azul (true para ligado, false para desligado).
 * @param duration_ms Duração em milissegundos que o alarme deve permanecer ativo.
 */
void alarm_trigger(bool red_state, bool green_state, bool blue_state, uint duration_ms);

/**
 * @brief Desativa o alarme.
 *
 * Esta função desativa o alarme, interrompendo qualquer sinal ou ação
 * que esteja sendo executada pelo alarme.
 */
void alarm_disable();