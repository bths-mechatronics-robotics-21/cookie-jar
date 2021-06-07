
/*
COOKIE FEATURES:
Matthew Bilik
Computer Integrated Manufacturing
Mr. Lyons

BOILERPLATE FROM:
NodeMCU Web server for wi-fi remote control
2019, José Augusto Cintra
www.josecintra.com/blog
*/

/*
START INITIALIZATION
*/
// IMPORT GLOBAL VARIABLES:
#include "global.h"

//IMPORT PACKAGES:
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>


// IMPORT / INITIALIZE OTHER
using namespace std;

// INITIALIZE TIME 
#define EST (-4)

// INITIALIZE SERVO:
#include <Servo.h>
int cookieServo = 2;
Servo Servo1;

// Get time when first run:
int getCurrentTime(){
  time_t now;
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);  
  
  int hourTime = timeinfo->tm_hour+EST;

  return hourTime;
}

/*
 Compare the time loaded to the current time (in loop) 
 to determine when a cookie may be dispensed.
*/
int TIME_LOADED = getCurrentTime();

ESP8266WiFiMulti wifiMulti;     // For multiple wi-fi configuratiosn
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

// function prototypes for HTTP handlers
void handleRoot(); 
void handleNotFound();
/*
END INITIALIZATION
*/

void setup(){

  /* 
  BEGIN
  */
  Servo1.attach(cookieServo);
  delay(1000);  
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("ssid1", "password1");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid2", "password2");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

/*
  HANDLE URLS
*/

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/get-cookie", HTTP_GET, handleCookie);
  server.onNotFound(handleNotFound); // When a client requests an unknown URI 

/*
  END
*/

  server.begin(); // Actually start the server
  Serial.println("HTTP server started");
  return;
}

void loop(void){
  server.handleClient(); // Listen for HTTP requests from clients
  return;
}

/*
 REQUESTS HANDLED HERE:
*/

// In hours:
int dispenseInterval = 2;

void handleCookie(){
 // Check the time of request versus the initial time:
 if (getCurrentTime() > TIME_LOADED 
 && getCurrentTime()-dispenseInterval == TIME_LOADED) {
  // Dispense allowed!
  TIME_LOADED = getCurrentTime();
  server.send(200, "text/html", webCodeApproved);

  // OPEN AND CLOSE LID
  Servo1.write(90);
  // 3 SECOND DELAY
  delay(3000);
  Servo1.write(0);
  //END
 } else {
   // No dispense.
   timeLeft = getCurrentTime() - TIME_LOADED;
   server.send(200, "text/html", webCodeDenied);
 }
}

void handleRoot() {  // When URI / is requested, send a standard web page 
  server.send(200, "text/html", "Cookie Dispenser");
  return;
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Cookie not found."); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  return;
}
