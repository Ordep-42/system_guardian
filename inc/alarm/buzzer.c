#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "buzzer.h"

void buzzer_init(uint8_t pin, uint frequency_hz) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency_hz * 4096));
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0);
}

void beep(uint8_t pin, uint duration_ms) {
    pwm_set_gpio_level(pin, 1);
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);
}