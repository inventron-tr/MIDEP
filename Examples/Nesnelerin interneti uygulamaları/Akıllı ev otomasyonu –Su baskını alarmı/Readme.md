Akıllıı ev otomasyonu temelde aydınlatma kontrolü, enerji tasarrufu, güvenlik gibi evin birçok ihtiyacının uzaktan cihazlarla ya da sistemin kendi kendisine gerçekleştirmesi olarak tanımlanabilir. Bu örnekte ev içerisinde bir su baskını meydana geldiğinde alarmın çalacak ve kullanıcıya e-mail üzerinden bildirim yapılacak bir sistem kuracağız.

> **Sıvı seviye sensörü nedir?**
> 
> Sensör, sığ su seviyelerinde ve yağmurlu ortamda kullanılmaktadır. 40 mm su seviyesine kadar ölçüm yapabilmektedir. Sensörün yapısında birbirine paralel olarak bağlanmış iletken hatlar bulunmaktadır. Bu hatlar su ile temas ettiğinde MİDEP/Arduino kartına analog bir sinyal gönderir. Sensör 5V gerilim ile çalışmaktadır. 3 pini bulunmaktadır. + pinine besleme gerilimi olan 5V, – pinine GND bağlantısı yapılır. S pini ise sinyal (data) pini olduğundan dolayı MİDEP/Arduino kartının Analog pinlerinden birine bağlanabilir.
> ![resim](https://user-images.githubusercontent.com/44734477/183297211-5d57ee23-c04d-4cd0-9020-80b233bcb051.png)


Bu uygulamayı MİDEP kartınız ile gerçekleştirmek son derece kolaydır. Ancak burada sistemin iki önemli aşamadan oluştuğunu anlamak gerekir.

1. Su seviyesinin ölçümü: Su seviyesinin ölçümü arduino sensor kartına bağlı bir sıvı seviye sensörü tarafından gerçekleştirilir. Ölçüm sonuçlarına göre kritik seviye aşıldığında buzzer alarm çalar ve serial monitore bildirim yapılır. Örneğimizde su seviyesi aşıldığında serial monitore "1" aksi durumda ise "0" yazdırılmaktadır.

2. E-mail gönderimi: kritik seviye aşıldığında Python dilinde yazdığımız program ile kullanıcıya e-mail göndereceğiz. Bunun için python dilinde yazdığımız program sürekli olarak serial monitördeki değeri izlemelidir. Serial monitorde "1" değerini gördüğünde mail göndermelidir (su seviyesi aşıldığında serial monitore "1" aksi durumda ise "0" yazdırılmaktadır).

**Gerekli malzemeler**

* Arduino sensor kartı

* Sıvı seviye (yağmur) sensörü

* Buzzer

* Direnç (220 Ohm)

![resim](https://user-images.githubusercontent.com/44734477/183297222-5f92506c-f430-490a-9ed5-ea8e89eaec28.png)


**Arduino programlama**

Aşağıda verilen program kodunu arduino sensor kartına yükleyin ve sıvı seviyesine göre serial monitorde görünen değeri takip edin.

```
// python arduino haberleşme

int sensorPin = A0; //Sensörü bağlayacağımız pin
int esikDegeri = 100; //Su miktarı için eşik değeri
int buzzerPin = 8; //Buzzer'ı bağlayacağımız pin
int veri; //Sensörden okuduğumuz değer

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);  
}

void loop() {
  veri = analogRead(sensorPin); //Sensörden analog veriyi okuyoruz.
  if (veri > esikDegeri) { //Sensör verisi eşik değerini geçerse;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    Serial.println(1);
  } else { //Sensör verisi eşik değerinden küçük olursa;
    digitalWrite(buzzerPin, LOW);
    Serial.println(0);
  }
}

```

**Python programlama**

Python program kodunu yazmadan önce öncelikle lprogramda kullanacağımız kütüphaneleri kurmamız gerekmektedir. bunun için terminal penceresini açın ve aşağıdaki komutları yazarak "Serial" ve "Schedule" kütüphanelerini kurun.

`pip install schedule`

`pip install serial`

Kütüphaneleri yükledikten sonra Python IDLE açarak aşağıdaki program kodunu yazın.

```
import serial
import time
import schedule
import smtplib
 
def main_func():
    arduino = serial.Serial(port='/dev/ttymxc2', baudrate=9600)
    print('Arduino ile seri iletisim basladi')
    arduino_data = arduino.readline()
    decoded_value = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    
    if decoded_value[0] == '1':
        print(decoded_value[0])
        
        sent_from = gmail_user
        to = ['...@gmail.com']
        subject = 'Su baskini alarmi'
        body = 'Dikkat!! Evinizde su baskini tehlikesi algilandi. Lutfen kontrol ediniz.'
        
        email_text = """\
        From: %s
        To: %s
        Subject: %s
        %s
        
        """ % (sent_from, ", ".join(to), subject, body)
        try:
            smtp_server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
            smtp_server.ehlo()
            smtp_server.login(gmail_user, gmail_password)
            smtp_server.sendmail(sent_from, to, email_text)
            smtp_server.close()
            print ("Email basari ile gonderildi!")
        except Exception as ex:
            print ("Email gonderiminde hata….",ex)

    arduino_data = 0
    arduino.close()
    print('baglanti sonlandi')
    print('<------------------------------------->')
 
gmail_user = '...@gmail.com'
gmail_password = '…'
 
print ('program basladi')
 
schedule.every(20).seconds.do(main_func)
 
while True:
    schedule.run_pending()
    time.sleep(1)


```

Yukarıdaki programda öncelikle gönderici ve alıcı mail bilgilerini girmemiz gerekmektedir. Gönderici mail bilgileri için programda yer alan aşağıdaki satırlara gönderici gmail adresini ve şifresini girin.


```
gmail_user = '...@gmail.com'

gmail_password = '…'
```

Ardından aşağıdaki satırda alıcı mail adresini yazın.

`to = ['...@gmail.com']`

> Gönderim yapacağınız mail adresi için gmail ayarlarında en düşük güvenlik düzeyini ayarlamanız gerekmektedir. Bu nedenle bu uygulama için ayrı bir gmail hesabı oluşturabilirsiniz.

Programı çalıştırın. Eğer sensor kritik su seviyesinin aşıldığını algılar ve serial monitore "1" mesajı gönderirse program, alıcı mail adresine uyarı bildirimi gönderecektir.
