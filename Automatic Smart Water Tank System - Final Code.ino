#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
 
//define pins for Ultrasonic Sensor
const int trig = D5;     //D5 pin of nodemcu trig
const int echo = D6;     //D6 pin of nodemcu echo

const int motor= D4;     // the Nodemcu pin D4, which connects to the IN pin of motor
const int buzzer = D7;    // buzzer to arduino pin D7

bool isMotorON  = false;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

//define pin for Temp Sensor
#define ONE_WIRE_BUS D2     // D2 pin of nodemcu

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);      // Pass the oneWire reference to Dallas Temperature.

long duration;
float distanceCm;

String apiKey = "HXTF4LWG32GOS61L";     //  Enter Write API key from ThingSpeak
 
const char *ssid =  "Redmi 7";       // place wifi ssid
const char *pass =  "pasindu98";      // place wifi password
const char *server = "api.thingspeak.com";      // thingspeak api

WiFiClient client;
 
void setup() 
{
       Serial.begin(9600); // Starts the serial communication
       pinMode(trig, OUTPUT); // Sets the trigPin as an Output
       pinMode(echo, INPUT); // Sets the echoPin as an Input
       sensors.begin();

       // initialize digital pin D4 as an output.
       pinMode(motor, OUTPUT);

       pinMode(buzzer, OUTPUT); // Set buzzer - pin D7 as an output
       
       Serial.print("Connecting to ");
       Serial.println(ssid);
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
      // Clears the trigPin
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echo, HIGH);
      
      // Calculate the distance
      distanceCm = duration * SOUND_VELOCITY/2;

      float r = 7.75 ; // In radius meters
      float h = 22.5 ; // Water tank height
      float v = (22/7) * r * r * h / 1000; // Full tank volume
      
      float waterHeight = h - distanceCm;  // water height
      
      float waterVolume = (22/7) * r * r * waterHeight / 1000; // Tank water volume
      
      float waterPercentage = (waterVolume / v) * 100; // Percentage of available water

      sensors.requestTemperatures();
      float waterTemperature = sensors.getTempCByIndex(0);

      if (waterPercentage <= 30) {
//        if (isMotorON = false) {
//          isMotorON = true;
          digitalWrite(motor, LOW); // turn on pump
          Serial.println(" Water Motor ON ");
//        }
      }
        
      else if (waterPercentage >= 85) {
        digitalWrite(motor, HIGH);  // turn off pump
        Serial.println(" Water Motor OFF ");
      }
      if (waterTemperature >= 30) {
        tone(buzzer, 2000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        
      }
      else if (waterTemperature < 30) {
        noTone(buzzer);     // Stop sound...
        delay(1000);        // ...for 1sec
      }

      
              if (isnan(waterPercentage) || isnan(waterTemperature))
                
                 {
                     Serial.println("Failed to read from sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(waterPercentage);
                             postStr +="&field2=";
                             postStr += String(waterVolume);
                             postStr +="&field3=";
                             postStr += String(waterTemperature);
                             
                             postStr += "\r\n\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             // Print the Water Volume on the Serial Monitor
                             Serial.print("Water Volume: ");
                             Serial.print(waterVolume);
                             Serial.println(" Liters");
                             
                             // Print the Water Percentage on the Serial Monitor
                             Serial.print("Water Percentage: ");
                             Serial.print(waterPercentage);
                             Serial.println(" %");
                             
                             // Print the temperature on the Serial Monitor
                             Serial.print("Temperature is: ");
                             Serial.print(waterTemperature);
                             Serial.println(" C");
                             
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
          Serial.println("");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
