#include <stdio.h>
#include "pico/stdlib.h"
#include "matrizRGB.h"
#include "desenho.h"

// Configuração dos pinos

const uint LED_RED_PIN = 13; // Green = 11, Blue = 12 and Red = 13

const uint BUTTON1_PIN = 5; // Define o botão 1 como pino 5
const uint BUTTON2_PIN = 6; // Define o botão 2 como pino 6

const int num = 0; // Variável global para definir qual número selecionar na matriz

int main()
{
    // Inicialização dos pinos
    stdio_init_all();

    gpio_init(LED_RED_PIN);
    gpio_init(BUTTON1_PIN);
    gpio_init(BUTTON2_PIN);

    // Inicializa os pinos da matriz de Leds no pino 7

    npInit(7);

    // Confira direção dos pinos (Entrada ou saída)

    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON1_PIN, GPIO_IN);
    gpio_set_dir(BUTTON2_PIN, GPIO_IN);

    /* Configuração para habilitar o pull up interno para os botões, evitando o uso de resistores externos e
    garantindo que o pino esteja em nível alto quando o botão não estiver pressionado. */

    gpio_pull_up(BUTTON1_PIN);
    gpio_pull_up(BUTTON2_PIN);

    // Escreve o número inicial a ser exibido na matriz de Leds, neste caso o número 0.

    setMatrizDeLEDSComIntensidade(caixa_de_desenhos[num], 1, 1, 1);

    while (true)
    {

        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
