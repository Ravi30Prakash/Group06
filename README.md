# Group06
Flow Chart:
1. Start
2. Initialize Tiva TM4C
  Set clock and configure GPIO pins.
3. Initialize SD Card
  Check if the SD card is detected.
  If successful, proceed; if not, display error and restart.
4. Initialize Sensors
  Check if sensors are operational.
  If successful, proceed; if not, display error and halt.
5. Data Collection Loop:
  Read data from sensors.
  Format data for storage (e.g., CSV).
  Write formatted data to a specified location on the SD card.
  Wait for a specified interval before the next reading.
6. Check for Stop Condition
  If stop condition is met, proceed to end.
  Otherwise, repeat from step 5.
7. End:
  Close the file on the SD card.
  Power down the system safely.
