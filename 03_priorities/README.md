# 03 – Task-Prioritäten

**Lernziel:** Auf dem einkernigen ESP32-C6 erhält der bereite Task mit höherer Priorität bevorzugt CPU-Zeit.

- `xTaskCreate()` startet beide Rechen-Tasks.
- Die Prioritätswerte `HIGH_PRIORITY` und `LOW_PRIORITY` steuern die Auswahl.
- `vTaskDelay(1)` gibt die CPU freiwillig ab und verhindert den Watchdog.

```bash
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```

Beispiel: `HOCH: 10 Rechenblöcke` und `NIEDRIG: 10 Rechenblöcke`; die Mengen zeigen die Scheduler-Verteilung, nicht eine exakte Zeitmessung.

Ändere `HIGH_PRIORITY` und `LOW_PRIORITY`. Entferne `vTaskDelay(1)` nicht dauerhaft: Der Watchdog könnte auslösen.

## Funktionsablauf

```mermaid
flowchart TD
    A[HOCH, Priorität 5, Rechen-Task] --> D{Scheduler, ein CPU-Kern}
    B[NIEDRIG, Priorität 2, Rechen-Task] --> D
    D -->|höhere Priorität bevorzugt| A
    D -->|nach freiwilligem Yield| B
    A --> Y[vTaskDelay(1)]
    B --> Y
```

