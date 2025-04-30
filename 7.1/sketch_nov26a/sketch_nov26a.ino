// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL2KIo5FwVI"
#define BLYNK_TEMPLATE_NAME "Kimberly"
#define BLYNK_AUTH_TOKEN "9hP9yGXO3NndpLtPTAjbZ_Ekuo-yn7BH"
#define tempPin A1
const int trigPin = 6;
const int echoPin = 7;
long duration = 0;
float distance = 0.0;
// Comment this out to disable prints and save space
#define BLYNK_PRINT SerialUSB
#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleWiFiShield101.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RojasFam";
char pass[] = "L0v3sh0t";
char auth[] = "9hP9yGXO3NndpLtPTAjbZ_Ekuo-yn7BH";

void setup()
{
  // Debug console
  SerialUSB.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(tempPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  Blynk.run();
  sensor();
}

void sensor() {

  //temperature calculation
  float heat = analogRead(tempPin) ;
  float v = heat * (3300/1024);
  float realHeat = (v - 500 ) / 10;

  //acquire distance 
  digitalWrite(trigPin, LOW);
  delay(1);
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);

  //distance calculation
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .034) /2;

  //prints the temperature
  Serial.print("temperature : ");
  Serial.print(realHeat);
  Serial.println(" C \n");
  Blynk.virtualWrite(V5, realHeat); //collect the value and bring it to v5

  //prints the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Blynk.virtualWrite(V2, distance);
  delay(2000);
}