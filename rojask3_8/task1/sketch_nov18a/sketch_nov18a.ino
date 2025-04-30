//publisher code 
#include <ArduinoMqttClient.h>
#include <WiFi101.h>
#define tempPin A1 //pin of your sensor
//WiFi that you want to be connected
char ssid[] = "RojasFam"; // your network SSID (name)
char pass[] = "L0v3sh0t"; // your network password (use for WPA, or use as key for WEP)
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.0.219"; //your broker here is mosquitto
int port= 1883; //channel of the broker
//topics, you can change the name
const char topic[] = "real_unique_topic";
const char topic2[] = "real_unique_topic_2";
const char topic3[] = "real_unique_topic_3";
//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;
int count = 0;
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
}
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
  // failed, retry
  Serial.print(".");
  delay(5000);
}
  Serial.println("You're connected to the network");
  Serial.println();
  //connection to the broker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  //connection to the broker failed
  if (!mqttClient.connect(broker, port)) {
  Serial.print("MQTT connection failed! Error code = ");
  Serial.println(mqttClient.connectError());
  while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  }

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  // save the last time a message was sent
  previousMillis = currentMillis;
  //record sensor valuse
  float heat = analogRead(tempPin) ;
  float v = heat * (3300/1024);
  float realHeat =(v - 500 ) / 10;
  //int Rvalue3 = analogRead(A2);
  /*Serial.print("Sending message to topic: ");
  Serial.println(topic);
  Serial.println(Rvalue);*/
  //Register the temperature by the topic2
  Serial.print("Sending message to topic: ");
  Serial.println(topic2);
  Serial.println(realHeat);
  /*Serial.print("Sending message to topic: ");
  Serial.println(topic2);
  Serial.println(Rvalue3);*/
  // send message, the Print interface can be used to set the message contents
  /* mqttClient.beginMessage(topic);
  mqttClient.print(Rvalue);
  mqttClient.endMessage();*/
  //sending the message
  mqttClient.beginMessage(topic2);
  mqttClient.print(realHeat);
  mqttClient.endMessage();
  /* mqttClient.beginMessage(topic3);
  mqttClient.print(Rvalue3);
  mqttClient.endMessage();*/
  Serial.println();
  }
}
