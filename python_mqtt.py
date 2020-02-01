
# This python code gets the data of IMU through MQTT protocol and log the data into a csv file having name "Filename". 

import paho.mqtt.client as mqtt
import csv
import time

# Please change the file name below every time when you collect data for various tests otherwise it will enter the data
# in the same csv file in new line.

# Enter File name

Filename = 'Filename.csv'


with open(Filename, mode='a', newline='') as csv_file:

        now = time.strftime('%H:%M:%S')
        fieldnames = ['Time', 'AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ', 'MagX', 'MagY', 'MagZ']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames,delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        writer.writeheader()

        
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    # Below, Enter the topic name which you want to subscribe.
    
    client.subscribe("Enter topic name to subscribe")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    x=(" "+str(msg.payload)).rsplit()
    # extracting data of AccX and MagZ respectively
    z = x[0].split("b'")[1]               
    a = x[8].split("'")[0]
    
    with open(Filename, mode='a', newline='') as csv_file:

        now = time.strftime('%H:%M:%S')
        
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames,delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
       
        writer.writerow({'Time': now, 'AccX': z, 'AccY': x[1], 'AccZ': x[2], 'GyroX': x[3], 'GyroY': x[4], 'GyroZ': x[5], 'MagX': x[6], 'MagY': x[7], 'MagZ': a})
        print(now)
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Enter server name or IP address same as arduino code.
client.connect("Enter server address or IP ideress", 1883, 60)


# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
