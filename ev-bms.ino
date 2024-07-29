#include <ESP32-TWAI-CAN.hpp>
#include <WiFi.h>
#include <Update.h>
#include <WebServer.h>
#include "EEPROM.h"

#include <DNSServer.h>

IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
const byte DNS_PORT = 53;
WebServer server(80);
const char* serverIndex = "<form method='POST' action='/doupdate' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

CanFrame rxFrame;
#define CAN_TX    5
#define CAN_RX    8


long tout;
long vspeed;
int batvolt[100];
long minvolt,maxvolt,v1,v2,v3,v4;
String strval;
byte bn,maxspeed;




String insertval(int i){
  return "<td>"+String(i)+"</td>";
}



void handleRoot() {

String msg;
msg="<head><meta http-equiv='refresh' content='5'><meta charset='utf-8'></head><body>";

msg+="<table border=1><tr>";
msg+="<td>Мінімальна напруга .</td>";
msg+=insertval(minvolt);
msg+="</tr><td>Максимальна напруга .</td>";
msg+=insertval(maxvolt);
msg+="<tr><td>Різниця між комірками</td>";
msg+=insertval(maxvolt-minvolt);
msg+="</tr>";

msg+="<tr><td>V1 .</td>";
msg+=insertval(v1);
msg+="</tr>";

msg+="<tr><td>V2 .</td>";
msg+=insertval(v2);
msg+="</tr>";

msg+="<tr><td>Відсоток заряду</td><td>";
msg+= String(v3/100.0,2);
msg+="</td></tr>";

msg+="<tr><td>V1 .</td>";
msg+=insertval(v4);
msg+="</tr>";

msg+="<tr><td>Швидкість</td>";
msg+=insertval(vspeed);
msg+="</tr>";
msg+="</table>";

msg+= strval+"<br><br>";
msg+="<table border=1><tr><td>Номер комірки .</td><td>Напруга на комірці .</td></tr>";

for (int i=1;i<91;i++){
msg+="<tr>";  
msg+=insertval(i);
msg+=insertval(batvolt[i]);
msg+="</tr>";  
}
 
msg+="</table><br><br> <a href='http://192.168.4.1/update'>Оновлення прошивки пристрою</a></div>";
msg+="<br>Speed limit sound "+String(maxspeed);
msg+="</body>";
 
server.send(200, "text/html", msg);
 tout=0;
}



void httpsetup()
{
  String message= F("<head><meta http-equiv=\"refresh\" content=\"3;URL=/\" /></head><body>");  
 
  for (int i=0; i < server.args(); i++){
  if (server.argName(i)=="sl") {
    String val=server.arg(i);
    message += " speed : " + val + "\n"; 
    maxspeed=byte(val.toInt());
    EEPROM.write(1, maxspeed);EEPROM.commit();
    }
 }
 server.send(200, F("text/html"), message);
 tout=0;
   }   



 
void handleNotFound() {
 String message = "File Not Found\n\n";
 server.send(404, "text/htmh", message);
 tout=0;
}


void beep()
{
for (int i=0;i<5;i++){
 digitalWrite(2,0);
 delay(70);
 digitalWrite(2,1);
 delay(50);
 }
 bn=2;

tout=0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2,0);
  delay(300);
  Serial.println("Serial begin");
  EEPROM.begin(64);
  maxspeed=byte(EEPROM.read(1));
  
  digitalWrite(2,1);
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  uint32_t chipid = 0;
  for (int i = 0; i < 17; i = i + 8)
     chipid |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  char ap_ssid[25];
  snprintf(ap_ssid, 26, "Chery_ev-%08X", chipid);
  WiFi.softAP(ap_ssid);
 

    Serial.println("\n\nWiFi parameters:");
    Serial.print("Mode: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
    Serial.print("IP address: ");
    Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());
    
	ESP32Can.setPins(CAN_TX, CAN_RX);
  ESP32Can.setRxQueueSize(5);
	ESP32Can.setTxQueueSize(5);
  ESP32Can.setSpeed(ESP32Can.convertSpeed(500));
  if(ESP32Can.begin()) {
        Serial.println("CAN bus started!");
    } else {
        Serial.println("CAN bus failed!");
    }

  if(ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX, CAN_RX, 10, 10)) {
        Serial.println("CAN bus started!");
    } else {
        Serial.println("CAN bus failed!");
    }

 
  server.on("/", handleRoot);
  
  server.on("/update", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
    tout=0;
    });
  server.on("/set",httpsetup);  
  server.on("/doupdate", HTTP_POST, []() {
      tout=0;
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", (Update.hasError()) ? "FAIL" : "<body>All OK <br><br> <a href='http://192.168.4.1/'>Return to main </a></body>");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin()) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      } else {
        Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
      }
    });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
 
  dnsServer.start(53, "*", apIP);
     
 
 delay(500);
 bn=1;
}






 
void loop() {

   delay(1);
 

 
   server.handleClient();
   dnsServer.processNextRequest();
   
  
   if ((tout<121000 ) && (tout>120000)) { //Timeout for wifi off
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);  
      tout=122000;
   }
   if (tout<121000 ) tout++; //Timeout for wifi off
 
   if (bn==1) beep();
   while (ESP32Can.readFrame(rxFrame, 1)) {
   if(rxFrame.identifier == 0x318) {
    vspeed=(rxFrame.data[3]*256+rxFrame.data[4])/100;
    
    if ((vspeed>maxspeed) && (bn==0)) bn=1;
    if ((vspeed<maxspeed-3) && (bn==2)) bn=0;
    }

   if(rxFrame.identifier == 0x46c) {   
          maxvolt=rxFrame.data[0]*256+rxFrame.data[1];
          minvolt=rxFrame.data[2]*256+rxFrame.data[3];
        }

   if(rxFrame.identifier == 0x469) {   
          strval="";
          v1=rxFrame.data[0]*256+rxFrame.data[1];
          v2=rxFrame.data[2]*256+rxFrame.data[3];
          v3=rxFrame.data[4]*256+rxFrame.data[5];
          v4=rxFrame.data[6]*256+rxFrame.data[7];
        }
   
   if ((rxFrame.identifier>0x540) && (rxFrame.identifier<0x558)){
    int mp=(rxFrame.identifier-0x541)*4;
    batvolt[mp+1]=rxFrame.data[0]*256+rxFrame.data[1];
    batvolt[mp+2]=rxFrame.data[2]*256+rxFrame.data[3];
    batvolt[mp+3]=rxFrame.data[4]*256+rxFrame.data[5];
    batvolt[mp+4]=rxFrame.data[6]*256+rxFrame.data[7];    
   }
        
 } // end can rx
 
}
