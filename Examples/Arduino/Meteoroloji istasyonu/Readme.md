# Meteoroloji istasyonu

Bu uygulamada DHT 11 sensöründen aldığımız sıcaklık ve nem değerlerini Arduino sensor kartı üzerinde bulunan OLED ekrana yazdıracağız. Böylelikle ortama ait sıcaklık ve nem verilerinin ekran üzerinden izlenebildiği küçük bir meteoroloji istasyonu oluşturacağız.

**Gerekli malzemeler**

* Arduino sensor kartı

* DHT-11 ısı ve nem sensoru

#### SSD1306 128x32 Display

Arduino sensor kartı üzerinde bulunan display ekran 128x32 çözünürlüğe sahiptir. I2C haberleşme protokolü ile Arduino ile haberleşir.

![resim](https://user-images.githubusercontent.com/44734477/183248859-561eeae0-e237-48b7-9dff-0a6aa09a85de.png)

**I2C haberleşme protokolü nedir?**

Arduino, diğer Arduino veya sensörlerle haberleşmek için bazı haberleşme protokolleri kullanır. Bu protokollerden birisi de I2C'dir. I2C (Inter-Integrated Circuit) protokolü bir ana (master) ve çoklu bağımlı (slave) cihazlardan oluşmaktadır. Böylelikle bir cihaz 1024 cihaz ile haberleşebilir. Bu nedenle Arduino dâhil bir çok mikrodenetleyici tarafından kullanılmaktadır. Bir diğer avantajı ise haberleşme sırasında sadece 2 pin (SDA ve SCL) kullanmasıdır.

![resim](https://user-images.githubusercontent.com/44734477/183248866-8f9084fb-6518-445c-b2c4-779e20d56789.png)

I2C iletişiminde her cihazın önceden ayarlanmış bir kimliği veya benzersiz bir cihaz adresi vardır, böylece master hangi cihazlarla iletişim kuracağını seçebilir. Bunun için SDA ve SCL pinlerini kullanır. SCL (Seri saat) hattı, I2C veri yolundaki cihazlar ile ana cihaz tarafından üretilen veri aktarımı arasında senkronize olan saat sinyalidir. Verileri taşıyan hat ise SDA hattıdır. Master ve slave cihazların aynı besleme hattına bağlanmasına gerek yoktur. Fakat iletişimin sağlanması için toprak hatlarının aynı olması gerekir.

**Devre kurulumu**

Uygulama için aşağıda verilen şekilde devreyi kuruyoruz.

![resim](https://user-images.githubusercontent.com/44734477/183248876-063b0618-09af-4243-8409-6627e50095cf.png)

**Programlama**

Program satırında #include komutu ile başlayan kütüphaneleri ekleyin. Bu kütüphaneleri aşağıdaki linklerden edinebilirsiniz.

* DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

* Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

* Adafruit_BusIO Lib: https://github.com/adafruit/Adafruit_BusIO

* Adafruit-GFX-Library Lib: https://github.com/adafruit/Adafruit-GFX-Library

* Adafruit_SSD1306 Lib: https://github.com/adafruit/Adafruit_SSD1306
