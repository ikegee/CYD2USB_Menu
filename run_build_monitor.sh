#!/bin/bash

# create variable for your USB-Serial COM port
COM_PORT="COM7"

pio run --target clean
clear
pio run -t erase
clear
pio run -t build
clear
pio run --target upload
clear
pio device monitor --port $COM_PORT --baud 115200
