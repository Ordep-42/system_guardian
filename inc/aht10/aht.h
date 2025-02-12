#pragma once

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define AHT10_ADDRESS 0x38

/**
 * @brief Enumeração que define o status do sensor AHT10.
 */
typedef enum { NOT_CALIBRATED = -2, BUSY = -1, CALIBRATED = 0 } aht_status_t;

/**
 * @brief Estrutura que representa um dispositivo AHT10.
 *
 * @param i2c_address Endereço I2C do dispositivo AHT10.
 * @param sda_pin Pino de dados I2C (SDA).
 * @param scl_pin Pino de clock I2C (SCL).
 * @param i2c_port Porta I2C utilizada para comunicação.
 * @param status Status atual do dispositivo AHT10.
 */
typedef struct {
    uint8_t i2c_address;
    uint8_t sda_pin, scl_pin;
    i2c_inst_t *i2c_port;
    aht_status_t status;
} aht_dev_t;

/**
 * @brief Estrutura para armazenar dados de temperatura e umidade do sensor
 * AHT10.
 *
 * @struct aht_data_t
 * @param temperature
 * Membro que armazena a temperatura medida pelo sensor AHT10.
 *
 * @param humidity
 * Membro que armazena a umidade medida pelo sensor AHT10.
 */
typedef struct {
    float temperature;
    float humidity;
} aht_data_t;

/**
 * @brief Inicializa o dispositivo AHT10.
 *
 * Esta função configura e inicializa o sensor AHT10 com os parâmetros
 * fornecidos.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 * @param i2c_port Ponteiro para a instância da porta I2C.
 * @param i2c_address Endereço I2C do dispositivo AHT10.
 * @param sda_pin Número do pino SDA.
 * @param scl_pin Número do pino SCL.
 *
 * @return PICO_ERROR_NONE em caso de sucesso, ou um código de erro negativo em
 * caso de falha.
 */
int aht_init(aht_dev_t *dev, i2c_inst_t *i2c_port, uint8_t i2c_address,
             uint8_t sda_pin, uint8_t scl_pin);

/**
 * @brief Calibra o dispositivo AHT10.
 *
 * Esta função envia o comando de calibração para o dispositivo AHT10 para
 * garantir leituras precisas de temperatura e umidade.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 *
 * @return Retorna PICO_ERROR_NONE em caso de sucesso, ou um código de erro
 * negativo em caso de falha.
 */
int aht_calibrate(aht_dev_t *dev);

/**
 * @brief Realiza o reset de software do dispositivo AHT10.
 *
 * Esta função envia um comando de reset de software para o dispositivo AHT10,
 * reiniciando-o e colocando-o em seu estado inicial.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 *
 * @return Retorna PICO_ERROR_NONE em caso de sucesso, ou um código de erro
 * negativo em caso de falha.
 */
int aht_soft_reset(aht_dev_t *dev);

/**
 * @brief Lê os dados do sensor AHT10.
 *
 * Esta função lê os dados do sensor AHT10 e armazena-os na estrutura fornecida.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 * @param data Ponteiro para a estrutura onde os dados lidos serão armazenados.
 *
 * @return Retorna PICO_ERROR_NONE em caso de sucesso, ou um código de erro em
 * caso de falha.
 */
int aht_read_data(aht_dev_t *dev, aht_data_t *data);