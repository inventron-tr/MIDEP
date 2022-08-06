void setup() {
// seri iletişimi 9600 bits per second değerine ayarlıyoruz.
Serial.begin(9600);
}

void loop() {
// bu komut ile " " arasına yazdığımız mesajı ekranda görüntülüyoruz.
Serial.println("Hello World!");
delay(1000);
}
