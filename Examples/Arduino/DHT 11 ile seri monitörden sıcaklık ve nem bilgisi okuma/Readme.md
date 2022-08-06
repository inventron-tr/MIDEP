Ortam sıcaklığı ve nem bilgisinin ölçülmesi, meteorolojik verilerin toplanmasından ev otomasyonuna kadar birçok uygulamada kullanılabilmektedir. Bu uygulamada sıcaklık ve nem yüzdesini ölçen bir sensor (DHT-11) ile Arduino sensor kartını kullanarak sıcaklık ve nem bilgisinin ekranda (serial monitör) görüntülenmesi sağlayacağız. 

**Gerekli malzemeler**

* Arduino sensor kartı

* DHT-11 ısı ve nem sensoru

#### DHT-11 ısı ve nem sensoru

Nem, etrafınızdaki hava ile karışan su buharıdır ve yüzde olarak ölçülür. Yani, eğer nem yüzde 60 ise (ki bu ortalama nemdir), o zaman etrafımızdaki havanın yüzde 60'ı su buharıdır. DHT-11 sensoru dijital olarak sinyal veren bir sıcaklık ve nem algılayıcıdır. İçeriğinde bulunan 8 bit’lik bir mikroişlemci ile algıladığı sıcaklık ve nem bilgisini dijital sinyale dönüştürür. 0 ile 50°C arasında 2°C hata payı ile sıcaklık ölçen birim, 20-90% RH (Relative humidity) arasında 5% RH hata payı ile nem yüzdesini ölçer. DHT-11 modülü, 5V, data ve GND pinleri üzerinden karta bağlanır. Data pini Arduino shield üzerinde bulunan herhangi bir sayısal pine bağlanabilir.

![resim](https://user-images.githubusercontent.com/44734477/183248212-5634434a-1259-42a4-8667-1d1f99453e16.png)

**Devre kurulumu**

Uygulama için aşağıda verilen şekilde devreyi kuruyoruz.

![resim](https://user-images.githubusercontent.com/44734477/183248215-36c6a7e7-83a1-4f62-8256-ba4bcf2cffd3.png)


**Programlama**

Arduino IDE’ye “Adafruit_Sensor.h” ve “DHT.h” kütüphanelerini ekleyin. Bu kütüphaneleri aşağıdaki linklerden edinebilirsiniz.

https://github.com/adafruit/Adafruit_Sensor

https://github.com/adafruit/DHT-sensor-library
