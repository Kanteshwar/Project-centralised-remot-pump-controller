#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "GOOD BOY";
const char* password = "mani2810";
 

#define ORG "ppql51"
#define DEVICE_TYPE "SONY"
#define DEVICE_ID "IOT"
#define TOKEN "pavanisony"
String command;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//Serial.println(clientID);

WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int payloadLength);
PubSubClient client(server, 1883, callback, wifiClient);
void setup() {
  Serial.begin(115200);
  Serial.println();
   pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
  wifiConnect();
  mqttConnect();
}

void loop() {
  if (!client.loop()) {
    mqttConnect();
  }
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    //Serial.println((char)payload[i]);
    command += (char)payload[i];
  }
Serial.println(command);
if(command == "Motor1ON"){
  digitalWrite(D1,HIGH);
  Serial.println("Motor 1 is Switched ON");
}
else if(command == "Motor1OFF"){
  digitalWrite(D1,LOW);
  Serial.println("Motor 2 is Switched OFF");
}

if(command == "Motor2ON"){
  digitalWrite(D2,HIGH);
  Serial.println("Motor 2 is Switched ON");
}
else if(command == "Motor2OFF"){
  digitalWrite(D2,LOW);
  Serial.println("Motor 2 is Switched OFF");
}
command ="";
}
