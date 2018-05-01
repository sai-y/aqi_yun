import requests
import configparser
import os

KEY_FILE = "/root/key.ini"
def get_key():
	config = configparser.ConfigParser()
	if os.path.isfile("/root/key.ini"):
		config.read(KEY_FILE)
		return config.get("TOKEN", "API_KEY")


if __name__ == "__main__":
	api_key = get_key()
	print(api_key)
