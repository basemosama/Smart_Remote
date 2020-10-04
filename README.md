
# Smart Remote
This an Esp8266 Wifi module code to turn on or off Devices by using Smart Remote app.
you can download the app from here :


# Esp8266 Setup
The example Esp8266 code uses Arduino to program the Wifi Module .  
you will need to setup arduino to use the example.
you can follow the instructions in the link below  
https://github.com/esp8266/Arduino  

# Libraries
You will have to install these libraries 

 - [ ] **Arduino Json :** 
you can install it from library manger or from here 
 https://www.arduino.cc/reference/en/libraries/arduinojson/
 - [ ]  **SimpleTimer :**
 you will need to download it and put it in your arduio libraries folder from here :
 https://github.com/schinken/SimpleTimer

#### For More Informations on how to install the libraries you can follow this guide
https://www.arduino.cc/en/Guide/Libraries

# Setup
You should add your Wifi SSID and Pasword on the arduino code .  
Then You should get the ip address of the Esp8266 Wifi Module after running the code.  
and then update the app ip address on the app settings.  

# How it Work 
First the Esp8266 will create a local server that we will use to communicate with the app.
for each device it will be represtende in json and has the following properties :(id - name - status - pin) 
The server has 3 main routes we can use by sending POST requests and data will be sent and recived in json
```no-highlight
POST /status

Body json( json array of devices : ) like:
[
   {
      "id":1,
      "name":"led",
      "pin":0,
      "status":true
   },
   {
      "id":2,
      "name":"tv",
      "pin":0,
      "status":false
   },
   {
      "id":3,
      "name":"Pc",
      "pin":0,
      "status":true
   }
]

```
this method is responsible of changing the state of each device depending on the status of each device sent in the body of the request

```no-highlight
POST /timer Body json( json array of devices : ) like above
Response :
[
   {
      "id":1,
      "name":"led",
      "pin":0,
      "status":true,
	  "time":756,  
	  "timeText":"22:45",
	 "timerId":1
   },
   {
      "id":2,
      "name":"tv",
      "pin":0,
      "status":false
   },
   {
      "id":3,
      "name":"Pc",
      "pin":0,
      "status":true
   }
]
```
this method will set a timer for certain duration for each device that has a time value 
it will make the Esp8266 change the state of the device after this duration

```no-highlight
POST /sync  Body json( json array of devices : ) like previous requests
```
this will update the status of each device base on there pins 
and return back the devices with the updated state.


# Features of The app
You can turn on and off any device that connected to Esp8266 .  
Setting timer to turn on and off any of your devices .  
Turn On and Off all your devices with just one click.  
Add timer to Turn On and Off a device or all your devices.  

# ScreenShots 

Home Screen                                      |                  Adding Device                 |                   Editing Device                   |                 Adding Timer                     |                  Settings Screen                
:--------------------------------------------------:|:---------------------------------------------------:|:----------------------------------------------------:|:-------------------------------------------------:|:--------------------------------------------
<img src="https://lh3.googleusercontent.com/75-BTUdba6pUHIJGj69glQTYDzf8zosfpi4C2Vxm2-7JBvXtL5eRllwGz4zPwFkI_PkE=w1920-h937-rw" /> | <img src="https://lh3.googleusercontent.com/SERR1c4AGUDM1wyy4iIj-xjWSz24MxoAlIM1b-lnbcbkqG2M3r5aHBxyH7RKxZVZcTk=w1920-h937-rw" /> | <img src="https://lh3.googleusercontent.com/NPNdf_pVL_iEKinifRtrsCcz64nB5yj9B8IWNub5tcHGSQ3JeNy2AZ48AomNYuW1EA_W=w1920-h937-rw" /> | <img src="https://lh3.googleusercontent.com/bmkaJ5LiXwDsyu-G_x2knG5_cBCmUkLxJ_yL8MGpM1ZPvYlju9KAEFh_8L3CjSroLA=w1920-h937-rw" /> |<img src="https://lh3.googleusercontent.com/bl4mnTb94tkmLUmsLcv7ZiET_cbg31uPARiUdpmXrvHAGq4mEnTO_GH_3qrlWoc26Q7s=w1920-h937-rw" /> 