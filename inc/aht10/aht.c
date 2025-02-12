#include "aht.h"

#define CMD_INIT 0xE1      // Inicializa e calibra o sensor
#define CMD_TRIGGER 0xAC   // Inicia a medição
#define CMD_SOFTRESET 0xBA // Reinicia o sensor

#define STATUS_CALIBRATED 0x68 // Sensor calibrado
#define STATUS_BUSY 0x80       // Sensor ocupado

#define SOFT_RESET_MS 20 // Tempo de espera para reinicialização ou calibração

/**
 * @brief Envia um comando para o sensor AHT10.
 *
 * Esta função envia um comando de um byte para o sensor AHT10 usando o
 * protocolo I2C.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 * @param cmd O byte de comando a ser enviado para o sensor.
 * @return Retorna o resultado da operação de escrita I2C. PICO_ERROR_GENERIC
 * indica falha.
 */
int aht_send_command(aht_dev_t *dev, uint8_t cmd)
{
    return i2c_write_blocking(dev->i2c_port, dev->i2c_address, &cmd, 1, false);
}

/**
 * @brief Lê um comando do dispositivo AHT10 via I2C.
 *
 * Esta função realiza a leitura de um bloco de dados do dispositivo AHT10
 * utilizando a interface I2C.
 *
 * @param dev Ponteiro para a estrutura do dispositivo AHT10.
 * @param data Ponteiro para o buffer onde os dados lidos serão armazenados.
 * @param len Comprimento dos dados a serem lidos.
 * @return Retorna o resultado da operação de leitura. PICO_ERROR_GENERIC indica
 * falha.
 */
int aht_read_command(aht_dev_t *dev, uint8_t *data, uint8_t len)
{
    return i2c_read_blocking(dev->i2c_port, dev->i2c_address, data, len, false);
}

int aht_init(aht_dev_t *dev, i2c_inst_t *i2c_port, uint8_t i2c_address,
             uint8_t sda_pin, uint8_t scl_pin)
{
    dev->i2c_address = i2c_address;
    dev->sda_pin = sda_pin;
    dev->scl_pin = scl_pin;
    dev->i2c_port = i2c_port;
    dev->status = NOT_CALIBRATED;

    i2c_init(dev->i2c_port, 400 * 1000);

    gpio_set_function(dev->sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(dev->scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(dev->sda_pin);
    gpio_pull_up(dev->scl_pin);

    return aht_calibrate(dev);
}

int aht_calibrate(aht_dev_t *dev)
{
    if (!dev) {
        return PICO_ERROR_INVALID_ARG;
    }

    uint8_t cal_data;
    if (aht_send_command(dev, CMD_INIT) == PICO_ERROR_GENERIC) {
        return PICO_ERROR_IO;
    }
    sleep_ms(SOFT_RESET_MS);
    if (i2c_read_blocking(dev->i2c_port, dev->i2c_address, cal_data, 1,
                          false) == PICO_ERROR_GENERIC) {
        return PICO_ERROR_IO;
    }

    if (cal_data == STATUS_CALIBRATED) {
        dev->status = CALIBRATED;
    }
    return PICO_ERROR_NONE;
}

int aht_soft_reset(aht_dev_t *dev)
{
    if (!dev) {
        return PICO_ERROR_INVALID_ARG;
    }
    if (aht_send_command(dev, CMD_SOFTRESET) == PICO_ERROR_GENERIC) {
        return PICO_ERROR_IO;
    }
    sleep_ms(SOFT_RESET_MS);
    return aht_calibrate(dev);
}

int aht_read_data(aht_dev_t *dev, aht_data_t *data)
{
    if (!dev || !data) {
        return PICO_ERROR_INVALID_ARG;
    }

    if (dev->status == NOT_CALIBRATED) {
        if (aht_calibrate(dev) != PICO_ERROR_NONE) {
            return PICO_ERROR_INVALID_STATE;
        }
    }

    if (dev->status == BUSY) {
        return PICO_ERROR_RESOURCE_IN_USE;
    }

    if (aht_send_command(dev, CMD_TRIGGER) == PICO_ERROR_GENERIC) {
        return PICO_ERROR_IO;
    }

    uint8_t data_buf[6];
    if (aht_read_command(dev, data_buf, 6) == PICO_ERROR_GENERIC) {
        return PICO_ERROR_IO;
    }

    uint32_t raw = ((uint32_t)data_buf[1] << 12) |
                   ((uint32_t)data_buf[2] << 4) | ((uint32_t)data_buf[3] >> 4);

    data->humidity = (float)raw * 100 / (1 << 20);

    raw = ((uint32_t)(data_buf[3] & 0x0F) << 16) |
          ((uint32_t)data_buf[4] << 8) | data_buf[5];

    data->temperature = (float)raw * 200 / (1 << 20) - 50;

    return PICO_ERROR_NONE;
}