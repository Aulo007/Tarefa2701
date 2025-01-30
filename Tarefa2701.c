#include <stdio.h>
#include "pico/stdlib.h"

// Configuração dos pinos

const uint LED_BLUE_PIN = 11;
const uint LED_GREEN_PIN = 12;
const uint LED_RED_PIN = 13;

const uint BUTTON1_PIN = 5;
const uint BUTTON2_PIN = 6;


int main()
{
    stdio_init_all();

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
