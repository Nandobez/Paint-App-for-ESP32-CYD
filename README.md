# Aplicativo de Desenho com Touchscreen

Este projeto implementa um aplicativo de desenho interativo usando ESP32 com display TFT e touchscreen. O usuário pode selecionar cores e desenhar na tela tocando diretamente no display.

## 📋 Características

- **Interface de seleção de cores**: 6 cores disponíveis (vermelho, amarelo, verde, ciano, azul, magenta)
- **Desenho livre**: Desenhe na tela tocando e arrastando o dedo
- **Feedback visual**: Borda branca indica a cor selecionada
- **Área de desenho protegida**: Previne desenho acidental na área de seleção de cores

## 🔧 Hardware Necessário

- **ESP32** (qualquer modelo compatível)
- **Display TFT 320x240** compatível com TFT_eSPI
- **Touchscreen XPT2046**
- **Conexões SPI** para comunicação

## 📡 Conexões do Touchscreen

| Pino Touchscreen | Pino ESP32 | Função |
|------------------|------------|---------|
| T_IRQ | GPIO 36 | Interrupção |
| T_DIN | GPIO 32 | MOSI |
| T_OUT | GPIO 39 | MISO |
| T_CLK | GPIO 25 | Clock |
| T_CS | GPIO 33 | Chip Select |

## 📚 Bibliotecas Necessárias

```cpp
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
```

### Instalação das Bibliotecas

1. **TFT_eSPI**: Disponível no Gerenciador de Bibliotecas do Arduino IDE
2. **XPT2046_Touchscreen**: Instale via Gerenciador de Bibliotecas

## ⚙️ Configuração

### Configuração do Display TFT_eSPI

Antes de compilar, configure o arquivo `User_Setup.h` da biblioteca TFT_eSPI com as especificações do seu display.

### Calibração do Touchscreen

O código inclui valores de calibração padrão:
```cpp
int x = map(p.x, 200, 3700, 0, SCREEN_WIDTH);
int y = map(p.y, 240, 3800, 0, SCREEN_HEIGHT);
```

**Nota**: Estes valores podem precisar de ajuste fino dependendo do seu hardware específico.

## 🎨 Como Usar

1. **Seleção de Cor**: Toque em uma das 6 caixas coloridas na parte superior da tela
2. **Desenho**: Toque e arraste na área abaixo das caixas de cor para desenhar
3. **Mudança de Cor**: Toque em uma nova cor para alterar a ferramenta de desenho

## 📐 Parâmetros Configuráveis

```cpp
#define SCREEN_WIDTH 320    // Largura da tela
#define SCREEN_HEIGHT 240   // Altura da tela
#define BOXSIZE 40          // Tamanho das caixas de cor
#define PENRADIUS 3         // Raio do pincel
```

## 🎯 Funcionalidades Detalhadas

### Seleção de Cores
- **6 cores predefinidas** organizadas horizontalmente
- **Indicador visual** com borda branca na cor selecionada
- **Restauração automática** da aparência das cores não selecionadas

### Sistema de Desenho
- **Pincel circular** com raio configurável
- **Proteção de área** impede desenho na zona de seleção de cores
- **Detecção contínua** de toque para desenho fluido

### Calibração e Mapeamento
- **Mapeamento de coordenadas** do touchscreen para pixels da tela
- **Filtragem de ruído** com delay anti-bounce
- **Detecção de toque** usando IRQ e polling

## 🔍 Debugging

Para ativar o debug das coordenadas do touchscreen, descomente a linha:
```cpp
// Serial.printf("x: %d | y: %d | z: %d\n", x, y, p.z);
```

## 🚀 Compilação e Upload

1. Certifique-se de que todas as bibliotecas estão instaladas
2. Configure o `User_Setup.h` da TFT_eSPI
3. Selecione a placa ESP32 correta
4. Compile e faça o upload do código

## 🔧 Solução de Problemas

### Touchscreen não responde
- Verifique as conexões dos pinos
- Confirme a configuração SPI
- Teste os valores de calibração

### Cores não aparecem corretamente
- Verifique a configuração do display no `User_Setup.h`
- Confirme a orientação da tela (`setRotation`)

### Desenho impreciso
- Ajuste os valores de mapeamento de coordenadas
- Calibre o touchscreen para seu hardware específico

## 📄 Licença

Este projeto é de código aberto e pode ser modificado e distribuído livremente.

## 🤝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para:
- Reportar bugs
- Sugerir melhorias
- Adicionar novas funcionalidades
- Melhorar a documentação
