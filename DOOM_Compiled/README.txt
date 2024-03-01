# DOOM For WIFI Toothbrush

Flash the compiled files via:

esptool.py --port COM1  --baud 115200 write_flash 0x0000 bootloader.bin
esptool.py --port COM1  --baud 115200 write_flash 0x8000 partition-table.bin
esptool.py --port COM1  --baud 115200 write_flash 0x10000 esp32c3-doom-application.bin
esptool.py --port COM1  --baud 115200 write_flash 0x140000 MiniDOOM.wad