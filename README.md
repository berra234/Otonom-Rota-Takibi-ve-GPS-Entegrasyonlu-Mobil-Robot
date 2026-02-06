

Bu proje, otonom mobil robotlar için geliştirilmiş bir Ham Veri İşleme ve Seyrüsefer ünitesidir. Sistem, GPS modülünden gelen NMEA verilerini harici bir kütüphane kullanmadan doğrudan bayt seviyesinde ayrıştırır ve optik enkoderler kullanarak motor hızlarını gerçek zamanlı olarak senkronize eder.

Yazılım, Arduino Mega üzerinde çalışmakta olup, coğrafi koordinatları (Enlem/Boylam) metrik mesafeye çeviren matematiksel algoritmaları ve aracın düz bir hatta gitmesini sağlayan Kapalı Çevrim (Closed-Loop) kontrol mimarisini içerir.
-Projenin Teknik Hedefleri
Kütüphanesiz GPS Ayrıştırma (Parsing): TinyGPS gibi hazır kütüphaneler kullanmak yerine, UART tamponundaki (buffer) veriyi manuel olarak işleyerek bellek yönetimi ve protokol hakimiyetini kanıtlamak.

Coğrafi Hesaplamalar: Derece-Dakika-Saniye (DMS) formatındaki veriyi ondalık sisteme çevirmek ve Kosinüs Teoremi ile boylamlar arası mesafe düzeltmesi yapmak.

Motor Senkronizasyonu: İki bağımsız DC motorun mekanik farklılıklarını, enkoder geri beslemesi ve kesme (interrupt) rutinleri ile elimine ederek doğrusal sürüş sağlamak.
Donanım Mimarisi
Mikrodenetleyici: Arduino Mega 2560 (Donanımsal Serial1 portu GPS için kullanılmıştır).

Sensörler:

GPS Modülü (Neo-6M vb.) @ 9600 Baud.

2x Optik Enkoder (Kesme tabanlı okuma).

Eyleyiciler (Aktüatörler): 2x DC Motor + L298N Sürücü.

Arayüz: 16x2 LCD Ekran (Paralel Bağlantı).
Matematiksel Model ve Algoritma
1. NMEA Ayrıştırma Mantığı
Sistem, $GPGGA veya $GPRMC paketlerini yakalamak için özel bir durum makinesi (state-machine) kullanır. Gelen veri ASCII formatındadır:

ASCII Dönüşümü: Gelen karakterlerden '0' (48) çıkarılarak tamsayı değerleri elde edilir.

Örnek: '4' (52) - 48 = 4 (int).
2. Navigasyon Matematiği
Dünya küresel olduğu için iki boylam arasındaki mesafe Ekvator'dan kutuplara gidildikçe azalır. 
Kod içerisinde bu düzeltme şu formülle uygulanmıştır:
MesafeDog˘​u​=ΔBoylam×cos(Enlemrad​)×1.852
Burada 1.852 katsayısı, Deniz Mili (Nautical Mile) dönüşümünden türetilmiş metrik sabittir.
Diferansiyel Sürüş Kontrolü
Her 100ms'de bir sol ve sağ tekerleklerin enkoder darbeleri (solplus ve sagplus) karşılaştırılır:

Sol > Sağ: Sol motor yavaşlatılır, sağ hızlandırılır.

Sağ > Sol: Sağ motor yavaşlatılır, sol hızlandırılır.

Eşit: Nominal hız korunur.

