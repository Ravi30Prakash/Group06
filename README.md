# Group06
Project name: SD Card Datalogger

Aim: To study about SD card data management and storing a string of data in a continious data locations,
     which can be used for data logging purpose. 

Flow Chart (Program Flow):

    1. Initialize clock and configure GPIO pins for SPI and input button switch.
    2. Wait for button switch press.
    3. If button press detected Initia1ize SD Card and erase the SD card.
    4. Write a small string (eg: abcdefg) of data into the SD card in continious data location (not using any file format).
    5. wait for next button press, if pressed repeat from step 3.