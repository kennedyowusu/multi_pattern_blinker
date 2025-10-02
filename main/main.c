#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_controller.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Multi-Pattern LED Blinker");

    // Configure LED controller
    led_config_t led_config = {
        .gpio_num = GPIO_NUM_2,      // Built-in LED on most ESP32 boards
        .active_high = true          // LED turns on when GPIO is HIGH
    };

    // Initialize LED controller
    esp_err_t ret = led_init(&led_config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize LED controller");
        return;
    }

    ESP_LOGI(TAG, "LED controller initialized successfully");
    ESP_LOGI(TAG, "Cycling through patterns...");

    // Cycle through all patterns
    while (1) {
        ESP_LOGI(TAG, "Pattern: OFF");
        led_set_pattern(LED_PATTERN_OFF);
        vTaskDelay(pdMS_TO_TICKS(3000));

        ESP_LOGI(TAG, "Pattern: ON");
        led_set_pattern(LED_PATTERN_ON);
        vTaskDelay(pdMS_TO_TICKS(3000));

        ESP_LOGI(TAG, "Pattern: BLINK_SLOW");
        led_set_pattern(LED_PATTERN_BLINK_SLOW);
        vTaskDelay(pdMS_TO_TICKS(5000));

        ESP_LOGI(TAG, "Pattern: BLINK_FAST");
        led_set_pattern(LED_PATTERN_BLINK_FAST);
        vTaskDelay(pdMS_TO_TICKS(5000));

        ESP_LOGI(TAG, "Pattern: PULSE");
        led_set_pattern(LED_PATTERN_PULSE);
        vTaskDelay(pdMS_TO_TICKS(5000));

        ESP_LOGI(TAG, "Pattern: SOS");
        led_set_pattern(LED_PATTERN_SOS);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
