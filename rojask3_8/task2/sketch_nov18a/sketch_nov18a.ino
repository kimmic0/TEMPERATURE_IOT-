//client code
#include <ArduinoMqttClient.h>
#include <WiFi101.h>
//WiFi that you want to be connected
char ssid[] = "RojasFam"; // your network SSID
char pass[] = "L0v3sh0t"; // your network password
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.0.219"; //your broker here is mosquitto
int port = 1883; //channel of the broker
//topics, you can change the name
const char topic[] = "real_unique_topic";
const char topic2[] = "real_unique_topic_2";
const char topic3[] = "real_unique_topic_3";
void setup() {
//Initialize serial and wait for port to open:
Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
// attempt to connect to Wifi network:
Serial.print("Attempting to connect to SSID: ");
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
// set the message receive callback, setup that you are the subscriber
mqttClient.onMessage(onMqttMessage);
Serial.print("Subscribing to topic: ");
Serial.println(topic);
Serial.println();
// subscribe to a topic
mqttClient.subscribe(topic);
mqttClient.subscribe(topic2);
mqttClient.subscribe(topic3);
// topics can be unsubscribed using:
// mqttClient.unsubscribe(topic);
Serial.print("Topic: ");
Serial.println(topic);
Serial.print("Topic: ");
Serial.println(topic2);
Serial.print("Topic: ");
Serial.println(topic3);
Serial.println();
}
void loop() {
// call poll() regularly to allow the library to receive MQTT messages and
// send MQTT keep alive which avoids being disconnected by the broker
mqttClient.poll();
}
//print the MQTT message
void onMqttMessage(int messageSize) {
// we received a message, print out the topic and contents
Serial.println("Received a message with topic '");
Serial.print(mqttClient.messageTopic());
Serial.print("', length ");
Serial.print(messageSize);
Serial.println(" bytes:");
// use the Stream interface to print the contents
while (mqttClient.available()) {
Serial.print((char)mqttClient.read());
}
Serial.println();
Serial.println();
}