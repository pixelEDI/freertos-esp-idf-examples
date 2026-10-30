# FreeRTOS mit ESP-IDF auf dem Seeed Studio XIAO ESP32-C6

Dieses Projekt zeigt grundlegende FreeRTOS-Konzepte mit kurzen, eigenständigen Beispielen für den Seeed Studio XIAO ESP32-C6.

Die vier Lernprojekte sind in C für ESP-IDF 5.x/6.x umgesetzt. Jedes Verzeichnis ist ein separates ESP-IDF-Projekt und benötigt keine zusätzliche Hardware.

## Start

In das gewünschte Verzeichnis wechseln und ausführen:

```bash
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```

Die serielle Ausgabe erfolgt mit `ESP_LOGI()`. Die Portangabe `/dev/ttyACM0` bei Bedarf anpassen.

## Projekte

1. `01_queues` – Datenübergabe mit Queue
2. `02_suspend_resume` – Task pausieren und fortsetzen
3. `03_priorities` – Prioritäten auf einem CPU-Kern
4. `04_task-notification` – Task-Notifications für Ereignisse

Jede README enthält Lernziel, die drei wichtigsten Funktionen, erwartete Ausgabe und einen Ablauf für ein Video bis drei Minuten.

Weitere Tutorials und Kurse gibt es auf dem [YouTube-Kanal @pixeledi](https://www.youtube.com/@pixeledi) sowie in der [PixelEDI Akademie](https://pixeledi.eu/akademie).

Weitere Projekte findest du auf [pixeledi.eu](https://pixeledi.eu).
