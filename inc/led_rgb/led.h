#pragma once

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12

/**
 * @brief Inicializa o LED no pino especificado.
 *
 * Esta função configura o pino especificado como saída e inicializa o LED RGB.
 *
 * @param pin O pino onde o LED está conectado.
 */
void led_init(uint8_t pin);

/**
 * @brief Configura a cor do LED RGB.
 *
 * Esta função define o estado dos pinos de um LED RGB para configurar sua cor.
 *
 * @param red_pin Pino correspondente ao LED vermelho.
 * @param green_pin Pino correspondente ao LED verde.
 * @param blue_pin Pino correspondente ao LED azul.
 * @param red_state Estado do LED vermelho (true para ligado, false para desligado).
 * @param green_state Estado do LED verde (true para ligado, false para desligado).
 * @param blue_state Estado do LED azul (true para ligado, false para desligado).
 */
void led_set_color(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, bool red_state, bool green_state, bool blue_state);