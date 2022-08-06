/* 
DHT sıcaklık ve nem sensörü uygulaması
Kaynak: Adafruit industries
Gerekli kütüphaneleri aşağıdaki linklerden indirebilirsiniz:
DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
Adafruit Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2   // DHT sensörün bağlandığı dijital pin numarası
#define DHTTYPE  DHT11   // DHT sensör tipi

DHT_Unified dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin(); // sensörü başlatma komutu
}
 
void loop() {
  //Ölçüm aralığındaki gecikme süresi
  delay(2000);

  // Sıcaklık ölçümü ve seri ekrana yazdırma
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Sicaklik olcumunde hata!"));
  }
  else {
    Serial.print(F("Sicaklik: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Nem ölçümü ve seri ekrana yazdırma
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Nem olcumunde hata!"));
  }
  else {
    Serial.print(F("Nem: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
