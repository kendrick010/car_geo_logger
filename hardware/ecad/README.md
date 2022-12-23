# Car Geo-Logger PCB

**September 2022:** First v1 board designed with a horizantal mounted USB-C connector and 0603 (imperial) sized passives. Currently waiting for assembly and testing. The v1 board is a experimental prototype, some expected patch notes for next version, 

- Pure SMD components, standardize to 0603 (imperial)
- Vertical mounted USB-C connector
- SD-Card socket erratically had a layer for milling on Altium, change library and part
- Less beefier backup battery, change library and battery (current LR44)

The ideal board is a minimal ESP32 module embedded with a USB to UART bridge, GPS chip, and SD storage.

**October 2022:** The v1 board arrived and was partially assembled due to missing components from shipping difficulties. However, this inconvenience has gratefully provided me some time to reflect that the v1 design is too ambitious. I was a bit unconfident about the NEO-6M GPS Module schematic prior to sending to my gerbers to JLCPCB. Additionally, the GPS antenna connector was tedious to solder.

Hopefully, once the academic quarter ends, I can start and finish the v2 board. Rather than embedding an entire GPS Module into the PCB, I plan to simply add jumper headers for a [GPS Breakout Board Module](https://www.amazon.com/Microcontroller-Compatible-Sensitivity-Navigation-Positioning/dp/B07P8YMVNT/ref=sr_1_3?crid=22ROHB4K82FYE&keywords=gps+module&qid=1671508036&sprefix=gps+modul%2Caps%2C156&sr=8-3)

<p align="center">
  <img src="v1\outputs\board_v1.jpg" style="max-width: 50%;"/>
</p>

**December 2022:** The v2 board finalized and sent to JLCPCB to be manufactured. Implemented design changes,

- Scaled down the GPS Module schematic from v1 to simply jumper headers for a [GPS Breakout Board Module](https://www.amazon.com/Microcontroller-Compatible-Sensitivity-Navigation-Positioning/dp/B07P8YMVNT/ref=sr_1_3?crid=22ROHB4K82FYE&keywords=gps+module&qid=1671508036&sprefix=gps+modul%2Caps%2C156&sr=8-3)
- Replaced the SD Card Slot Socket from v1. The PCB part generated a conflicting layer in JLCPCB's program prior to manufacturing
- Revised the `RESET` and `BOOT` button schematic
- Minor edits to the power decoupling on the ESP32 and CP2102 chip
