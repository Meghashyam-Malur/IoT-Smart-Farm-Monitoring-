#include <WiFi.h>
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include <DHT.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti; // object of type WiFiMulti

#define DHTPIN 4
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//const char *ssid =  "SPECTRON777";     // Enter your WiFi Name
//const char *pass =  " "; // Enter your WiFi Password

WiFiClient client;
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "Spectron777" // Your Adafruit IO Username
#define MQTT_PASS "aio_Oktn10Whh14K51PvxptaYibrAU4b" // Adafruit IO AIO key

const int moisturePin = A0;             // moisteure sensor pin
int moisturePercentage;              //moisture reading

//Set up the feed you're publishing to
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish Farm_Soil_M = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/feeds/farmdata.farm-soil-m");
Adafruit_MQTT_Publish Farm_Temp = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/feeds/farmdata.farm-temp");
Adafruit_MQTT_Publish Farm_Hmdty = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/feeds/farmdata.farm-hmdty");

void setup()
{
  Serial.begin(115200);
  delay(10);
  /*Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");*/
  
  wifiMulti.addAP("SPECTRON777", " ");         // add your wifi ssid and passwords here
  wifiMulti.addAP("SPECTRON2K2K 2.4Ghz", " "); // add your wifi ssid and passwords here

  Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected to:");
        Serial.println(WiFi.SSID());
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        
  dht.begin();
}
}





 void loop()
{
  
    MQTT_connect();
    int temp = analogRead(moisturePin);
  moisturePercentage = ( 100 - ( (analogRead(moisturePin) / 4095.00) * 100 ) );
  //moisturePercentage = map(temp,550,0,0,100);
  Serial.print("Soil Moisture is  = ");
  
  Serial.print(moisturePercentage);
  
  Serial.println("%");
  Serial.print("Raw SM vals  = ");
  Serial.println(temp);
  

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //int t = tmp;
  //int h = hum;
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");

  String data1 = String(moisturePercentage);
 
       if (! (Farm_Soil_M.publish(moisturePercentage)&& Farm_Temp.publish(t)&& Farm_Hmdty.publish(h))) //This condition is used to publish the Variable (moisturePercentage) on adafruit IO. Change thevariable according to yours.
       {                     
         delay(10000);   
          }
 delay(11000);
}


void MQTT_connect() 
{
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
