# IoT-Smart-Farm-Monitoring-
Designed and developed an Iot Based Farm monitoring module using ESP32 Node MCU, DHT11 Tempreature and humidity sensor and Soil Moisture sensor powered by Solar

For this project, the Node MCU ESP32  micro-controller unit is used, which takes sensor data from DHT11 Temperature and Humidity Sensor and HW808 Soil Moisture 
sensor every 10 seconds. The data is resolved and then uploaded to ADAFRUIT IO cloud IoT platform.

The Data from sensors range from digital to analog signals, the required preprocessing is done on board the NODE-MCU and resolved into the required format.
MQTT based Keys are generated from the FEEDs on the Adafruit IO page and are appropriately instantiated to allow for publishing of data to the feeds over MQTT.

Finally, the data stream is visualized to give important insights in the farms parameters so that farmers can take informed decisions in their practices.
