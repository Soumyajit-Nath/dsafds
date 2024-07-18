#include <ArduinoJson.h>
#include "AgriArenaClient.h"
#include "time.h"

String AgriArenaClient::getTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Failed to obtain time";
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  char buffer[64];
  strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(String(buffer));
  return String(buffer);
}


void AgriArenaClient::config(String URL, const char *certificate) {
    // this->client.setCACert(certificate);

    http.begin(client, URL);
    http.addHeader("Content-Type", "application/json");

    
    configTime(0, 0, ntpServer);
    
}


void AgriArenaClient::send(DynamicJsonDocument data, const uint64_t &chipId, IPAddress IP) {
  String timestamp = getTime();
    data["did"] = chipId;
  //  data["ip"] = IP;
    data["timestamp"] = timestamp;


    String jsonString;
    serializeJson(data, jsonString);
    Serial.println(jsonString);


    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }
}