# Python ile bulut platformuna (Ubidots) veri gönderme

Pythonn programlama dilinde yer alan kütüphaneler kullanılarak bulut platformları ile kolaylıkla iletişim kurulabilir. Böylelikle sensörlerden elde edilen veriler gerçek zamanlı olarak internet üzerinden takip edilebiliriz. Aynı zamanda internet üzerinden de cihazların çevre birimlerine erişip bu birimlerin kontrolü sağlayabiliriz. 

Cihazların birbirleri ile ya da son kullanıcı ile haberleştikleri bu teknolojiyi nesnelerin interneti (IoT- Internet of things) olarak adlandırıyoruz. Ubidots, IoT uygulamalarında verilerin internette izlenmesi ve cihazlar ile etkileşim kurma konusunda kullanımı kolay ve kapsamlı bir bulut platformudur.
Bu uygulamada python ile “sicaklik” ve “nem” olarak iki değişkene rasgele sayılar atayacağız ve bu sayıları ubidots platformu üzerinde görüntüleyeceğiz.

### Ubidots nasıl çalışır?

Geliştirme kartına bağlı sensörlerden gelen veri her güncellendiğinde, bir veri noktası (dots) oluşturulur. Ubidots, cihazlardan gelen bu “veri noktalarını” değişkenlerin içerisinde saklar. Ayrıca bu değişkenlerin her birine karşılık gelen bir zaman damgası oluşturulur.  Kısacası cihaz tarafından üretilen her veri ubidots platformu tarafında bir değişken içerisinde tutulur ve izlenir.

Ubdots ile veri alışverişi birçok protokol üzerinden gerçekleştirilebilir. Bu protokollerden biri de http protokolüdür.  http protokolü, istemci (MİDEP kartı, PC vs.) ile sunucu (Ubidots) arasında bir takım verileri çekip göstermek istendiğinde kullanılan bir iletişim yöntemidir. Günümüzde web/mobil uygulamaların çoğunda bu iletişim protokolü kullanılır. http protokolü request (istek) ve buna karşılık response (cevap) olmak üzere iki kısımdan oluşmaktadır. http request kendi içinde farklı metotlardan (GET, POST, PUT, DELETE, vb.) meydana gelir. 

Bu uygulamada POST metodunu kullanacağız. POST metodu belirtilen kaynağa bir veri (entity) göndermek için kullanılır, bu da genellikle sunucuda bir durum değişikliğine neden olur. Yani cihaz (MİDEP) tarafından üretilen veri http protokolü içerisinde bulunan POST metodu ile ubidots platformuna gönderilecek ve ubidots tarafında veri görselleştirilecektir.

Uygulamaya başlamadan önce ubidots platformunda hesap açmak gerekecektir.
Bunun için https://ubidots.com/ sitesinde gidip menüden “industries > stem” sekmesine tıklayın.
 
![resim](https://user-images.githubusercontent.com/44734477/183297437-6d58b2de-ab9a-4f8c-a3ec-d146944581d4.png)

Açılan sayda kullanıcı adı şifre bilgilerini girip, “My IoT project is for personal, non-commercial use.” Kutucuğunu tıklayarak üye olun.
 
![resim](https://user-images.githubusercontent.com/44734477/183297442-836845fb-8c70-4b57-8d4e-4b90b6787328.png)

Adresinize gelecek linke tıklayıp üyeliğiniz onaylandıktan sonra kullanıcı adı ve şifrenizi girerek sisteme giriş yapın.

**Programlama**

Öncelikle programda kullanılacak python “request” kütüphanesinin yüklenmesi için terminal penceresine aşağıdaki komutu yazıp enter’e basın.

`pip install requests`

Python IDLE açın. Yeni dosya oluşturun ve program kodunu yazın.
```
import time
import requests
import math
import random

TOKEN = "TOKEN'i buraya yapistirin"  
DEVICE_LABEL = "cihaz_MIDEP"  # cihaz etiketini yazin
VARIABLE_LABEL_1 = "sicaklik"  # birinci degiskeni olusturun
VARIABLE_LABEL_2 = "nem"  # ikinci degiskeni olusturun.

def build_payload(variable_1, variable_2):
    # 2 rasgele veri olusturulur
    value_1 = random.randint(-10, 50)
    value_2 = random.randint(0, 85)

    payload = {variable_1: value_1,
               variable_2: value_2}

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
Program kodunda `TOKEN = "..."`  kısmına ubidots tarafından size verilen Token numarasını kopyalayıp yapıştırın.

Token numarasını bulmak için ubidots sayfanızda sağ üst köşedeki profil resminizin üzerine ve ardından “API Credentals” sekmesine tıklayın.
 
![resim](https://user-images.githubusercontent.com/44734477/183297458-f887fd33-7845-4dfc-939b-02ecd01ecafd.png)

Açılan sekmeden Tokens kısmında yer alan default token numarasını “copy” düğmesine basarak kaydedin.
 
![resim](https://user-images.githubusercontent.com/44734477/183297464-fb217bd5-fd55-41c0-8112-84cb9b216b3c.png)

Token numarasını kopyaladıktan sonra program kodunda `TOKEN = "..."` satırında tırnak aralığı içerisine yapıştırın. 

Programı çalıştırın ve ubidots sayfanıza gidin. 

**"Devices > devices"** sekmesine tıkladığınızda pyhton programında cihaz olarak tanımladığınız cihazınızı ubidots üzerinde görüntüleyebilirsiniz.
 
 
![resim](https://user-images.githubusercontent.com/44734477/183297472-6cc74edc-b253-4046-b173-9986d96a246d.png)

![resim](https://user-images.githubusercontent.com/44734477/183297476-d037d746-bbb9-42d6-97de-389aee1bbaa8.png)


Sayfada görünen cihaz adının üzerine tıkladığınızda “cihaz_MİDEP” ten alınan verileri görebilirsiniz.
 
![resim](https://user-images.githubusercontent.com/44734477/183297483-4a2cf048-0d05-4b9d-b83f-20be2d48802f.png)

Sıcaklık ve nem verilerini ana sayfada görüntülemek için ise sol üst köşede yer alan ubidots butonuna tıklayarak “**dashboard**”unuza gidin. Açılan sayfada **“+”** simgesine ya da “**add new widget**” üzerine tıklayın.
 
![resim](https://user-images.githubusercontent.com/44734477/183297491-f97a0e9a-996d-4c1b-ad38-3e4af1a23a81.png)

Açılan pencerede “Line chart” seçin.

![resim](https://user-images.githubusercontent.com/44734477/183297494-e5c0e4fd-c578-4292-b950-77cd4ab269db.png)

 
Açılan pencerede “Name” kısmından grafiğinize isim verin. Ardından “add variable” düğmesine tıklayın. 
 
![resim](https://user-images.githubusercontent.com/44734477/183297503-b6f5f4e2-cd18-422d-b6cd-272681694627.png)

Açılan pencereden cihaz_MİDEP üzerine tıklayarak sicaklik verisini seçin.

![resim](https://user-images.githubusercontent.com/44734477/183297516-879851b3-d135-49c9-8dee-1f615d44e7c5.png)

 
Onayladıktan sonra sıcaklık verisi çizgi grafik olarak pano sayfanızda (dashboard) görünecektir. Benzer adımları dilediğiniz grafik biçiminde nem verisini görüntülemek için de yapabilirsiniz.
