
#include <ESP8266WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

String  Myvalue;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "pradeepp70"
#define AIO_KEY  "aio_btuR85L8ysHYPQ5uTDxnZuTApoWQ"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe voicecommamnds = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/voicecommamnds");
boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}
int rightMotor2 = D7;   // D7 - right Motor -
int rightMotor1 = D6;   // D8 - right Motor +
int leftMotor1 = D3; // Left motor -
int leftMotor2 = D4; //Left motor +
void setup()
{
  Myvalue = "";

Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT); 
  pinMode(leftMotor2, OUTPUT);  
  pinMode(rightMotor1, OUTPUT);  
  pinMode(rightMotor2, OUTPUT);  
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
   WiFi.begin("madhavi","12345");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&voicecommamnds);

}


void loop()
{

    if (MQTT_connect()) {
      Adafruit_MQTT_Subscribe *subscription_name;
      while ((subscription_name = mqtt.readSubscription(5000))) {
        if (subscription_name == &voicecommamnds) {
          Myvalue = ((char *)voicecommamnds.lastread);
          Serial.println(Myvalue);
          if (Myvalue == "forward") {
            Serial.println("Forward");
          forwardMotor();
          }
          if (Myvalue == "backward") {
            Serial.println("backward");
            reverseMotor();
          }
          if (Myvalue == "right") {
            Serial.println("right");
             rightMotor();
          }
          if (Myvalue == "left") {
            Serial.println("left");
            leftMotor();
          }
          if (Myvalue == "stop") {
            Serial.println("stop");
            stopMotor();
          }

        }

      }

    }

}

void forwardMotor(void)   
{    
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
}

/* command motor backward */
void reverseMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
}

/* command motor turn left */
void leftMotor(void)   
{

  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
}

/* command motor turn right */
void rightMotor(void)   
{

  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
}

/* command motor stop */
void stopMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
}
