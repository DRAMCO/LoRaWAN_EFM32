# LoRaWAN_EFM32
LoRaMAC implementation based on the SEMTECH implemenation for the EFM32 Happy Gecko develop board.
Developed by [DRAMCO](http://www.dramco.be).
More information soon.



## TODO LoRa EFM32## 

Question mark behind the name means it&#39;s just a suggestion, but feel free to already get started.

| Description | Who | Files | Status |
| --- | --- | --- | --- |
| Remove unnecessary functionality: uart, usb uart, serial, gps (if possible remove files) | @GeoffreyOttoy | boards/uart-board.c<br>boards/uart-board.h<br>boards/uart-usb-board.c<br>boards/uart-usb-board.h<br>boards/uart-gps.c<br>boards/uart-gps.c<br>system/gps.c<br>system/gps.h<br>system/uart.c<br>system/uart.h<br>system/serial.c<br>ystem/serial.h | |
| Check AES HW problem (OTAA) | @GeoffreyOttoy ? | system/crypto/aes.c | |
| Add EEPROM functionality | Jonas? | boards/eeprom-board.c | |
| Add i2c functionality | Jonas | boards/i2c-board.c | |
| Add ADC functionality | Jonas? | boards/adc-board.c | |
| Add battery level reading | Jonas? |   | |
| Add i2c sensor functionality |   | _New files:_ | |
| Wonder Gecko: temperature &amp; humidity(Interrupt possible?) | Jonas? | system/humitemp.csystem/humitemp.h | |
| Expansion board: light(Don&#39;t forget interrupt!) | Jonas? | system/light.csystem/light.h | |
| LoRa payload formatting (PORT will define the sensor type) | Team? | src/main.cPrepareTxFrameFrame(…) | |
| Check license to be used | [Gilles](https://github.com/GillesC) |   | done |
| Format source files (comments to include license) | Team? | Check all files | |
| Write example applications + walkthrough (workshop) | Team |   | |

Feel free to expand on this list.


