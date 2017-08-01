# LoRaWAN_EFM32
LoRaMAC implementation based on the SEMTECH implemenation for the EFM32 Happy Gecko develop board.
Developed by [DRAMCO](http://www.dramco.be).
More information soon.

## Reducing power consumption of IoT nodes: a hands-on
This project will be used in hands-on sessions to let attendees experience the development of low power IoT nodes.
### More information about these sessions
In this hands-on session the attendees will experience the development of a wireless sensor node. More
specifically, how low-power operation can be achieved by clever utilization of the available resources.
Such design choices include: selecting the right wireless technology, duty-cycled operation, hardware
acceleration, etc.
The participants will experiment with a custom LoRa-based sensor, built with a Semtec SX1272 Radio
chip and an EFM32 Cortex M0 processor. The way operations are being performed on the node can be
customized in the Silabs Simplicity Studio IDE. The effect of these changes on the energy consumption
can be observed through the IDE’s built-in energy profiler.
In the end, the lecturers will have shown that the design of true low-power wireless sensors requires a
thoughtful design. Both software and hardware need to work seamlessly together within the boundaries
of a specific application.

## TODO

Question mark behind the name means it&#39;s just a suggestion, but feel free to already get started.

| Description | Who | Files | Status |
| --- | --- | --- | --- |
| Remove unnecessary functionality:<br>uart, usb uart, serial, gps (if possible remove files) | [Geoffrey](https://github.com/geoffreyottoy) | `boards/uart-board.c`<br>`boards/uart-board.h`<br>`boards/uart-usb-board.c`<br>`boards/uart-usb-board.h`<br>`boards/uart-gps.c`<br>`boards/uart-gps.c`<br>`system/gps.c`<br>`system/gps.h`<br>`system/uart.c`<br>`system/uart.h`<br>`system/serial.c`<br>`system/serial.h`| |
| Check AES HW problem (OTAA) | [Geoffrey](https://github.com/geoffreyottoy) ? | `system/crypto/aes.c` | |
| Add EEPROM functionality | Jonas? | `boards/eeprom-board.c` | |
| Add i2c functionality | Jonas | `boards/i2c-board.c` | |
| Add ADC functionality | Jonas? | `boards/adc-board.c` | |
| Add battery level reading | Jonas? | `boards/board.c` in `BoardGetBatteryLevel()`  | |
| Add i2c sensor functionality |   | _New files:_ | |
| Happy Gecko: temperature &amp; humidity <br>(Interrupt possible?) | Jonas? | `system/humitemp.c`<br>`system/humitemp.h` | |
| * Expansion board: light <br>(Don&#39;t forget interrupt!) | Jonas? | `system/light.c`<br>`system/light.h` | |
| * LoRa payload formatting (PORT will define the sensor type) | Team? | `src/main.c`<br>`PrepareTxFrame(…)` | |
| Check license to be used | [Gilles](https://github.com/GillesC) |   | done |
| * Format source files <br>(comments to include license) | Team? | Check all files | |
| Write example applications + walkthrough (workshop) | Team |   | |

Feel free to expand on this list.


