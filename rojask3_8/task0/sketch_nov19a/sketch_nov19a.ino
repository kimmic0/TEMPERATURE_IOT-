#include <WiFi101.h>

#define tempPin  A1
#define buttonPin  A0
#define photoPin  A4
float v = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(buttonPin);
  if(buttonState == LOW)
  {
    float heat = analogRead(tempPin);
    v = heat * (5000/1024);
  }
  float realHeat = 25-((0.75+v)/(10^2));
  Serial.print("temperature : ");
  Serial.print(realHeat);
  Serial.print(" F\n");
}
