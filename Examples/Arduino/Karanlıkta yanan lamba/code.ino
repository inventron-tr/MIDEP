int LED = 5; //5.Pinde LED olduğu tanımlandı.
int sensor_pin = A3; //A3 Pininde ışık sensörü olduğu tanımlandı.
int sensor_durum = 0; 

void setup() { 
  pinMode(LED,OUTPUT); 
  Serial.begin(9600); //Seri haberleşme başlatıldı.
  digitalWrite(LED,LOW); 
}

void loop() {
  sensor_durum = analogRead(sensor_pin); //A3 pinindeki değer sensor_durum değişkenine atandı.
  Serial.println(sensor_durum); //Okunan değer seri monitöre yazdırıldı.
  delay(50);
  if(sensor_durum > 150)
  {  //sensorün üzerine düşen ışık değeri 150'den büyük ise LED yanmasın.
     digitalWrite(LED,LOW); 
  }
 if(sensor_durum < 150)
  {  // sensorün üzerine düşen ışık değeri 150'den küçük ise LED yansın.
     digitalWrite(LED,HIGH); 
  }
 }
