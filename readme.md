# ApiSSense - Depuração de Hardware com Pi Pico

Este repositório contém a aplicação de testes e depuração de um dos sensores do projeto **ApiSSense**, desenvolvida como requisito para a tarefa "Desenvolvimento de sensores e atuadores IoT - Parte 9" do programa de Residência Tecnológica **Embarcatech**. O foco desta rotina é a validação do driver do sensor microclimático (DHT22) utilizando a máquina de estados (PIO) do Raspberry Pi Pico W, juntamente com a integração de periféricos nativos da placa **BitDogLab**.

## Objetivos Atendidos

* **Depuração em Tempo Real:** Uso de *Breakpoints*, *Step-Over* e *Watch Window* para inspecionar a conversão de dados puros gerados pela PIO.
* **Isolamento de Hardware:** Diagnóstico de falhas de lógica de hardware e validação elétrica da comunicação *One-Wire* do sensor.
* **Uso de Periféricos (BitDogLab):** Acionamento do LED nativo da placa com base nos *thresholds* de temperatura lidos pelo sensor externo.

## Arquitetura de Hardware e Conexões

O ambiente de depuração exige a conexão de três hardwares principais:

### 1. Raspberry Pi Pico W (Target) + BitDogLab
* **LED Verde (GP11):** Indica temperatura normal (<= 30°C).
* **LED Vermelho (GP13):** Indica anomalia/aquecimento (> 30°C).
* **LED Azul (GP12):** Indica falha de hardware (Timeout no pino de dados).

### 2. Sensor DHT22 (Microclima)
* **VCC:** 3.3V
* **GND:** GND
* **DATA:** Pino GP28 do RP2040

### 3. Pi Pico (Debugger)
As conexões entre a Pico Probe e a Pico W (Target) devem seguir:
* **GND -> GND**
* **GP2 -> SWCLK**
* **GP3 -> SWDIO**
* **GP4 -> GP0** (Target RX)
* **GP5 -> GP1** (Target TX)

## Como Depurar

1. Conecte a Pi Pico à porta USB do seu computador.
    1.1. Com a Pi Pico no modo bootsel, carregue-a com o _debugprobe_on_pico.uf2_.
2. Certifique-se de que a placa Target (Pico W) também está alimentada.
3. No VS Code, abra o arquivo `pico_debug.c`.
4. Adicione um **Breakpoint** na linha da função de bloqueio da PIO:
    `dht_result_t result = dht_finish_measurement_blocking(...);`
5. Pressione **F5** para iniciar o GDB e o OpenOCD. A execução irá parar na função `main()`.
6. Pressione **F5** novamente para soltar a execução. O sistema irá parar no Breakpoint configurado.
7. Na aba **Watch Window**, observe a variáveis `temperature` e `humidity`.
8. Pressione **F10** (*Step-Over*) e observe a atualização das variáveis em tempo real com os dados convertidos do sensor.
