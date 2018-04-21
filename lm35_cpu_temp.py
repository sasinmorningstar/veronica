#!/usr/bin/env python
__author__ = 'dave'

import httplib, urllib
import time
import serial
sleep = 30 # how many seconds to sleep between posts to the channel
key = 'YZ4W4OTFVIVH6YKU'  # Thingspeak channel to update

#Report Raspberry Pi internal temperature to Thingspeak Channel
def thermometer():
    ser = serial.Serial('/dev/ttyACM0',9600)
    temp = ser.readline()
    while True:
        #Calculate CPU temperature of Raspberry Pi in Degrees C
        #temp = int(open('/sys/class/thermal/thermal_zone0/temp').read()) / 1e3 # Get Raspberry Pi CPU temp
        params = urllib.urlencode({'field1': temp, 'key':key }) 
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        try:
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print temp
            print response.status, response.reason
            data = response.read()
            conn.close()
        except:
            print "connection failed"
        break
#sleep for desired amount of time
if __name__ == "__main__":
        while True:
                thermometer()
                time.sleep(sleep)
