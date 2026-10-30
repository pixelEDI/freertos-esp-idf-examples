# 04 – FreeRTOS-Task-Notifications

**Lernziel:** Ein Task wartet energiesparend auf ein Ereignis und wird von einem zweiten Task gezielt aufgeweckt.

- `xTaskCreate()` erzeugt den Ereignis- und den Worker-Task.
- `xTaskNotifyGive()` sendet eine einfache Benachrichtigung an einen Task.
- `ulTaskNotifyTake()` wartet blockierend, bis diese Benachrichtigung eintrifft.

```bash
idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
```

Beispiel:

```text
Ereignis erkannt - Worker wird benachrichtigt
Ereignis empfangen - Arbeit wird ausgeführt
```

Der Ereignis-Task simuliert einen Sensor oder eine Netzwerkverbindung. Ändere die zwei Wartezeiten und beobachte, wann der Worker geweckt wird.

## Funktionsablauf

```mermaid
flowchart LR
    E[Ereignis-Task, alle 2 s] -->|xTaskNotifyGive| N[Task-Notification]
    N -->|ulTaskNotifyTake| W[Worker-Task wird aktiv]
    W --> A[Arbeit ausführen]
    W -->|danach wieder warten| N
```

