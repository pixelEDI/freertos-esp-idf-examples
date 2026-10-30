#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "notify";
static TaskHandle_t worker_handle;

static void worker_task(void *arg)
{
    while (true) {
        // Der Task schläft, bis ein Ereignis für ihn eintrifft.
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        ESP_LOGI(TAG, "Ereignis empfangen - Arbeit wird ausgeführt");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void event_task(void *arg)
{
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(2000)); // simuliert Sensor- oder Netzwerkereignis
        ESP_LOGI(TAG, "Ereignis erkannt - Worker wird benachrichtigt");
        // Task-Notification weckt genau den gewünschten Task auf.
        xTaskNotifyGive(worker_handle);
    }
}

void app_main(void)
{
    xTaskCreate(worker_task, "worker", 2048, NULL, 1, &worker_handle);
    xTaskCreate(event_task, "event", 2048, NULL, 1, NULL);
}
