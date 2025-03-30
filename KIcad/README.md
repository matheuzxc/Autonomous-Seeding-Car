# PCB do Sistema Eletrônico - **Autonomous-Seeding-Car**

Este repositório contém as PCBs (Placas de Circuito Impresso) que compõem os módulos eletrônicos do projeto **Autonomous-Seeding-Car**. O sistema eletrônico é composto por três PCBs empilhadas verticalmente, cada uma responsável por um conjunto específico de funções dentro do sistema. As PCBs foram projetadas no **KiCad**, com o objetivo de criar um design eficiente e compactado, garantindo a integração correta dos módulos eletrônicos.

## Estrutura das PCBs

A estrutura do sistema é organizada em três PCBs interconectadas, uma em cima da outra, de forma a otimizar o uso de espaço e a organização dos componentes. Cada PCB desempenha um papel crucial no funcionamento geral do carrinho autônomo. As PCBs são distribuídas conforme descrito abaixo:

### PCB 1: Módulo Regulador de Tensão e Ponte H

A primeira PCB contém os seguintes módulos eletrônicos:

- **Módulo Regulador de Tensão (LM2596)**: Responsável por fornecer a tensão estável necessária para os outros módulos do sistema, garantindo que os componentes eletrônicos operem de forma segura e eficiente.
- **Ponte H Dupla (L298N)**: Controla os motores do veículo, regulando a direção e velocidade com base nos comandos enviados pelo ESP32. Este módulo é essencial para o controle de movimentação do carrinho.

![PCB 1 - Módulo Regulador de Tensão e Ponte H](imagens/pcb1.jpg)

### PCB 2: ESP32 e Módulo Bluetooth

A segunda PCB contém os seguintes componentes:

- **ESP32 WROOM**: O microcontrolador central do sistema, que coordena a comunicação entre os diferentes módulos e processa os comandos para controle de movimento e semeadura.
- **Módulo Bluetooth HC-05**: Responsável pela comunicação sem fio com o controle remoto, permitindo que o carrinho seja operado remotamente. Recebe comandos de movimentação e transmite-os ao ESP32 para execução.

![PCB 2 - ESP32 e Módulo Bluetooth](imagens/pcb2.jpg)

### PCB 3: Módulo GPS

A terceira PCB contém o **Módulo GPS NEO-6M**, responsável por fornecer a localização geográfica do carrinho. Ele permite que o veículo se desloque até coordenadas pré-definidas com precisão, essencial para a navegação autônoma.

![PCB 3 - Módulo GPS](imagens/pcb3.jpg)

### Montagem Final das 3 PCBs

As 3 PCBs foram projetadas para serem empilhadas verticalmente, com uma em cima da outra. A disposição otimiza o uso do espaço e facilita a integração dos módulos. Abaixo, está a foto da montagem final das 3 PCBs conectadas.

![Montagem Final - As 3 PCBs Empilhadas](imagens/pcb_final.jpg)

### Posicionamento da Bússola

A **bússola (HMC5883L)** está posicionada na frente do carro, fora da pilha de PCBs. Ela é responsável por fornecer a direção do carrinho em relação ao norte magnético, permitindo que o sistema ajuste a orientação de forma precisa.

---

## Pinos de Conexão no ESP32

Abaixo estão os pinos utilizados para cada módulo no ESP32:

| **Módulo**           | **Pinos no ESP32**                               |
|----------------------|--------------------------------------------------|
| **GPS (NEO-6M)**      | RX2 → GPIO 16, TX2 → GPIO 17                    |
| **Bússola/IMU**       | SDA → GPIO 21, SCL → GPIO 22                    |
| **Ponte H (Motores)** | IN1 → GPIO 25, IN2 → GPIO 26, IN3 → GPIO 27, IN4 → GPIO 14, PWM A → GPIO 32, PWM B → GPIO 33 |
| **Bluetooth (HC-05)** | RX1 → GPIO 4, TX1 → GPIO 2                      |
| **Servo Motor**       | Sinal → GPIO 13                                 |

---

## Design no KiCad

Todas as PCBs foram projetadas no **KiCad**, uma ferramenta open-source poderosa para o design de circuitos eletrônicos e PCBs. O design foi otimizado para garantir um layout compacto, com o mínimo de interferências entre os componentes e com uma conexão eficiente entre as diferentes placas.

---

## Instruções de Fabricação

Para fabricar as PCBs, exporte os arquivos gerados pelo KiCad, incluindo os arquivos de camadas, furos e serigrafia. Em seguida, envie esses arquivos para uma empresa de fabricação de PCBs ou produza-as internamente, caso tenha a infraestrutura necessária.

---

## Contribuições

Contribuições para este projeto são bem-vindas! Caso deseje sugerir melhorias no design ou no código, fique à vontade para abrir um **pull request**.

---

## Licença

Este projeto está licenciado sob a licença **MIT**. Consulte o arquivo LICENSE para mais detalhes.

