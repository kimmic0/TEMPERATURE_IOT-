// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL2KIo5FwVI"
#define BLYNK_TEMPLATE_NAME "Kimberly"
#define BLYNK_AUTH_TOKEN "9hP9yGXO3NndpLtPTAjbZ_Ekuo-yn7BH"
int ledPin = 6; //led pin
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

BLYNK_WRITE(V2)
{ // Executes when the value of v1 changes remember screen above
  if(param.asInt() == 1) // if true
  {
      sensor(); //execute sensor function
  }
  else{
      digitalWrite(ledPin, LOW); // turn led off
  }
}

void setup()
{
  // Debug console
  SerialUSB.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  pinMode(ledPin, OUTPUT); // set led pin assignment
  digitalWrite(ledPin, LOW); //automatically set led to off
}

void loop() 
{
  Blynk.run();
}

void sensor()
{
  digitalWrite(ledPin, HIGH); // turn led on when button pressed
}