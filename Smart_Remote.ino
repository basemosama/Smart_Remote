#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SimpleTimer.h>

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";
ESP8266WebServer server;
//Change the pins you are using here 
int myPins[]={5,4,0,2,14,12,13,15};
// Change the No of devices to the same number of devices on the app 
int noOfDevices=7;
String data;
SimpleTimer timer;

void setup() {
  
for(int i=0;i<sizeof(myPins);i++){
  pinMode(myPins[i],OUTPUT);
  digitalWrite(myPins[i],0);
 }

  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/status",changeDeviceStatus);
  server.on("/timer",setTimer);
  server.on("/sync",syncData);
  server.onNotFound(handleNotFound);

  server.begin();
}
void loop() {
    server.handleClient();   
    timer.run();

}



void changeDeviceStatus(){
  data = server.arg("plain");
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, data);

  JsonArray jArray =doc.as<JsonArray>();
  for (int i=0;i<jArray.size();i++) {
  JsonVariant device =jArray[i] ;

   int id = device["id"] ;
   String name = device["name"] ;
   boolean status = device["status"];
   //This should refer to the pin set by the app which the device is connected to if you want you can use it if you set the pins correctly instead of the pins list
   int pin = device["pin"] ;
   Serial.print("Device id : ");
   Serial.print(id);
   Serial.print(" name : ");
   Serial.print(name);
   Serial.print(" status : ");
   String onOffText = status ? "on" : "off";
   Serial.println(onOffText);
   if(i<sizeof(myPins)){
   digitalWrite(myPins[i],status);}

  }
  server.send(200,"text/plain","Success");


}

void setTimer(){
    data = server.arg("plain");
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, data);
    JsonArray jArray =doc.as<JsonArray>();
  
    for (int i=0;i<jArray.size();i++) {
    
    JsonVariant device =jArray[i] ;

  int id = device["id"] ;
  String name = device["name"] ;
  boolean status = device["status"];
  int pin = device["pin"] ;
  long duration = device["time"] ;
  String timeText = device["timeText"];
  
if(duration) {
   Serial.print("Setting a Timer for Device id : ");
   Serial.print(id);
   Serial.print(" name : ");
   Serial.print(name);
   String onOffText = status ? "on" : "off";
   Serial.print(" to turn ");
   Serial.print(onOffText);
   Serial.print(" at ");
   Serial.print(timeText);
   Serial.print(" after : ");
   Serial.print(duration);
   Serial.println(" seconds ");
   if(i < sizeof(myPins)){
    int devicePin = myPins[i];
    int timerId = timer.setTimeout(duration * 1000, [=]{updateDeviceStatus( devicePin, status);});
    device["timerId"] =timerId;
       Serial.print(" timerId : ");
   Serial.println(timerId);
    }
    
}

  }

  String jsonData;
serializeJson(jArray, jsonData);
  server.send(200,"application/json",jsonData);
  doc.clear();

}




void updateDeviceStatus(int pin,boolean status)
{
    Serial.print("updating timer status fot pin : ");
   Serial.print(pin);
   Serial.print(" status : ");
      String onOffText = status ? "on" : "off";
   Serial.println(onOffText);
   
   digitalWrite(pin,status);
     server.send(200,"application/json","Timer success");

   }

   
void syncData(){
  data = server.arg("plain");
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, data);

  JsonArray jArray =doc.as<JsonArray>();
  for (int i=0;i<jArray.size();i++) {
  JsonVariant device =jArray[i] ;
   String name = device["name"] ;
   int pin = device["pin"] ;

   if(i < sizeof(myPins)){
    int devicePin = myPins[i];
   boolean status = digitalRead(devicePin);
       device["status"] =status;

   }
   }
    String jsonData;
serializeJson(jArray, jsonData);
  server.send(200,"application/json",jsonData);
  doc.clear();
  
  }

  
  void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

 
