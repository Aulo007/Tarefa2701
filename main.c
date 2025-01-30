#include <stdio.h>
#include "pico/stdlib.h"
#include "matrizRGB.h"
#include "desenho.h"

// Configuração dos pinos

const uint LED_RED_PIN = 13; // Green = 11, Blue = 12 and Red = 13

const uint BUTTON1_PIN = 5; // Define o botão 1 como pino 5
const uint BUTTON2_PIN = 6; // Define o botão 2 como pino 6

volatile int num; // Variável global para definir qual número selecionar na matriz

static void gpio_irq_handle(uint gpio, uint32_t events);

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

    num = 5; // inicializa o valor da variável volátil como 5

    // Escreve o primeiro número inicial na matriz de leds 5x5, neste caso o 5.
    setMatrizDeLEDSComIntensidade(caixa_de_desenhos[num], 0.1, 0.1, 0.1);

    // Configuração da interrupção com o callback
    gpio_set_irq_enabled_with_callback(BUTTON1_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);
    gpio_set_irq_enabled_with_callback(BUTTON2_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);

    // Loop principal

    while (true)
    {

        gpio_put(LED_RED_PIN, true);
        sleep_ms(200);
        gpio_put(LED_RED_PIN, false);
        sleep_ms(200);

        printf("Botão 1: %d \n", gpio_get(LED_RED_PIN));
    }
}

static void gpio_irq_handle(uint gpio, uint32_t events)
{
    if (num >= 0 && num <= 9)
    {
        if (gpio == BUTTON1_PIN)
        {
            /* Ternário (Condição ? valor se verdadeiro: valor se falso), atribui valor a variável volátil num
               Se o número for menor que 9 ele incrementa o num em 1, se não, faz o valor permanecer em 9 */

            num = (num < 9) ? num + 1 : 9;
        }
        else if (gpio == BUTTON2_PIN)
        {
            /* Ternário (Condição ? valor se verdadeiro: valor se falso), atribui valor a variável volátil num
              Se o número for maior que 0 ele decrementa o num em 1, se não, faz o valor permanecer em 0 */
            num = (num > 0) ? num - 1 : 0;
        }

        setMatrizDeLEDSComIntensidade(caixa_de_desenhos[num], 0.1, 0.1, 0.1);
    }
}
