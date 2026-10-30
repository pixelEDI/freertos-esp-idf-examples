#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "queues";
static QueueHandle_t number_queue;

static void sender_task(void *arg)
{
    int number = 0;
    while (true) {
        number++;
        // Send wartet höchstens 100 ms, statt den Task endlos zu blockieren.
        if (xQueueSend(number_queue, &number, pdMS_TO_TICKS(100)) == pdPASS) {
            ESP_LOGI(TAG, "gesendet: %d, Queue: %u/5", number,
                     (unsigned)uxQueueMessagesWaiting(number_queue));
        } else {
            ESP_LOGI(TAG, "Queue voll - Zahl %d verworfen", number);
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Sender: eine Zahl pro Sekunde
    }
}

static void receiver_task(void *arg)
{
    int number;
    while (true) {
        // Receive wartet bis zu zwei Sekunden auf den nächsten Wert.
        if (xQueueReceive(number_queue, &number, pdMS_TO_TICKS(2000)) == pdPASS) {
            ESP_LOGI(TAG, "empfangen: %d, Queue: %u/5", number,
                     (unsigned)uxQueueMessagesWaiting(number_queue));
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // Empfänger verarbeitet nur alle zwei Sekunden
    }
}

void app_main(void)
{
    number_queue = xQueueCreate(5, sizeof(int)); // höchstens fünf Zahlen puffern
    if (number_queue == NULL) {
        ESP_LOGE(TAG, "Queue konnte nicht erstellt werden");
        return;
    }
    xTaskCreate(sender_task, "sender", 2048, NULL, 1, NULL);
    xTaskCreate(receiver_task, "receiver", 2048, NULL, 1, NULL);
}
