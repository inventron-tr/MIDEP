/* Meteoroloji istasyonu.
   Kaynak: Adafruit industries
   Gerekli kütüphaneleri aşağıdaki linklerden indirebilirsiniz:
   DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
   Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
   Adafruit_BusIO Lib: https://github.com/adafruit/Adafruit_BusIO
   Adafruit-GFX-Library Lib: https://github.com/adafruit/Adafruit-GFX-Library
   Adafruit_SSD1306 Lib: https://github.com/adafruit/Adafruit_SSD1306
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2   // DHT sensörün bağlandığı dijital pin
#define DHTTYPE  DHT11   // DHT sensör tipi
DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //I2C display adresi burada belirtilir.
  dht.begin(); // sensörü başlatma komutu
  display.clearDisplay(); // Ekranı temizler
  display.setTextSize(1,2); // karakter büyüklüğü bu komut ile belirlenir.
  display.setTextColor(SSD1306_WHITE); // Karakter rengi bu komut ile belirlenir.
}

void loop() {  
  delay(2000); //Ölçüm aralığındaki gecikme süresi
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  // Sıcaklık ölçümü ve ekrana yazdırma
  sensors_event_t event;
  dht.temperature().getEvent(&event);
 
  if (isnan(event.temperature)) {
    display.println(F("Sicaklik olcumunde hata!"));
  }  else {
    display.print(F("Sicaklik: "));
    display.print(event.temperature);
    display.println(F("C"));
  }
  // Nem ölçümü ve ekrana yazdırma
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    display.println(F("Nem olcumunde hata!"));
  }  else {
    display.print(F("Nem: "));
    display.print(event.relative_humidity);
    display.println(F("%"));
  }
  display.display();
}
