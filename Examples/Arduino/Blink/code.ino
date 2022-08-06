/*
  Bu uygulamada MİDEP/Arduino üzerindeki 13. Pine bağlı yerleşik LED 1sn aralıklarla yakıp söndürülür. 
  Arduino kütüphanelerinde 13 numaralı pin LED_BUILTIN olarak da adlandırılır.
*/
 // Setup fonksiyonu Arduino sensor board başlatıldığında ya da resetlendiğinde sadece bir kere çalışır.
void setup() {
  // LED_BUILTIN pinini (13 numaralı pin) çıkış olarak ayarla.
  pinMode(LED_BUILTIN, OUTPUT);
}

// loop fonsiyonu sürekli çalışır.
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // LED’i yak (HIGH = +5V)
  delay(1000);                       // 1 sn bekle
  digitalWrite(LED_BUILTIN, LOW);    // LED’i söndür (LOW = 0V)
  delay(1000);                       // 1 sn bekle
}
