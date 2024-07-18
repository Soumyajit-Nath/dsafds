#ifndef AGRIARENACLIENT_H
#define AGRIARENACLIENT_H

#include <ArduinoJson.h>
// #include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>

class AgriArenaClient {
    // WiFiClientSecure client;
    WiFiClient client;
    HTTPClient http;
    const char* ntpServer = "pool.ntp.org";
public:
    // AgriArenaClient();

    String getTime();
    void config(String, const char *);
    void send(DynamicJsonDocument, const uint64_t&, IPAddress);
};

#endif