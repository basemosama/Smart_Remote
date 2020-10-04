# Smart Remote
An APP to turn on or off Devices by using Esp8266 Wifi Module.

# Esp8266 By URL Setup
this Esp8266 code will send the data in the url.

# Setup
You should add your Wifi SSID and Pasword on the arduino code .  
Then You should get the ip address of the Esp8266 Wifi Module   
like from the example arduino code .  
and then put it on the app settings .  

# How it Work 
The app will send data via WiFi to the Esp8266   
representing devices on 1 and 0  
the data will be like 11100  
the number of the data is the number of the devices  
1 means a device has been turned on  
0 means a device has been turned off  
you can change the number of devices on the arduino code.    

