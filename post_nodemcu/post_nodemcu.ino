#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;

long myChannelNumber = 1617988;
const char myWriteAPIKey[] = "QEK0DYH0NEUA3WYL";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("PTCL-BB-208", "356E3FB0");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float v = 50;
  float i = 10;
  Serial.println("Voltage: " + (String) v);
  Serial.println("Current: " + (String) i);
  ThingSpeak.writeField(myChannelNumber, 1, v, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, i, myWriteAPIKey);
  delay(5000);
}
