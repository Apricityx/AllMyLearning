import requests
import json


def send_data():
    url = 'http://localhost/api/login.php'
    raw_data = {'encrypted': 'MpJUYv68NoA7PLHT/+8WpX1G1KeTqqTUyZfWB74ZMbu0AuVcoZufWx2AK5uFJA8GzsmhQ8dm1oUyC9g6c0DpPQ=='}
    data = json.dumps(raw_data)
    # print(data)
    response = requests.post(url, data)
    return response.text


print(send_data())