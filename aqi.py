#!/usr/bin/python

import requests
import configparser
import os
import datetime
import time
import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge')
from bridgeclient import BridgeClient as bridgeclient

KEY_FILE = "/root/key.ini"
URL = ("http://www.airnowapi.org/aq/observation/zipCode/current/"
       "?format=application/json"
       "&zipCode={0}&date={1}&distance=25&API_KEY={2}"
)
def get_key():
    config = configparser.ConfigParser()
    if os.path.isfile(KEY_FILE):
        config.read(KEY_FILE)
        return config.get("TOKEN", "API_KEY")
    else:
        return None


if __name__ == "__main__":
    api_key = get_key()
   
    value = bridgeclient()
    
    date = str(datetime.date.today())

    
    zip_code = value.get("ZIP")
    
    if zip_code is not None:
        print(zip_code)
        value.delete("ZIP")

        try:
            response = requests.get(URL.format(zip_code, date, api_key))
        except requests.exceptions.RequestException as e:  # This is the correct syntax
            print e
        else:
            body = response.json()

            larger_value = 0
            for item in body:
                level = item['Category']['Number']
                if level > larger_value:
                    larger_value = level
                value.put("LEVEL", "L" + str(larger_value))

            
    value.close()

        
    
