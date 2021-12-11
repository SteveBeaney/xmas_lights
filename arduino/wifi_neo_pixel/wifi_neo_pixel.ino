#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

#ifndef STASSID
#define STASSID "b1"
#define STAPSK  "ed174b4c5e"
#endif
#define LED_PIN0    14
#define LED_PIN1    15
#define LED_PIN2    12
#define LED_PIN3    4
#define LED_PIN4    13
#define LED_COUNT   100
#define TOTAL       500

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(LED_COUNT, LED_PIN0, NEO_RGB + NEO_KHZ400);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(LED_COUNT, LED_PIN1, NEO_RGB + NEO_KHZ400);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LED_COUNT, LED_PIN2, NEO_RGB + NEO_KHZ400);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(LED_COUNT, LED_PIN3, NEO_RGB + NEO_KHZ400);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(LED_COUNT, LED_PIN4, NEO_RGB + NEO_KHZ400);

void handlePlain() {
    if (server.method() == HTTP_POST) {
        server.send(200, "text/plain",  "0");
        String s = server.arg("plain");
        for( int p=0; p<s.length()/6; p++ ) {   
            int g = hex2int( s[p*6+0],s[p*6+1] );
            int r = hex2int( s[p*6+2],s[p*6+3] );
            int b = hex2int( s[p*6+4],s[p*6+5] );
            setPix(p,g,r,b);
        }
        showPix();
    }
}

int hex2int( int a, int b ) {
    int r = h2i( a )*16 + h2i(b);
    if( r < 0 ){
        r = 0; 
    }
    if( r >255 ){
        r = 255; 
    }
    return r;
}

int h2i ( int a ) {
    int r = a-'0';
    if( r>10 ) {
        r -= 7;
    }
    return r;
}

void setPix( int p, int r, int g, int b ) {
  int strip = p / 100;
  int led = p % 100;
  switch( strip )  {
      case 0:
          strip0.setPixelColor(led, strip0.Color(r,g,b));  
          break;
      case 1:
          strip1.setPixelColor(led, strip1.Color(r,g,b));  
          break;
      case 2:
          strip2.setPixelColor(led, strip2.Color(r,g,b));  
          break;
      case 3:
          strip3.setPixelColor(led, strip3.Color(r,g,b));  
          break;
      case 4:
          strip4.setPixelColor(led, strip4.Color(r,g,b));  
          break;
  }
}

void showPix() {
    strip0.show();  
    strip1.show();  
    strip2.show();  
    strip3.show();  
    strip4.show();  
}

void setup(void) {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(""); 

    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address:");
    Serial.println(WiFi.localIP());
    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");       
    }
    server.on("/led/", handlePlain);
    server.begin();
    Serial.println("HTTP server started");
    strip0.begin();
    strip1.begin();
    strip2.begin();
    strip3.begin();
    strip4.begin();
    for(int i=0; i<TOTAL; i++) { 
        setPix(i,40,0,40);
    }
    showPix();
    for(int i=1; i<TOTAL; i++) { 
        setPix(i,200,0,200);
        setPix(i-1,4,0,4);
        showPix();
        delay(10);
    }
    for( int n=0; n < 20; n++ ) {
        for(int i=0; i<TOTAL; i++) { 
            setPix(i,20,20,20);
        }
        showPix();
        delay(200);
        for(int i=0; i<TOTAL; i++) { 
            setPix(i,40,0,0);
       }
        showPix();
        delay(200);
    }  
    for(int i=0; i<TOTAL; i++) { 
            setPix(i,20,20,20);
    }
    showPix();
 }

void loop(void) {
    server.handleClient();
}
