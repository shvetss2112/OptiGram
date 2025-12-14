#ifndef UNTITLED2_OPTIGRAM_H
#define UNTITLED2_OPTIGRAM_H
#include <ESP8266WiFi.h>
void apiRequest(WiFiClientSecure& client,const char* botId,const char* method) {
    client.connect(F("api.telegram.org"),443);

    client.print(F("GET /bot"));
    client.print(botId);
    client.print(method);client.println(F(" HTTP/1.1"));

    client.println(F("Host: api.telegram.org"));
    client.println(F("Connection: close"));
    client.println();
}
#endif //UNTITLED2_OPTIGRAM_H