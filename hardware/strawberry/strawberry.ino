#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WS2812FX.h>

extern const char index_html[];
extern const char settings_html[];
extern const char main_js[];

#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"

//#define STATIC_IP                       // uncomment for static IP, set IP below
#ifdef STATIC_IP
  IPAddress ip(192,168,0,123);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
#endif

// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define LED_PIN 2                       // 0 = GPIO0, 2=GPIO2
#define LED_COUNT 24

#define WIFI_TIMEOUT 30000              // checks WiFi every ...ms. Reset after this time, if WiFi cannot reconnect.
#define HTTP_PORT 80

#define DEFAULT_COLOR 0xFF5900
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_SPEED 200
#define DEFAULT_MODE FX_MODE_STATIC

#define BRIGHTNESS_STEP 15              // in/decrease brightness by this amount per click
#define SPEED_STEP 10                   // in/decrease brightness by this amount per click

unsigned long last_wifi_check_time = 0;
String modes = "";

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server = ESP8266WebServer(HTTP_PORT);


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Starting...");

  modes.reserve(5000);
  modes_setup();

  Serial.println("WS2812FX setup");
  ws2812fx.init();
  ws2812fx.setMode(DEFAULT_MODE);
  ws2812fx.setColor(DEFAULT_COLOR);
  ws2812fx.setSpeed(DEFAULT_SPEED);
  ws2812fx.setBrightness(DEFAULT_BRIGHTNESS);
  ws2812fx.start();

  Serial.println("Wifi setup");
  wifi_setup();
 
  Serial.println("HTTP server setup");
  server.on("/", srv_handle_index_html);
  server.on("/settings", srv_handle_settings_html);
  server.on("/js/script.js", srv_handle_main_js);
  server.on("/modes", srv_handle_modes);
  server.on("/setup", srv_handle_setup);
  server.on("/set", srv_handle_set);
  server.onNotFound(srv_handle_not_found);
  server.begin();
  Serial.println("HTTP server started.");

  Serial.println("ready!");
}


void loop() {
  unsigned long now = millis();

  server.handleClient();
  ws2812fx.service();

  if(now - last_wifi_check_time > WIFI_TIMEOUT) {
    Serial.print("Checking WiFi... ");
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost. Reconnecting...");
      wifi_setup();
    } else {
      Serial.println("OK");
    }
    last_wifi_check_time = now;
  }
}



/*
 * Connect to WiFi. If no connection is made within WIFI_TIMEOUT, ESP gets resettet.
 */
void wifi_setup() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.mode(WIFI_STA);
  #ifdef STATIC_IP  
    WiFi.config(ip, gateway, subnet);
  #endif

  unsigned long connect_start = millis();
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(millis() - connect_start > WIFI_TIMEOUT) {
      Serial.println();
      Serial.print("Tried ");
      Serial.print(WIFI_TIMEOUT);
      Serial.print("ms. Resetting ESP now.");
      ESP.reset();
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}


/*
 * Build <li> string for all modes.
 */
void modes_setup() {
  modes = "";
  for(uint8_t i=0; i < ws2812fx.getModeCount(); i++) {
    modes += "<button class='dropdown-item' type='button' value='";
    modes += i;
    modes += "'>";
    modes += ws2812fx.getModeName(i);
    modes += "</button>";
  }
}

/* #####################################################
#  Webserver Functions
##################################################### */

void srv_handle_not_found() {
  server.send(404, "text/plain", "File Not Found");
}

void srv_handle_index_html() {
  server.send_P(200,"text/html", index_html);
}

void srv_handle_settings_html() {
  server.send_P(200,"text/html", settings_html);
}

void srv_handle_main_js() {
  server.send_P(200,"application/javascript", main_js);
}

void srv_handle_modes() {
  server.send(200,"text/plain", modes);
}

String createJsonResponse() {
  StaticJsonBuffer<500> jsonBuffer;

  JsonObject &root = jsonBuffer.createObject();
  root["ledlength"] = ws2812fx.getLength();
  root["brightness"] = ws2812fx.getBrightness();
  root["speed"] = ws2812fx.getSpeed();

  String json;
  root.prettyPrintTo(json);
  return json;
}

void srv_handle_setup() {
  server.send(200,"text/json", createJsonResponse());
}


void srv_handle_set() {
  for (uint8_t i=0; i < server.args(); i++){
    if(server.argName(i) == "c") {
      uint32_t tmp = (uint32_t) strtol(&server.arg(i)[0], NULL, 16);
      if(tmp >= 0x000000 && tmp <= 0xFFFFFF) {
        ws2812fx.setColor(tmp);
      }
    }

    if(server.argName(i) == "m") {
      uint8_t tmp = (uint8_t) strtol(&server.arg(i)[0], NULL, 10);
      ws2812fx.setMode(tmp % ws2812fx.getModeCount());
    }

    if(server.argName(i) == "b") {
      uint8_t tmp = (uint8_t) strtol(&server.arg(i)[0], NULL, 10);
      ws2812fx.setBrightness(tmp);
    }

    if(server.argName(i) == "s") {
      uint8_t tmp = (uint8_t) strtol(&server.arg(i)[0], NULL, 10);
      ws2812fx.setSpeed(tmp);
    }

    if(server.argName(i) == "l") {
      uint32_t tmp = (uint32_t) strtol(&server.arg(i)[0], NULL, 10);
      ws2812fx.setLength(tmp);
    }
  }
  server.send(200, "text/plain", "OK");
}
