# Ubidots ile sıcaklık ve nem verilerinin internetten izlenmesi

[Pyhton ile bulut platformuna (ubidots) veri gönderme](http://support.inventron.com.tr/forum/t/nesnelerin-interneti-uygulamalari-2-python-ile-bulut-platformuna-ubidots-veri-gonderme/56?u=murattamer) uygulamasında, python programında “sicaklik” ve “nem” adlı değişkenlere rasgele sayılar atanarak ubidots platformu üzerinde gözleniyordu. Bu uygulamada ise “sicaklik” ve “nem” değişkenlerine DHT 11 sensöründen gelen verileri atayarak internet üzerinden izlenmesini sağlayacağız.

> **Uygulamaya başlamadan önce**
> 
> DHT 11 sensörü ve nem kavramı için [DHT 11 ile seri monitörden sıcaklık ve nem bilgisi okuma](http://support.inventron.com.tr/forum/t/arduino-ile-programlama-6-dht-11-ile-seri-monitorden-sicaklik-ve-nem-bilgisi-okuma/49?u=murattamer),
> 
> Ubidots platformunun kullanımı ve ubidotsa veri gönderme adımları için ise [Pyhton ile bulut platformuna (ubidots) veri gönderme](http://support.inventron.com.tr/forum/t/nesnelerin-interneti-uygulamalari-2-python-ile-bulut-platformuna-ubidots-veri-gonderme/56?u=murattamer) başlığını inceleyebilirsiniz.

**Devre kurulumu**

Gerekli malzemeler

* MİDEP

* DHT 11 sıcaklık ve nem sensörü

Devreyi aşağıdaki görselde verilen şekliyle kurun.

![resim](https://user-images.githubusercontent.com/44734477/183297657-1ec84f8e-05b5-4830-a8e2-2ce133e35f5b.png)


**Programlama**

Uygulamamızda Adafruit DHT11 Python kütüphanesini kullanacağız.

Bu kütüphaneyi Github üzerinden indirebilirsiniz. Eğer MİDEP kartınızda Git yüklü değilse, terminal penceresine şu komutu yazın.

`sudo apt-get install git-core`

Eğer komutu çalıştırdığınızda hata alırsanız, aşağıdaki komutu çalıştırıp tekrar deneyin.

`sudo apt-get update`

Kütüphaneyi indirmek için terminal penceresinden aşağıdaki komutu çalıştırın.

`git clone https://github.com/adafruit/Adafruit_Python_DHT.git`

Aşağıdaki komut ile kütüphane klasörüne gidin

`cd Adafruit_Python_DHT`

Kütüphaneyi kurun


```
sudo apt-get install build-essential python-dev

sudo python setup.py install
```

Python IDLE açın. Yeni dosya oluşturun ve program kodunu yazın.

Program kodunda `TOKEN = "..."` kısmına ubidots tarafından size verilen Token numarasını kopyalayıp yapıştırın.

> Bu işlem için detaylı açıklamayı “[Pyhton ile bulut platformuna (ubidots) veri gönderme](http://support.inventron.com.tr/forum/t/nesnelerin-interneti-uygulamalari-2-python-ile-bulut-platformuna-ubidots-veri-gonderme/56?u=murattamer)” başlığı altında altında bulabilirsiniz.

```
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

```

Programı çalıştırın, ardından ubidots platformunda “**devices**” kısmından verileri izleyebilirsiniz.

Dilerseniz pano sayfasından (**Dashboard**) verileri çeşitli grafikler üzerinde görüntüleyebilirsiniz.
