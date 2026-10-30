#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "suspend";
static TaskHandle_t pausable_handle;

static void pausable_task(void *arg)
{
    while (true) {
        ESP_LOGI(TAG, "Pausierbarer Task läuft");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void steady_task(void *arg)
{
    while (true) {
        ESP_LOGI(TAG, "Zweiter Task läuft weiter");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void controller_task(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "pausable_task wird pausiert");
        vTaskSuspend(pausable_handle); // Task bleibt erhalten, führt aber nichts aus.
        vTaskDelay(pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "pausable_task wird fortgesetzt");
        vTaskResume(pausable_handle); // normaler Task setzt an seiner Stelle fort.
    }
}

void app_main(void)
{
    xTaskCreate(pausable_task, "pausable", 2048, NULL, 1, &pausable_handle);
    xTaskCreate(steady_task, "steady", 2048, NULL, 1, NULL);
    xTaskCreate(controller_task, "controller", 2048, NULL, 2, NULL);
}
