# Dinamik Dizi ve Bellek Yönetimi

## Problem Tanımı

Boyutu çalışma zamanında büyüyüp küçülebilen, tamsayı (`int`) değerler
tutan dinamik bir dizi yapısı geliştirin. Yapı, elemanların dizinin sonuna
eklenmesini, dizinin belirli bir konumundan çıkarılmasını ve o an kaç
eleman tuttuğunun sorgulanmasını desteklemelidir. Dizi kapasitesi
tükendiğinde bellek yeniden ayrılarak büyütülmeli, kullanım bittiğinde
ayrılan tüm bellek uygun şekilde serbest bırakılmalıdır.

## Bu Problem Neden Yapılıyor?

Bu alıştırma; `malloc`, `realloc` ve `free` ile dinamik bellek yönetimini,
işaretçilerle çalışmayı ve büyüyen bir veri yapısının iç durumunu (kapasite,
eleman sayısı) tutarlı biçimde yönetmeyi bir araya getirir. Ayrıca bellek
sızıntılarından ve geçersiz erişimlerden kaçınmanın, C'de veri yapısı
tasarlarken neden temel bir kaygı olduğunu gösterir.

## Desteklenen İşlemler

- Dizinin sonuna eleman ekleme
- Belirtilen bir konumdaki elemanı çıkarma
- Belirtilen bir konumdaki elemana erişme
- Geçerli eleman sayısını sorgulama
- Dizinin kullandığı belleği tamamen serbest bırakma

## Beklenen Davranışlar

1. Dizi, başlangıçta küçük veya boş bir kapasiteyle oluşturulabilmelidir.
2. Kapasite dolduğunda, yeni eleman eklenmeden önce bellek otomatik olarak
   büyütülmelidir; mevcut elemanlar bu işlemden etkilenmemelidir.
3. Belirtilen bir konumdaki eleman çıkarıldığında, dizinin geri kalan
   elemanları tutarlı ve erişilebilir kalmalıdır.
4. Dizinin sınırları dışında bir konuma erişme veya eleman çıkarma girişimi
   fark edilmeli, tanımsız davranışa yol açmadan ele alınmalıdır.
5. Bellek ayırma işlemlerinin başarısız olma ihtimali göz önünde
   bulundurulmalıdır.
6. Program sonlanmadan önce ayrılan tüm bellek serbest bırakılmalı, bellek
   sızıntısı oluşmamalıdır.
7. Yapı, farklı boyutlarda birçok ekleme ve çıkarma işlemi art arda
   yapıldığında doğru ve kararlı davranmalıdır.

Veri yapısının iç temsili, büyütme stratejisi (ör. kapasitenin katlanması),
uygulama programlama arayüzü (API) tasarımı ve test araçları bilinçli
olarak geliştiricinin kararına bırakılmıştır.

## Örnek Etkileşim

Aşağıdaki akış yalnızca olası bir kullanım örneğidir. Çözümün bir komut
satırı arayüzü sunması zorunlu değildir; bir kütüphane/modül olarak da
gerçekleştirilip test kodu üzerinden kullanılabilir.

```text
Dinamik dizi oluşturuldu (başlangıç kapasitesi: 4)
Eklendi: 10 -> [10]
Eklendi: 20 -> [10, 20]
Eklendi: 30 -> [10, 20, 30]
Eklendi: 40 -> [10, 20, 30, 40]
Eklendi: 50 -> kapasite büyütüldü -> [10, 20, 30, 40, 50]
İndeks 1 çıkarıldı -> [10, 30, 40, 50]
Eleman sayısı: 4
Bellek serbest bırakıldı.
```

## Değerlendirme Ölçütleri

- Ekleme, çıkarma, erişim ve sorgulama işlemleri farklı senaryolarda doğru
  sonuç üretmelidir.
- Kapasite büyütme işlemi mevcut verileri bozmadan çalışmalıdır.
- Geçersiz konum erişimleri ve olası bellek ayırma hataları, tanımsız veya
  yanıltıcı davranışa yol açmadan ele alınmalıdır.
- Bellek sızıntısı bulunmamalıdır (ör. `valgrind` gibi bir araçla
  doğrulanabilir).
- Çözüm, deponun belgelendirme, test ve derleme standartlarını karşılamalıdır.
