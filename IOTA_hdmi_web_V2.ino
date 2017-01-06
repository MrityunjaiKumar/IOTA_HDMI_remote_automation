#define rgb_r_pin 12
#define rgb_b_pin 4
#define rgb_g_pin 15
#define dht_pin 13
#define buzzer_pin 2
#define ir_led_pin 14
#define tsop_pin 5
#define ldr_pin A0
#define user_switch 2

/*
 * IOTA platform developed (as a part of my BTP project) at www.cedtnsit.in
 * Few application developed at http://iot.net.in/
 * Based on https://github.com/markszabo/IRremoteESP8266 library
 * 
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 *By:- www.mrityunjai.in
 */

/*
*
###windows port 1
irsend.sendNEC(0xFF18E7, 38);
0xFF18E7

###raspi port 2
irsend.sendNEC(0xFF10EF, 38);
0xFF10EF

###kali Port  3
irsend.sendNEC(0xFF9867, 38);
0xFF9867

*/

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>

IRsend irsend(ir_led_pin); 

const char* ssid = "";
const char* password = "";

WiFiServer server(80);

int hdmi_status=1;

void setup() {
  irsend.begin();
  Serial.begin(9600);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

int hdmi_val;

if (req.indexOf("/hdmi/1") != -1)
    hdmi_val = 1;
else if (req.indexOf("/hdmi/2") != -1)
    hdmi_val = 2;
else if (req.indexOf("/hdmi/3") != -1)
    hdmi_val = 3;  
else if (req.indexOf("/hdmi/4") != -1)
    hdmi_val = 4;  
else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  handle_ir(hdmi_val);
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n Selected HDMI is now ";
  s += (String)(hdmi_val);
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}

