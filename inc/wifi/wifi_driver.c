#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "wifi_driver.h"

int wifi_driver_init() {
    return cyw43_arch_init();
}

void wifi_driver_deinit() {
    cyw43_arch_deinit();
}

void wifi_driver_poll() {
    cyw43_arch_poll();
}

int wifi_driver_connect(const char *ssid, const char *pass, uint32_t timeout_ms) {
    cyw43_arch_enable_sta_mode();
    return cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, timeout_ms);
}

uint8_t* wifi_driver_get_ip_address() {
    if (wifi_driver_is_connected()) {
        uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        return ip_address;
    }
    return NULL;
}

bool wifi_driver_is_connected() {
    if (wifi_driver_status() == CYW43_LINK_JOIN) {
        return true;
    }
    return false;
}

int wifi_driver_status() {
    return cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
}