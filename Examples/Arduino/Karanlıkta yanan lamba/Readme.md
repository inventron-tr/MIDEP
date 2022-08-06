Akıllı şehir uygulamalarında ve akıllı ev sistemlerinde özellikle enerji tasarrufu sağlamak için aydınlatma sistemleri ortamdaki ışığa göre çalışabilmektedir. Ortamdaki ışık belirli bir seviyenin üzerindeyse lamba sönmekte, ışık azaldığında ise lamba yanmaktadır. Bu uygulamada da benzer şekilde Arduino sensor kartına bağlı sensor ile ışık şiddetini ölçerek ışık şiddeti azaldığında karta bağlı LED'i yakan uygulamayı gerçekleştireceğiz.

#### Grove Işık Sensoru

Grove - Işık sensoru, ışığın yoğunluğunu algılamak için bir foto-direnç (ışığa bağlı direnç) barındırmaktadır. Işık şiddeti arttığında foto direncin direnci azalır. LM358 OpAmp entegresi ise, ışığın yoğunluğuna (yani direnç değerine dayalı olarak) karşılık gelen voltaj üretir. Çıkış sinyali analog değerdir, ışık ne kadar parlaksa değer o kadar büyüktür.
![resim](https://user-images.githubusercontent.com/44734477/183247807-b996f0d9-c23c-4413-9c28-ee3178745459.png)

**Gerekli Malzemeler**

* Arduino sensor kartı

* Grove ışık sensoru

* Grove LED

**Devre kurulumu**

Deney için şekilde verilen devreyi kurabilirsiniz.

![resim](https://user-images.githubusercontent.com/44734477/183247801-d2d13647-0d66-4853-ae94-6cd414c0dd93.png)
