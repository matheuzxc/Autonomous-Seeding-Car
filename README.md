# Autonomous-Seeding-Car

Este projeto visa o desenvolvimento de um veículo remotamente controlado com controle de velocidade variável e navegação autônoma até coordenadas pré-definidas. A funcionalidade adicional será a simulação de uma semeadora automatizada, abordando desafios de sincronização mecânica-eletrônica e mapeamento georreferenciado.

## Metodologia

A metodologia adotada para o desenvolvimento do **Autonomous-Seeding-Car** foca na criação de um sistema autônomo e preciso, que integra controle de navegação, movimentação e semeadura em um veículo de baixo custo. A estrutura metodológica do projeto é composta pelas seguintes etapas principais:

### 1. **Navegação Autônoma**

A navegação do carrinho é baseada em coordenadas geográficas. O veículo utiliza um sistema de GPS para determinar sua posição e calcular a direção necessária para alcançar um destino pré-definido. A direção do carrinho é continuamente corrigida utilizando uma bússola digital, que fornece a orientação do veículo em relação ao norte magnético.

Além disso, o movimento é controlado dinamicamente com base em um sistema de controle, que ajusta a velocidade e a direção das rodas para garantir que o carrinho siga a trajetória desejada. A navegação é baseada na conversão das coordenadas geográficas em distâncias e ângulos de deslocamento, minimizando erros ao longo do caminho.

### 2. **Controle de Velocidade e Deslocamento**

O sistema de controle utiliza um controlador proporcional-integral-derivativo (PID) para ajustar a velocidade e direção do carrinho, de forma a evitar oscilações e garantir uma movimentação suave e precisa. O PID ajuda a manter o carrinho na trajetória correta, mesmo em condições variáveis ou imprecisas de movimentação, resultando em uma navegação mais estável e controlada.

### 3. **Execução da Semeadura**

Quando o carrinho chega ao ponto de destino, o processo de semeadura é automaticamente acionado. O carrinho se move em um padrão sistemático, alternando entre deslocamentos lineares e laterais para cobrir a área predeterminada para semeadura. Durante esses movimentos, o sistema de dispersão libera as sementes de maneira uniforme, assegurando que a operação de semeadura seja realizada de forma eficiente e precisa.

### 4. **Integração Mecânica e Eletrônica**

O projeto envolve desafios significativos de sincronização entre a mecânica e a eletrônica, especialmente na operação do sistema de semeadura e controle de movimentação. O ajuste contínuo de posição e direção, bem como o controle preciso do sistema de semeadura, são feitos de forma coordenada para garantir que as sementes sejam liberadas no momento e local corretos.

### 5. **Mapeamento Georreferenciado**

A navegação do carrinho é suportada por um mapeamento georreferenciado, que permite ao veículo seguir coordenadas pré-definidas, assegurando a cobertura adequada da área. A utilização de dados geoespaciais ajuda a garantir que o carrinho execute a semeadura de forma precisa, mapeando de forma eficiente os locais onde as sementes devem ser dispersas.

---

## Arcadia e Capella

Para o desenvolvimento do projeto, foi utilizada a **metodologia Arcadia** juntamente com a ferramenta **Capella**, ambas voltadas para a modelagem de sistemas complexos.

### Arcadia

**Arcadia** (Architecture Analysis & Design Integrated Approach) é uma metodologia estruturada para a análise e o design de sistemas complexos. Ela permite modelar, definir e validar os requisitos, projetar a arquitetura do sistema e garantir que todos os elementos funcionem de forma coerente e integrada.

A metodologia Arcadia segue um fluxo de camadas, cada uma abordando um aspecto específico do sistema:

1. **Operational Analysis (OA)**: Define as necessidades dos usuários e as operações gerais do sistema.
2. **System Analysis (SA)**: Especifica o que o sistema deve fazer, sem entrar nos detalhes de implementação.
3. **Logical Architecture (LA)**: Estrutura o sistema em componentes lógicos, definindo suas interações.
4. **Physical Architecture (PA)**: Foca na implementação real, especificando o hardware, software e interfaces.

Para o **Autonomous-Seeding-Car**, foi adotada a **camada de Arquitetura Física**, dado o prazo de desenvolvimento ágil e a necessidade de implementação prática dentro de um tempo limitado. Esta camada descreve todos os componentes físicos e suas interações no sistema, garantindo que a arquitetura final seja viável e eficiente.

### Capella

**Capella** é a ferramenta de modelagem baseada na metodologia Arcadia. Ela permite criar diagramas, definir requisitos, especificar as interações entre os módulos e gerar a arquitetura do sistema. Capella proporciona uma visão clara e estruturada de como o sistema será implementado, facilitando a análise e o design, além de garantir a consistência entre os diferentes componentes.

Com Capella, a arquitetura física do **Autonomous-Seeding-Car** foi modelada e validada, permitindo o desenvolvimento e implementação eficiente de todos os módulos do sistema, desde a navegação até a semeadura automatizada.

---

## Diagramas do Sistema

Abaixo estão os diagramas explicativos que foram usados para modelar a arquitetura do sistema no **Capella**.

### Bloco de Componente na Arquitetura Física

Este diagrama mostra os principais blocos de componentes na arquitetura física do **Autonomous-Seeding-Car**, representando os módulos de hardware e suas interações.

![Bloco de Componente na Arquitetura Física](images/ex_capella.png)

### Arquitetura Final

O diagrama abaixo mostra a arquitetura final do sistema, com os componentes integrados e suas conexões, tanto físicas quanto lógicas. Ele ilustra como os diferentes módulos interagem para formar o sistema completo.

![Arquitetura Final do Sistema](images/diagrama_capella.png)

---

Com essa abordagem metodológica e a utilização das ferramentas Arcadia e Capella, o projeto **Autonomous-Seeding-Car** é desenvolvido de forma organizada e eficaz, garantindo que todos os componentes funcionem de maneira integrada e otimizando o processo de navegação e semeadura do veículo.
