#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "OptiString.h"
#include <string>
#include "OptiGram.h"

const char* ssid = "";
const char* password = "";
const char* botId="";
const char* debugUserId="";
void flushIntoConsole(WiFiClientSecure& client) {
    while (client.connected() || client.available()) {
        if (client.available()) {
            char c = client.read();
            Serial.print(c);
        }
        yield();
    }
}

WiFiClientSecure client;
void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    client.setInsecure();
}

int counter = 0;
void loop() {

    apiRequest(client,botId,"/getUpdates?limit=1");
    Serial.println("\n\nHttp responce:");
    flushIntoConsole(client);

    OptiString<> messageMethod("/sendMessage?chat_id=");
    messageMethod.append(debugUserId);
    messageMethod.append("&text=");
    messageMethod.append(std::to_string(counter++).c_str());

    apiRequest(client,botId,messageMethod.c_str());

    client.stop();
    delay(1000);
}

