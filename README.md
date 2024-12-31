# STM32F072C8T6 Kit

The STM32F072C8T6 kit is a CAN bus adaptor with cellular and GNSS connecitivity that can be used for the new 5G wireless technology. This kit is available here:

The hardware board is a powerful board that features a microcontroller and a wireless modem. The microcontroller is an STM32F072C8T6 MCU which features a 32-bit ARM Cortex® M0+ core. The wireless modem is Quectel BG96/BG95/EG91/EG95 which is an embedded IoT (LTE Cat-M1, LTE Cat-NB1 and EGPRS) wireless communication modem. 

The board provides rich sets of Internet protocols (TCP/UDP/PPP/SSL/TLS/FTP/HTTP/PING/ MQTT/NITZ/SMS), GNSS technology (GLONASS, BeiDou/Compass, Galileo, QZSS), industry-standard interfaces (USB/UART/I2C/SPI/GPIO/ADC/DAC/PWM/JTAG/Interrupts/LEDs/Status Indicators), Nano USIM slot for a nano SIM card, and USB ports and DC power jack for external power supply. 

The board also supports two modes of operation; the first mode where the MCU controls the wireless modem and second mode where the modem is controlled directly without the need of the MCU. 
The board is ultra-compact size (2.8-inch X 1.6-inch) and fits into many embedded devices and applications.

The board is also compatible with Arduino and Arduino software (IDE). Many Arduino sketches and examples are provided with the kit and additional sketches can be developed and uploaded to the board.

The board supports Windows 7/8/8.1/10, Linux and Android.

The NB-IoT board is a rich board that can be used for a variety of smart and 5G applications. It enables applications such as wireless POS, smart metering, tracking, smart transportation, smart buildings, smart city, and smart homes, navigation, location, and tracking. 

# Arduino IDE Compatibiltiy
This Repository is compatible with Arduino IDE 2.1.1

# Software and Tools Included with the Board
-ArduinoSketches: Contains different Arduino examples and sketches to use with the board.

-STM32_Arduino.zip: Contains the library (used with Arduino IDE). It contains many examples such as UART, TCP, HTTP, ICMP (Ping), MQTT, use with Modem dugther board (AT commands and GNSS)

-STM32-Core.zip: Contains the board manager (used with Arduino IDE).

-Kit sketches: Folder contains more Arduino sketches for the STM32 USB board.

-CAN Adaptor: Folder contains Arduino sketches to use it with the CAN transceiver daughterboard , ISO1050, to make an CAN Adaptor. It contains also sketches to use it with cellular& GNSS modem. This will enable to use STM32 motherboard with CAN and Modem daughterboard to form a complete CAN adaptor with cellular and GNSS connectivity.

-Tools: Different tools including Quectel QNavigator and QCOM that can be used with the cellular & GNSS modem to communicate over USB or serial ports.


# How to Use Arduino IDE with the Board

1.	Install Arduino IDE for Windows from the following web site (Minimum Arduino IDE version 2.1.1):
https://www.arduino.cc/en/Main/Software

2.	Launch Arduino IDE and choose File->Preferences. In the Additional Boards Manager URLs, insert the following URL:
https://raw.githubusercontent.com/5ghub/stm32/refs/heads/master/package_STM32_index.json

4.	In Arduino IDE, choose Tools->Board->Boards Manager and install “STM32F072C8T6 Board”.

5.	Choose “STM32F072C8T6”

6. In the Arduino IDE, Choose Sketch->Include Library->Add .Zip Library and select the file STM32_Arduino.zip 

7.	You are ready now to use the Arduino IDE, use many example sketches, and  write the first sketch.
