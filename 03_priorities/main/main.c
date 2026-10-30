#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HIGH_PRIORITY 5 // Auf dem ESP32-C6 teilen sich beide Tasks einen Kern.
#define LOW_PRIORITY 2
static const char *TAG = "priorities";

static void cpu_task(void *arg) {
  const char *name = (const char *)arg;
  unsigned long count = 0;
  while (true) {
    for (volatile int i = 0; i < 100000; i++) {
    }
    count++;
    if ((count % 10) == 0) {
      ESP_LOGI(TAG, "%s: %lu Rechenblöcke", name, count);
      vTaskDelay(1);
    }
  }
}

void app_main(void) {
  xTaskCreate(cpu_task, "high", 2048, "HOCH", HIGH_PRIORITY, NULL);
  xTaskCreate(cpu_task, "low", 2048, "NIEDRIG", LOW_PRIORITY, NULL);
}
