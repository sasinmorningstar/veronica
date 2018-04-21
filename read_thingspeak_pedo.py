#!/usr/bin/env python
# import it all

import urllib2
import json
import time
from sklearn import tree

READ_API_KEY = 'AOTS2WX7AKJ4QXT8'
CHANNEL_ID = 480182


# get data from cloud
def getdata():
    connt_speak = urllib2.urlopen(
        "http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" % (CHANNEL_ID, READ_API_KEY))
    response = connt_speak.read()
    data = json.loads(response)
    steps_to_clorie(int(data['field1']))
    connt_speak.close()


# finds out calories burned form steps taken
def steps_to_clorie(steps):
    weight = raw_input("Enter weight (in lbs): ")
    calories_intake = raw_input("Enter daily calorie intake: ")
    calories_burned = ((0.57 * int(weight)) / 2200) * steps
    predict(int(calories_intake), calories_burned)


# this part predicts the health state
def predict(intake, burned):
    features = [[3000, 2000], [1400, 1500], [3000, 3000], [10000,9000]]  # dummy data set format--> [intake,burned]
    labels = [1, 2, 3, 1]
    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(features, labels)
    predict_val = clf.predict([[intake, burned]])
    if predict_val == 1:
        print 'You are eating more than burning!'
    elif predict_val == 2:
        print 'You are burning more than eating!'
    elif predict_val == 3:
        print 'Keep up the good work!'


def main():
    while True:
        getdata()
        time.sleep(20)  # wait for Thingspeak to update, default time is 15s


if __name__ == '__main__':   # std. boiler plate
    main()
