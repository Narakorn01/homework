/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "DHT.h"

#define DHTPIN 12  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "G49z0DOmMPbBc8njYdgm5lp26q6WXSVA";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PN18K";
char pass[] = "notch0848934416";

const int pingPin = 27;
int inPin = 26 ;

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(5,OUTPUT);
  pinMode(18,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.begin();
  
}

void loop()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Blynk.run();
  delay(100);
  Blynk.virtualWrite(5,HIGH);
  Blynk.virtualWrite(18,HIGH);
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, cm);

}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
