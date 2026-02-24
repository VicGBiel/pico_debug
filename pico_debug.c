#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "lib/DHT22/dht.h"

// Pinos do LED RGB da BitDogLab
#define LED_G 11
#define LED_B 12
#define LED_R 13

// Pino do DHT22 conforme seu projeto original
#define DHT_PIN 28 

int main() {
    stdio_init_all();

    // Configura LEDs da BitDogLab
    gpio_init(LED_R); gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G); gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B); gpio_set_dir(LED_B, GPIO_OUT);

    sleep_ms(2000); 

    dht_t dht;
    float temperature = 0.0f;
    float humidity = 0.0f;

    // Inicializa o DHT22 usando a máquina de estado PIO0 e pull-up interno
    dht_init(&dht, DHT22, pio0, DHT_PIN, true);

    while (true) {
        dht_start_measurement(&dht);
        dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature);

        if (result == DHT_RESULT_OK) {
            printf("Sucesso - Temp: %.1f C | Umidade: %.1f %%\n", temperature, humidity);

            if (temperature > 30.0f) {
                gpio_put(LED_R, 1);
                gpio_put(LED_G, 0);
            } else {
                gpio_put(LED_R, 0);
                gpio_put(LED_G, 1);
            }
        } 
        else if (result == DHT_RESULT_TIMEOUT) {
            printf("Erro: Timeout. O sensor DHT22 nao respondeu no pino %d.\n", DHT_PIN);
            // Pisca azul para indicar erro de hardware
            gpio_put(LED_B, 1); sleep_ms(100); gpio_put(LED_B, 0);
        } 
        else if (result == DHT_RESULT_BAD_CHECKSUM) {
            printf("Erro: Falha na integridade dos dados (Checksum Invalido).\n");
        }

        sleep_ms(2000); 
    }
    
    return 0;
}