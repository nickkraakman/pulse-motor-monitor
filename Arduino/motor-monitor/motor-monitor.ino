#include "config.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int batteryVoltagePin = A0;  // analog pin for reading battery voltage
const float referenceVoltage = 5.0;  // reference voltage for the Arduino

void setup() {
  Serial.begin(9600);  // initialize serial communication
  delay(10);

  // connect to WiFi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  int batteryVoltageReading = analogRead(batteryVoltagePin);  // read the voltage from the battery
  float batteryVoltage = batteryVoltageReading * referenceVoltage / 1023.0;  // calculate the battery voltage

  // create a JSON object with the battery voltage
  StaticJsonDocument<200> doc;
  doc["voltage"] = batteryVoltage;

  // send the JSON object to the web server
  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  String json;
  serializeJson(doc, json);
  int httpResponseCode = http.POST(json);

  // check the response code and print the result
  if (httpResponseCode == HTTP_CODE_OK) {
    Serial.println("Battery voltage sent successfully");
  } else {
    Serial.println("Error sending battery voltage");
  }

  delay(1000);  // wait 1 second before sending the voltage again
}
