import time
import requests
import sys
import Adafruit_DHT

TOKEN = "……"  # TOKEN'i buraya yapistirin
DEVICE_LABEL = "cihaz_MIDEP"  # cihaz etiketini yazin
VARIABLE_LABEL_1 = "sicaklik"  # birinci degiskeni olusturun
VARIABLE_LABEL_2 = "nem"  # ikinci degiskeni olusturun.

def build_payload(variable_1, variable_2):
    # DHT 11 sensorunden verileri alma
    humidity, temperature = Adafruit_DHT.read_retry(11, 4)

    payload = {variable_1: humidity,
               variable_2: temperature}
    return payload

def post_request(payload):
    # HTTP request portokolu olusturulur
    url = "http://industrial.api.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, DEVICE_LABEL)
    headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}

    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, json=payload)
        status = req.status_code
        attempts += 1
        time.sleep(1)

    # islem sonucu goruntuleme
    print(req.status_code, req.json())
    if status >= 400:
        print("[ERROR] veri gönderilemedi!")
        return False

    print("[INFO] istek gönderildi, cihaz guncellendi!")
    return True

def main():
    payload = build_payload(
        VARIABLE_LABEL_1, VARIABLE_LABEL_2)

    print("[INFO] veri gonderiliyor.")
    post_request(payload)
    print("[INFO] tamamlandı")

if __name__ == '__main__':
    while (True):
        main()
        time.sleep(1)
