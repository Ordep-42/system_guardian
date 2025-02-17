# System Guardian: Monitoramento Inteligente para PCs e Servidores

O System Guardian é uma solução de monitoramento para computadores pessoais e data centers, focada no acompanhamento contínuo da temperatura, umidade e consumo de energia. Com alertas visuais e sonoros, além de integração com a nuvem via MQTT e a plataforma Adafruit IO, o projeto proporciona uma abordagem acessível e eficiente para a manutenção preventiva e otimização de recursos.

### Recursos Utilizados

* LED RGB para indicações visuais.

* Buzzer para alarmes sonoros.

* Botão para desativação do alarme.

* Sensor AHT10 (I2C) para temperatura e umidade.

* Potenciômetro para simular consumo energético.

* Wi-Fi do RP2040 para comunicação via MQTT com Adafruit IO.

### Funcionalidades

* Monitoramento de temperatura, umidade e consumo de energia.

* Alertas visuais com cores no LED RGB.

* Alarmes sonoros ativados pelo buzzer em situações críticas.

* Botão para silenciar alarmes.

* Envio contínuo de dados para a nuvem com dashboards interativos no Adafruit IO.

### O projeto System Guardian está sendo desenvolvido como projeto final do curso Embarcatech.

## Para executar o projeto, crie um arquivo secrets.h baseado no arquivo de exemplo secrets.example.h presente na pasta raíz do repositório.