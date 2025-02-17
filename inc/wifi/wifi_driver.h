#pragma once

int wifi_driver_init();
void wifi_driver_deinit();
void wifi_driver_poll();
int wifi_driver_connect(const char *ssid, const char *pass, uint32_t timeout_ms);
uint8_t* wifi_driver_get_ip_address();
bool wifi_driver_is_connected();
int wifi_driver_status();
void wifi_driver_lwip_begin();
void wifi_driver_lwip_end();