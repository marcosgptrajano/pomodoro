# 🍅 Temporizador Pomodoro com Raspberry Pi Pico

Um projeto de hardware interativo que implementa um **Temporizador Pomodoro** utilizando um **Raspberry Pi Pico**, um **Display TFT LCD (2.8" SPI)**, um **Joystick** para navegação e um **Buzzer** para alertas sonoros.

O sistema permite que o usuário configure o tempo de estudo, tempo de descanso e a quantidade de ciclos através de uma interface gráfica diretamente na tela.

---

## ✨ Funcionalidades

* **Configuração Personalizada:** Defina o tempo de foco (estudo), tempo de pausa e o número de ciclos desejados.
* **Interface Gráfica Interativa:** Menus de navegação amigáveis exibidos no display TFT.
* **Controle por Joystick:** Navegação pelos menus utilizando os eixos X/Y do joystick e seleção pelo botão integrado.
* **Transições e Alertas:** Telas de transição entre os estados (Foco/Pausa) com alertas sonoros via Buzzer.
* **Controle de Sessão:** Funções de **Pausar** e **Pular (Skip)** durante a contagem do tempo.

---

## 🛠️ Hardware Necessário

* 1x **Raspberry Pi Pico**
* 1x **Display TFT SPI 240x320** (2.8 polegadas)
* 1x **Módulo Joystick Analógico** (com botão no eixo Z)
* 1x **Buzzer**
* Protoboard e Jumpers para conexão

---

## 🔌 Esquema de Ligação (Pinagem)

Consulte o arquivo de imagem integrado **`Diagram.png`** para visualizar o circuito elétrico e as conexões recomendadas no Fritzing. 

**Resumo de Conexões Principais:**
* **Joystick - Eixo Y:** Conectado ao pino `GP26` (ADC0) do Pico.
* **Joystick - Eixo X:** Conectado ao pino `GP27` (ADC1) do Pico.
* **Joystick - Botão (SW):** Conectado ao pino `GP20` (Configurado como `INPUT_PULLUP`).
* **Buzzer:** Conectado ao pino `GP2`.
* **Display TFT:** Utiliza a interface SPI padrão configurada na biblioteca `TFT_eSPI`.

---

## 💻 Dependências e Software

O projeto foi desenvolvido em **C++** utilizando a infraestrutura do Arduino (compatível com a IDE do Arduino ou PlatformIO).

### Bibliotecas Utilizadas:
* `TFT_eSPI` (por Bodmer) - Responsável por toda a interface gráfica do display.
* `<vector>` (Biblioteca Padrão C++) - Utilizada para gerenciar o array de configurações de tempo na classe interna do Pomodoro.

---

## 🚀 Como Executar

1. **Configuração da IDE:** Certifique-se de instalar o pacote de placas do **Raspberry Pi Pico/RP2040** na sua Arduino IDE.
2. **Biblioteca TFT_eSPI:** 
   * Instale a biblioteca `TFT_eSPI` pelo Gerenciador de Bibliotecas.
   * Você precisará editar o arquivo `User_Setup.h` dentro da pasta da biblioteca para configurar os pinos SPI corretos e o driver correspondente ao seu display (geralmente ILI9341 para modelos 2.8").
3. **Download do Projeto:** Clone este repositório ou baixe os arquivos fonte (`.ino`, `Pomodoro.h`, `Pomodoro.cpp`).
4. **Upload:** Compile e faça o upload do código para o seu Raspberry Pi Pico.

---

## 📁 Estrutura do Projeto

* `Pomodoro.h`: Arquivo de cabeçalho definindo a classe `Pomodoro`, com a estrutura de controle de estados, gerenciamento de ciclos e temporizadores.
* `Pomodoro.cpp`: Implementação da lógica de tempo (cálculos de `millis()`), funções de pausar, pular e cálculo do tempo restante do ciclo.
* `main.ino` (ou equivalente principal): Controla a interface gráfica de usuário (UI), leitura analógica do Joystick e orquestração do display via `TFT_eSPI`.
* `Diagram.png`: Esquema visual de montagem do circuito.

---
*Projeto criado para auxiliar no foco e produtividade utilizando técnicas de hardware embarcado e design de interface em C++.*
README.md
Exibindo README.md.
