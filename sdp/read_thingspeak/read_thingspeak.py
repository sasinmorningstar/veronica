#!/usr/bin/env python

#import it all
import urllib2, json

READ_API_KEY = 'WM55CD04MWQ9500A'
CHANNEL_ID = 456085

# get data from cloud
def getdata():
    connt_speak = urllib2.urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" % (CHANNEL_ID,READ_API_KEY))
    response = connt_speak.read()
    data = json.loads(response)
    got_data = str(data['field1'])
    print 'the data:', got_data
    connt_speak.close()

def main():
    print 'working!!'
    getdata()

if __name__ == '__main__':
    main()
