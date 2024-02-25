# ATC_Wifi_Toothbrush
The fitting firmware to update the Wifi Toothbrush plus an example custom firmware for the ESP32-C3

This repo is made together with this explanation video:(click on it)

[![YoutubeVideo](https://img.youtube.com/vi/-qvn0YUiH5o/0.jpg)](https://www.youtube.com/watch?v=-qvn0YUiH5o)


Folder "HackTheBrush" holds the code for an ESP32 which will act as an access point for the toothbrush to update it OTA with the custom firmware.
If you want to change the custom firmware you need to change the "CustomFW.h" file to the newly compiled ESP32-C3 data.

Folder "Wifi_Toothbrush_firmware" is the custom firmware itself, make sure to select ESP32-C3 as the board and set the Patition sheme to custom so it will fit with the stock firmware layout.

