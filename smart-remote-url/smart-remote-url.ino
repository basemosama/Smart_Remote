#include <ESP8266WiFi.h>
const char* ssid = "Your SSID";
const char* password = "Your Password";
WiFiServer server(80);
//Change the pins you are using here 
int myPins[]={5,4,0,2,14,12,13,15};
// Change the No of devices to the same number of devices on the app 
int noOfDevices=7;

String data;
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
  server.begin();
}
void loop() {
WiFiClient client = server.available();
  if(client){
//Getting data from the app and converting it to char arry 
String text=client.readStringUntil('\n');
text.remove(0,5);
text.remove(noOfDevices,text.length());
if(text!="favic"){
/*data will be like 11100
 *the number of the data is the number of the devices
 *1 means a device has been turned on
 *0 means a device has been turned off
 */
data=text;
Serial.println(data);

//Change state of the pins
for (int i=0;i<noOfDevices;i++) {
    if (data[i]=='0'){
       digitalWrite(myPins[i],0);
       Serial.print("pin ");
       Serial.print(i);
       Serial.println(" off");
     }
   else if(data[i]=='1'){
       digitalWrite(myPins[i],1);
       Serial.print("pin ");
       Serial.print(i);
       Serial.println(" on");

         }
   
       }
       /*------------Sending to the APP that the device state has changed--------------*/

       client.println("HTTP/1.1 200 OK");
       client.println("Content-Type: text/html");
       client.println("");
       client.print("success");

}

client.flush();  
}
}
