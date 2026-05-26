#!/bin/bash
pio run --target clean
clear
pio run -t erase
clear
pio run -t build
clear
pio run --target upload
clear
pio device monitor --port COM7 -b 115200
