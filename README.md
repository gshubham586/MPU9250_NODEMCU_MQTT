# MPU9250_ESP8266_MQTT

Here I have designed a system that can transmit Real-time-motion data of **MPU9250** at the different baud rates wirelessly and this data can be used remotely in various project according to your requirement and also real-time data logging can be performed in your PC.

## Modules used


### 1. MPU9250

The InvenSense MPU-9250 is a System in Package (SiP) that combines two chips: the MPU-6500 three-axis gyroscope and three-axis accelerometer;and the AK8963 three-axis magnetometer. The MPU-9250 supports I2C, up to 400 kHz, and SPI communication, up to 1 MHz for register setup and 20 MHz for data reading.
For further details about MPU9250 visit [here](https://www.invensense.com/download-pdf/mpu-9250-datasheet/).

 ### 2. ESP8266 Node MCU
The Node MCU is an open source firmware and development kit that helps you to prototype your IoT product with ArduinoIDE or in few Lua script lines.
It includes firmware which runs on the ESP8266 Wi-Fi SoC and hardware which is based on the ESP-12 module. 

## Installations

### 1. Installations to program NodeMCU with Arduino IDE

1. Open up the Arduino IDE.
2. Go to File -> Preferences -> Additional Boards Manager URLs and paste this URL http://arduino.esp8266.com/stable/package_esp8266com_index.json -> click OK
3. Close the IDE and open it up again.
4. Go to Tools -> Board (where you’d select your version of Arduino) -> Boards Manager,type and search for the ESP8266 and click Install. You now should be able to use the ESP8266    as an Arduino. Simply select the "NODEMCU 1.0(ESP-12E MODULE)" as your board with Port and you should be ready to code.
Now, with ESP8266 board installed to Arduino IDE, we can program NodeMCU using Arduino IDE directly.
#### Required Libraries in Arduino IDE:
**1.   ESP8266WiFi.h** 
**2. PubSubClient.h** 
 <Open Arduino IDE, Go to Sketch -> Include Library -> Manage Libraries , Type and search for "**PubSubClient**" by **Nick O'Leary** and install it.>
 **3. Wire.h**
 **4. MPU9250.h**
 <Go to Sketch -> Include Library -> Manage Libraries , Type and search for "**MPU9250**" by **Brian Taylor** and install it.>

### 2.Python

#### 1. Install python from [here](https://www.python.org/downloads/).

#### 2. Install paho-mqtt
Now you have to install paho python client.This code provides a client class which enable applications to connect to an MQTT broker to publish messages, and to subscribe to topics and receive published messages. you can visit [here](https://pypi.org/project/paho-mqtt/) for installation instructions.



## Connection of MPU9250 with NodeMCU

Connect pins of **MPU9250** with the pins of **Nodemcu** in the follwing manner:
SCL --- D1
SDA --- D2
VCC --- 3V3
GND --- GND

#### Setup :
1. Create a  **Wi-Fi  HOTSPOT** using your smartphone.
2. Now connect your PC with it using Wi-Fi.
3. Open **command prompt** and type  **ipconfig** and run to know your local ip address (This method is for **windows OS** PC. if you are not using windows operating system then search for methods to know your ip address.)
4. Now open the Arduino code and edit few lines of codes as per requirement.
5.  Now open python code and make few changes as per requirement.
6. Now upload the arduino code in ESP8266 Nodemcu via USB cable. And run the python code in your PC. A file with "**Filename**" will be generated in same folder where the python code is present. This file will contain the data of MPU9250.
