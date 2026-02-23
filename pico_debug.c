#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Bibliotecas do sensor SCD41 (coloque a pasta lib/SCD41 no novo repo)
#include "lib/sensirion_common.h"
#include "lib/sensirion_i2c_hal.h"
#include "lib/scd4x_i2c.h"
#include "lib/sensirion_i2c.h"

// Pinos I2C
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1

// UART
#include "hardware/uart.h"
#define UART_TX_PIN 16
#define UART_RX_PIN 17
#define BAUD_RATE 115200

// Pinos do LED RGB da BitDogLab
#define LED_R 13
#define LED_G 11

int main() {
    stdio_init_all();
    stdio_uart_init_full(uart0, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);

    // Configura LED da BitDogLab
    gpio_init(LED_R); gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G); gpio_set_dir(LED_G, GPIO_OUT);

    // Configura I2C
    i2c_init(I2C_PORT, 400 * 1000); 
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa SCD41
    scd4x_wake_up();
    scd4x_stop_periodic_measurement();
    scd4x_reinit();
    scd4x_start_periodic_measurement();

    uint16_t co2 = 0;
    int32_t temp = 0;
    int32_t hum = 0;
    bool data_ready = false;

    while (true) {
        scd4x_get_data_ready_status(&data_ready);
        
        if (data_ready) {
            int16_t error = scd4x_read_measurement(&co2, &temp, &hum);
            
            if (error == 0) {
                printf("CO2: %u ppm, Temp: %.2f C\n", co2, temp / 1000.0f);
                
                // aciona LED se CO2 > 1000
                if (co2 > 1000) {
                    gpio_put(LED_R, 1);
                    gpio_put(LED_G, 0);
                } else {
                    gpio_put(LED_R, 0);
                    gpio_put(LED_G, 1);
                }
            }
        }
        sleep_ms(100);
    }
}