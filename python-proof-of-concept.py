import requests
import json
import time
import math

data = {
    'sid': '000000',
    'timestamp': '',
    'bathroom-id': ''
}

data['timestamp'] = math.floor(time.time())
data['bathroom-id'] = data['timestamp'] % 5

print(f"Sending data: {data}")

r = requests.post('http://localhost:8000', data=data)
