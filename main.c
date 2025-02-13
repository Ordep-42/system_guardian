#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/aht10/aht.h"

void termo_task(void *pvParameters)
{
    aht_dev_t aht;
    aht_init(&aht, i2c0, AHT10_ADDRESS, 16, 17);

    aht_data_t data;
    for (;;) {
        if (aht_read_data(&aht, &data) == PICO_ERROR_NONE) {
            printf("Temperature: %.2f C\n", data.temperature);
            printf("Humidity: %.2f %%\n", data.humidity);
        }
        sleep_ms(1000);
    }
}

int main()
{
    stdio_init_all();

    termo_task(NULL);
}
