#include <ESP8266WiFi.h>

const char* ssid = "SHAW-CAA940";
const char* password = "251154132470";

const char* host = "cdn.rawgit.com";
const char* url = "/boolid/Strawberry/master/webserver/main.html";

String html = "";

WiFiServer server(80); // MDefine Web Server Port

String get_mainpage(){
  String html_return = "";
  WiFiClient client;

  Serial.printf("\n[Downloading Content from %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        html_return += line + "\r\n";
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    html_return = "Connection Failed!";
    Serial.println("connection failed!]");
    client.stop();
  }
  int start_html = html_return.indexOf("<!DOCTYPE HTML>");
  if(start_html > 0){
    int end_html = html_return.indexOf("</html>");
    html_return = html_return.substring(start_html, end_html + 7);
  }
  
  return html_return;
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Serial.println("Getting the html files from the server");
  html = get_mainpage();
  Serial.println("Done getting the files");

  // Start the Web Server
  server.begin();
  Serial.println("Web Server Started");

  // Display IP address
  Serial.print("You can connect to the Server here: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println();
}


void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  client.print(html);
  Serial.println(html);
  delay(1000);
}
