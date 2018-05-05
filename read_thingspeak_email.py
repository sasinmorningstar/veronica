#!/usr/bin/env python
# import it all

import urllib2
import json
import time, smtplib

READ_API_KEY = 'J9MFLB8AL9UHXCVJ'
CHANNEL_ID = 488650

email_user = 'sunnyk14320@gmail.com'
email_send = 'somitsinha108@gmail.com'
sender_psw = 'ifraafreen'
 
threshold = 72 
str0 = "your heart rate is normal"
str1 = "your heart rate is abnormal"
# get data from cloud
def getdata():
    connt_speak = urllib2.urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" % (CHANNEL_ID, READ_API_KEY))
    response = connt_speak.read()
    data = json.loads(response)
    return data['field1']
    connt_speak.close()


def send_mail(body, user_addr, sender_addr, password):
   server = smtplib.SMTP('smtp.gmail.com',587)
   server.starttls()
   server.login(user_addr,password)
   server.sendmail(user_addr,sender_addr,body)
   server.quit()

def main():
    while True:
        val = getdata()
       # threshold = 72
        if val>threshold:
          send_mail(str1+val,email_user,email_send,sender_psw)
        else:
          send_mail(str0+val,email_user,email_send,sender_psw)
           
        
         
        send_mail(val, email_user, email_send, sender_psw) #send email
        time.sleep(20)  # wait for Thingspeak to update, default time is 15s


if __name__ == '__main__':   # std. boiler plate
    main()
