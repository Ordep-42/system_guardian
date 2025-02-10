# System Guardian: Monitoramento Inteligente para PCs e Servidores

Com o avanço da tecnologia e o aumento da demanda por computadores de alto desempenho, a necessidade de monitoramento eficiente se tornou essencial. System Guardian é um sistema de supervisão inteligente projetado para monitorar e controlar a temperatura, umidade e consumo energético de PCs residenciais e data centers.

Utilizando a placa BitDogLab, o projeto combina sensores e uma interface intuitiva para oferecer informações em tempo real sobre o estado dos dispositivos. O display OLED exibe os dados coletados pelo sensor AHT10 (temperatura e umidade) e por um potenciômetro (simulando consumo energético). Além disso, a matriz de LEDs RGB indica visualmente quais servidores ou PCs estão ativos, enquanto o joystick permite a navegação pelo menu do sistema.

Para maior conectividade, System Guardian envia os dados via MQTT para um dashboard na nuvem (como Adafruit IO ou Home Assistant), permitindo o monitoramento remoto dos dispositivos. Além disso, conta com alertas sonoros e visuais utilizando o buzzer e o LED RGB, que avisam sobre superaquecimento ou consumo elevado de energia.

O projeto também implementa um sistema de controle remoto, possibilitando ligar e desligar servidores ou PCs conforme necessário. Para garantir eficiência e confiabilidade, o firmware é desenvolvido com o FreeRTOS, garantindo execução multitarefa e resposta em tempo real.

System Guardian é uma solução inovadora, acessível e eficiente para garantir o funcionamento seguro e otimizado de qualquer ambiente computacional.

### O projeto System Guardian está sendo desenvolvido como projeto final do curso Embarcatech.
