# İnternet üzerinden Midep GPIO pinlerinin kontrolü

Öncelikli uygulamalarda gerçekleştirdiğimiz üzere MİDEP kartına bağlı sensörlerden alınan verilerin internet ortamında izlenebileceği gibi, internetten de MİDEPkartına veri göndermek ve gpio pinlerine erişerek çevresel birimleri (LED, Motor vb.) kontrol etmek mümkündür.

Bu uygulamada popüler bir bulut platformu olan [adafruit.io](https://io.adafruit.com) uygulamasında oluşturulan bir buton ile MİDEP kartının gpio pinlerini kontrol edeceğiz.

**Gerekli malzemeler**

* MİDEP

* LED (1 adet)

* 220 Ohm direnç (1 adet)

**Devre kurulumu**

![resim](https://user-images.githubusercontent.com/44734477/183297777-fd1ae57c-0f3b-4152-9313-ab04894cf204.png)

### Adafruit IO

Adafruit IO, internet üzerinden verileri görüntülemek, yanıtlamak ve etkileşim kurmak için tasarlanmış bir bulut platformudur.

Platformu kullanmak için öncelikle https://io.adafruit.com/ adresine giderek üye olun. İstenilen bilgileri doldurup üyeliğinizi tamamladıktan sonra hesabınıza giriş yapın.

![resim](https://user-images.githubusercontent.com/44734477/183297788-606838b3-e7d4-455d-9340-378f2f762da2.png)

Hesabınıza giriş yaptıktan sonra **IO** sekmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297792-f3726d5d-85db-4344-a7dc-c900e406c462.png)

Midep kartının Adafruit ile iletişim kurabilmesi ve veri gönderebilmesi için üç önemli parametre vardır.

1. Username

2. AIO Key (Active Key)

3. Feed key

İlk iki parametreye “**Dashboards** (Pano sayfası)” kısmında “**My Key**” sekmesinden erişebilirsiniz.

![resim](https://user-images.githubusercontent.com/44734477/183297800-77f500bb-cdc3-47e0-925a-dfc263c65b5c.png)

Açılan pencerede “**username**” ve “**AIO key (Active Key)**” değerlerinizi görebilirsiniz. Python programını yazarken bu değerleri gireceksiniz.

![resim](https://user-images.githubusercontent.com/44734477/183297804-d3bd3a7e-3b74-4962-8b58-cdbcf400f786.png)

“Username” ve “Active Key” MİDEP kartınızın adafruit IO hesabına bağlanması ile ilgilidir ve python programında ilgili yere yazılması gerekir.

MİDEP kartından adafruit platformuna veri göndermek ya da almak için ise “**feed**” oluşturmalısınız. Bunun için “**dashboards**” sayfasından “**Feeds**” sekmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297808-8164a8fd-24e5-46c3-ad7f-88b4a5616e23.png)

Açılan sayfada oluşturduğunuz feed’leri görebilirsiniz. Yeni feed oluşturmak ya da mevcut feed’leri kontrol etmek için “**view all**” düğmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297818-7be74c0f-46d6-4db6-8a68-337afb642025.png)

Açılan sayfada, Yeni feed oluşturmak için “**New Feed**” düğmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297826-c882fcc8-a388-4731-974e-d102f435e5af.png)

Açılan pencerede feed adını yazın. İsterseniz Feed için kısa bir açıklamayı “**description**” bölümüne ekleyebilirsiniz. Ardından “**create**” düğmesine tıklayarak feed’i oluşturun.

![resim](https://user-images.githubusercontent.com/44734477/183297829-99cb7856-b032-4dc1-8b03-8e92b861a70c.png)

Oluşturduğunuz “**digital**” adlı feed, Feeds listenizde görülecektir. MİDEP kartınıza veri göndermek için bu feed’i kullanacaksınız. Bunun için “**Feed Key**” bilmeniz gerekir. Genellikle “**Feed Key**” feed’e verdiniz adın küçük harflerden oluşmuş versiyonudur. Yani feed adı “DIGITAL” ya da “digital” ise feed key “digital”’dir. Feed Key’i görmek için, “**digital**” adlı feed’in üstüne tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297835-eb136744-ae40-48be-afbd-2aaa470ffbf3.png)

Açılan sayfada **feed info**’ya tıklayarak Feed key’i öğrenebilirsiniz. Feed key’i python programında ilgili yere yazmanız gerekmektedir.

![resim](https://user-images.githubusercontent.com/44734477/183297843-77c7c645-89d4-4a15-84ae-522910b94d18.png)

![resim](https://user-images.githubusercontent.com/44734477/183297849-ce528d05-31d5-4d8f-b1f8-7b4b3f4f4d75.png)

Adafruit IO platformunda görsel bir buton öğesi oluşturmak ve “**digital**” adı feed’i bu butona bağlamak için sırasıyla **Dasboards > view all > New Dashboard** tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297859-a4282809-30e7-4f6a-bc88-249894b80c42.png)

![resim](https://user-images.githubusercontent.com/44734477/183297863-9577b198-f8cc-467b-a01c-8b958a913585.png)

![resim](https://user-images.githubusercontent.com/44734477/183297868-fd4da7f8-86a5-4739-aec3-b584b22f98e7.png)

Açılan pencereden Dashboard’a bir isim verin ve “**Create**” düğmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297874-8fc1d5d2-101f-4714-9f66-22db4aac9e31.png)

Dashboard sayfanızda oluşturduğunuz dashboard görünecektir. Dashboard’u ayarlamak için üzerine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297882-ffbea39f-c570-437a-a7f4-48ccd92b400a.png)

Açılan sayda, Buton oluşturmak için ayarlar kısmında “**create new block**” tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297887-eabc33f4-1fd5-4ce2-8569-c15a396a756f.png)

Açılan pencerede verilerinizi görselleştirmek için oluşturabileceğiniz blok listesi çıkacaktır. Buton oluşturmak için “**toggle**” görseli üzerine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297892-70f33879-5a8e-4da2-884e-66df0afcd8a6.png)

Ardından oluşturduğunuz bloğu feed ile ilişkilendirmek için listeden “**digital**” adlı feed’i seçin ve “**next step**” düğmesine basın.

![resim](https://user-images.githubusercontent.com/44734477/183297901-d6a7da54-72a9-46da-9d5a-11dfd57576ca.png)

Burada blok ismi ve butonun ON ve OFF durumlarında midep kartına göndereceği parametreleri belirleyin. ON durumu için “1”, OFF durumu için ise “0” yazın. Ardından “**create block**” düğmesine tıklayın.

![resim](https://user-images.githubusercontent.com/44734477/183297908-91d76b18-08fc-4a0d-af63-fe84bf96ad49.png)

Midep kartınızda terminal penceresini açın ve aşağıdaki komutu girerek adafruit IO kütüphanesini yükleyin.

`pip3 install adafruit-io`

Yeni bir python dosyası açın ve aşağıdaki program kodunu yazın.

> ***Program kodunda “username”, "AIO Key" ve "feed" kısımlarına yukarıda açıklandığı şekliye parametrelerinizi yazmayı unutmayın!***

```
import time
import digitalio # import Adafruit Blinka
import board
# import Adafruit IO REST client.
from Adafruit_IO import Client, Feed, RequestError

# Adafruit IO key'i yazin.
ADAFRUIT_IO_KEY = '...'

# Adafruit IO username'i yazin.
ADAFRUIT_IO_USERNAME = 'YOUR_AIO_USERNAME'

# REST istemcisinin bir örnegini olusturun.
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

try: # 'digital' adında bir feed varsa
    digital = aio.feeds('digital')
except RequestError: # yoksa 'digital' adında feed olustur.
    feed = Feed(name="digital")
    digital = aio.create_feed(feed)

# led set up
led = digitalio.DigitalInOut(board.D5)
led.direction = digitalio.Direction.OUTPUT

while True:
    data = aio.receive(digital.key)
    if int(data.value) == 1:
        print('received <- ON\n')
    elif int(data.value) == 0:
        print('received <- OFF\n')

    # LED'i feed degerine ayarla
    led.value = int(data.value)
    time.sleep(0.5)

```

Dosyayı kaydederek F5 tuşuna ya da terminal penceresinden `python3 <dosya adı.py>` komutunu çalıştırarak programı başlatın. 
Adafruit sayfasında dashboard’unuzda bulunan butonun konumunu değiştirdiğinizde MİDEP kartına bağlı LED’in açılıp kapandığını ve ekranda LED durumunun bildirildiğini göreceksiniz.
