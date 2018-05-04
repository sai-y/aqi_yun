import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge')
from bridgeclient import BridgeClient as bridgeclient


if __name__ == "__main__":
	value = bridgeclient()

	key = value.get("LEVEL")

	if key is not None:
		value.delete("LEVEL")

	value.close()