#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/time.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

uint8_t seletor;
bool on_menu = true;
uint32_t ms_since_last_IRQ = 0;
uint8_t IRQ_delay = 70;

void IRQ_callback() {
    if ((uint32_t)(to_ms_since_boot(get_absolute_time()) - ms_since_last_IRQ) >= IRQ_delay) {
        on_menu = !on_menu;
        printf("IRQ!\n");
        ms_since_last_IRQ = to_ms_since_boot(get_absolute_time());
    }
}

void init_display() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void init_joystick() {
    adc_init();
    adc_gpio_init(26);
}

void display_menu(uint8_t* ssd, struct render_area* frame_area, uint8_t select) {
    char *menu[] = {
        " Temp e Umid  ",
        " Consumo Ener ",
        " LED RGB      "};

    int y = 0;
    char text[17];

    for (uint i = 0; i < count_of(menu); i++) {
        if (i == select) {
            strcpy(text, ">");
        } else {
            strcpy(text, " ");
        }
        strcat(text, menu[i]);
        ssd1306_draw_string(ssd, 5, y, text);
        y += 8;
    }
    render_on_display(ssd, frame_area);
}

void menu_task() {
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    uint8_t counter = 0;
    for (;;) {
        if (on_menu) {
            printf("Menu!\n");
            adc_select_input(0);
            uint16_t x = adc_read();

            if (x < 1365) {
                counter++;
            } else if (x > 4095 - 1365) {
                counter--;
            }

            seletor = counter % 3;

            display_menu(ssd, &frame_area, seletor);
        } else if (!on_menu) { 
            switch (seletor) {
                case 0:
                    // Visualizar temperatura e umidade
                    printf("Temperatura e umidade\n");
                    break;

                case 1:
                    // Visualizar consumo energético
                    printf("Consumo energético\n");
                    break;

                case 2:
                    // Sla
                    printf("Terceira opção\n");
                    break;
            }
        }
        sleep_ms(100);
    }
}

int main()
{
    stdio_init_all();
    
    init_joystick();
    init_display();
    ssd1306_init();

    gpio_init(22);
    gpio_set_dir(22, GPIO_IN);
    gpio_pull_up(22);
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_FALL, true, &IRQ_callback);

    menu_task();

    return 0;
}