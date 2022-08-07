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
