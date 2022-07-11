#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "ACT102636485631";
const char* password = "59348679";
String serverName = "http://water-project-01.herokuapp.com";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int count=0;
void loop() {
  // put your main code here, to run repeatedly:
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      count+=1;
      String serverPath = serverName + "/up/flowrate:"+count;
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  delay(5000);
}
