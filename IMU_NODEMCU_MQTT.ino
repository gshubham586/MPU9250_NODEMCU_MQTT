
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <MPU9250.h>

const char* ssid = "Enter wi-fi SSID";                            // Enter wi-fi SSID/Name
const char* password = "Eneter wi-fi password";                   // Enter wi-fi password

const char* mqttServerIP = "Enter server name or IP address";     // Enter server IP or localhost IP address (If you are using a local mqtt broker). To get your local host IPv4 address type
                                                                  // ipconfig in command prompt in windows OS and you will get IPv4 address of your PC. 
const int mqttPort = 1883;                                        // Port for MQTT protocol

WiFiClient espClient;
PubSubClient client(espClient);

MPU9250 IMU(Wire,0x68);                                  // Register address for I2C communication
int status;

int i=1;
String datasensor;      

char* Topic = "Enter the topic name";                    // Write topic name to publish

void reconnect(){                                        // Function to connect MQTT broker
  
  while(!client.connected()){                            // MQTT Begin
    
    Serial.println("Connecting to MQTT Server..");
    Serial.print("IP MQTT Server : "); Serial.println(mqttServerIP);

    bool hasConnection = client.connect("IMU");         // Connecting to MQTT broker (IMU is client name)
    if(hasConnection){
      
      Serial.println("Success connected to MQTT Broker");
    } else {
      
      Serial.print("Failed connected");
      Serial.println(client.state());
     
      delay(2000);
      Serial.println("Try to connect...");
    }
  }
  client.publish(Topic, "Reconnecting");
}


void setup() {
  
  Serial.begin(74880);                                           // You can change Baud rate to obtain the MPU9250 data at the different rates. (For example when baud rate
                                                                 // is set to 9600, it gives approx 10 data per second.)
  pinMode(LED_BUILTIN, OUTPUT);                      
 
  Serial.print("Connecting to ");
  Serial.println(ssid);                                   
  WiFi.begin(ssid, password);                                     // Connecting to wi-fi
  while (WiFi.status() != WL_CONNECTED) {                 
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqttServerIP, mqttPort);
//  client.setCallback(callback);
  

 while(!Serial) {}

   
  status = IMU.begin();                                             // Starting communication with IMU (MPU9250)
  if (status < 0) {                                                 // If communication with MPU9250 is not established then inform the user
    
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);                        // setting the accelerometer full scale range to +/-8G 
 
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);                      // setting the gyroscope full scale range to +/-500 deg/s
  
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_92HZ);                // setting DLPF bandwidth to 92 Hz (For further details visit https://github.com/bolderflight/MPU9250)
  
  IMU.setSrd(4);                                                     // Here sampling frequency should be Double or more than Double of the DLPF Bandwidth to get accurate data and formula 
                                                                     // for sampling frequency is SF=1000/(SRD+1). So choose srd according to above DLPF Bandwidth.

}

char dataPublish[100];
void publishMQTT(char* topics, String data){
   data.toCharArray(dataPublish, data.length() + 1);
   client.publish(topics, dataPublish);
}

void loop() {
  
   if (!client.connected()) {
    reconnect();
  }
  if(!client.loop()){
    client.connect("ESP8266Client");
  }
  

 IMU.readSensor();                              // Reading Data From MPU9250 Sensor
float  GyroX = IMU.getGyroX_rads();             // Reading X-axis data of gyrometer.
float  GyroY = IMU.getGyroY_rads();             // Reading Y-axis data of gyrometer.
float  GyroZ = IMU.getGyroZ_rads();             // Reading Z-axis data of gyrometer.
float  AccX = IMU.getAccelX_mss();              // Reading X-axis data of Accelerometer.
float  AccY = IMU.getAccelY_mss();              // Reading Y-axis data of Accelerometer.
float  AccZ = IMU.getAccelZ_mss();              // Reading Z-axis data of Accelerometer.
float  MagX = IMU.getMagX_uT();                 // Reading X-axis data of Magnetometer.
float  MagY = IMU.getMagY_uT();                 // Reading Y-axis data of Magnetometer.
float  MagZ = IMU.getMagZ_uT();                 // Reading Z-axis data of Magnetometer.
 

// Data to send through nodemcu using mqtt protocol..
// Here String(var,6) is used because it gives the value of  "var" upto 6 place after decimal.

  datasensor = String(AccX,6)+"  "+String(AccY,6)+"  "+String(AccZ,6)+"  "+String(GyroX,6)+"  "+String(GyroY,6)+"  "+String(GyroZ,6)+"  "+String(MagX,6)+"  "+String(MagY,6)+"  "+String(MagZ,6);
  
  publishMQTT(Topic,datasensor);                // Publishing Data "datasensor" through MQTT   
          
  // Printing the Data on Serial Monitor.
  
  Serial.print(i);                              // Counting the No. of Data received
  Serial.print("\t");  
  Serial.print(AccX,6);
  Serial.print("\t");
  Serial.print(AccY,6);
  Serial.print("\t");
  Serial.print(AccZ,6);
  Serial.print("\t");
  Serial.print(GyroX,6);
  Serial.print("\t");
  Serial.print(GyroY,6);
  Serial.print("\t");
  Serial.print(GyroZ,6);
  Serial.print("\t");
  Serial.print(MagX,6);
  Serial.print("\t");
  Serial.print(MagY,6);
  Serial.print("\t");
  Serial.println(MagZ,6);
i++;
}
