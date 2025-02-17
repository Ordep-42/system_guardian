#pragma once

/**
 * @brief Inicializa o buzzer no pino especificado.
 *
 * Esta função configura o pino especificado como saída e inicializa o buzzer.
 *
 * @param pin O pino onde o buzzer está conectado.
 */
void buzzer_init(uint8_t pin);

/**
 * @brief Emite um som de beep através de um buzzer.
 *
 * Esta função faz com que um buzzer emita um som de beep por um determinado
 * período de tempo.
 *
 * @param pin O pino ao qual o buzzer está conectado.
 * @param duration_ms A duração do beep em milissegundos.
 */
void beep(uint8_t pin, uint duration_ms);