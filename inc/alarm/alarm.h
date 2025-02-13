#pragma once

#define ALARM_BUZZER_PIN 21
#define ALARM_BUTTON_PIN 5

void alarm_init();
void alarm_arm();
void alarm_trigger(bool red_state, bool green_state, bool blue_state, uint duration_ms);
void alarm_disable();