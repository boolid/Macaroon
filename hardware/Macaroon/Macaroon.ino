#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ArduinoJson.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"         //https://github.com/tzapu/WiFiManager

#include <WS2812FX.h>
#define LED_PIN   D2 // digital pin used to drive the LED strip (esp8266)
#define LED_COUNT 30 // number of LEDs on the strip
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <EEPROM.h>
#define ANALOG_PIN A0
#define SAMPLE_SEC 50

int ANALOG_THRESHOLD = 1024;
int address_size = 4000;
unsigned long previousMillis = 0;

extern const char index_html[];
extern const char settings_html[];
extern const char main_js[];

std::unique_ptr<ESP8266WebServer> server;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(address_size);
  WiFiManager wifiManager;
  
  //reset saved settings
  wifiManager.autoConnect("Macaroon");

  server.reset(new ESP8266WebServer(WiFi.localIP(), 80));

  server->on("/", srv_handle_main_page);
  server->on("/js/script.js", srv_handle_main_js);
  server->on("/get", srv_handle_get);
  server->on("/set", HTTP_POST, srv_handle_set);
  server->onNotFound(srv_handle_not_found);

  server->begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());

  ws2812fx.init();
  String data = read_memory();
  set_LED(data);
  ws2812fx.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  ws2812fx.service();
  server->handleClient();

  // 100ms delay for reading Analog Value as it freezes the server
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= SAMPLE_SEC) {
    if(analogRead(ANALOG_PIN) > ANALOG_THRESHOLD) {
      Serial.println("Sound Triggered");
      ws2812fx.trigger();
    }
    previousMillis = millis();
  }

  // Reset Wifi Connection
//  wifiManager.resetSettings();
}

String read_memory() {
  String data = "";
  for (int i = 0; i < address_size; i++){
    byte read_data = EEPROM.read(i);
    if (read_data > 0) {
      data += char(read_data);  
    }
  }
  Serial.println("READING MEMORY:");
  Serial.println(data);
  return data;
}

void clear_memory() {
  for (int i = 0 ; i < address_size; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

void write_memory(String data) {
  clear_memory();
  for (int i = 0; i < data.length(); i++){
    EEPROM.write(i, data[i]);
  }
  EEPROM.commit();
}

void srv_handle_main_page() {
  server->send_P(200,"text/html", index_html);
}

void srv_handle_main_js() {
  server->send_P(200,"application/javascript", main_js);
}

void srv_handle_not_found() {
  server->send(404, "text/plain", "File Not Found");
}

String createJsonResponse() {
  StaticJsonBuffer<500> jsonBuffer;

  JsonObject &root = jsonBuffer.createObject();
  root["countLED"] = ws2812fx.numPixels();
  root["brightness"] = ws2812fx.getBrightness();
  root["soundThreshold"] = ANALOG_THRESHOLD;
  
  JsonArray& jsonSegments = root.createNestedArray("segments");  
  WS2812FX::segment* segments = ws2812fx.getSegments();
  for(int i=0; i<ws2812fx.getNumSegments(); i++) {
    WS2812FX::segment seg = segments[i];
    JsonObject& jsonSegment = jsonBuffer.createObject();
    jsonSegment["segmentStart"] = seg.start;
    jsonSegment["segmentEnd"] = seg.stop;
    jsonSegment["mode"] = seg.mode;
    jsonSegment["speed"] = seg.speed;
    jsonSegment["color"] = String(seg.colors[0], HEX);
    jsonSegments.add(jsonSegment);
  }
    
  String json;
  root.prettyPrintTo(json);
  return json;
}

void srv_handle_get() {
  server->send(200,"text/json", createJsonResponse());
}

void srv_handle_set() {
  String data = server->arg("plain");
  Serial.println(data);
  write_memory(data);
  set_LED(data);
  server->send(200, "text/plain", "OK");
}

void set_LED(String data) {
  DynamicJsonBuffer jsonBuffer(1000);
  JsonObject& root = jsonBuffer.parseObject(data);
  String json;
  root.prettyPrintTo(json);
  Serial.println(json);
  if (root.success()) {
    ANALOG_THRESHOLD = root["soundThreshold"];
    ws2812fx.stop();
    ws2812fx.setLength(root["countLED"]);
    ws2812fx.setBrightness(root["brightness"]);
    ws2812fx.setNumSegments(1); // reset number of segments
    JsonArray& segments = root["segments"];
    for (int i = 0; i< segments.size(); i++){
      JsonObject& seg = segments[i];
      uint32_t color = (uint32_t) strtol(seg["color"], NULL, 16);
      ws2812fx.setSegment(i, seg["segmentStart"], seg["segmentEnd"], seg["mode"], color, seg["speed"], false);
    }
    ws2812fx.start();
  }
  Serial.println("Finish Setting LED");
}

