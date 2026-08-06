# Temel Hesap Makinesi

## Problem Tanımı

Temel aritmetik işlemler yapabilen, komut satırından kullanılan etkileşimli bir
hesap makinesi geliştirin. Program, kullanıcının her işlemden veya düzeltilebilir
bir girdi hatasından sonra programı yeniden başlatmasına gerek kalmadan birden
fazla hesaplama yapabilmesini sağlamalıdır.

## Bu Problem Neden Yapılıyor?

Bu alıştırma; kullanıcı girdisi okuma, karar verme, aritmetik işlemler yapma,
işlemleri tekrarlama ve geçersiz verileri ele alma gibi temel C programlama
becerilerini küçük bir programda bir araya getirir. Ayrıca basit bir programın
bile kullanıcı hata yaptığında öngörülebilir davranması gerektiğini gösterir.

## Desteklenen İşlemler

- Toplama (`+`)
- Çıkarma (`-`)
- Çarpma (`*`)
- Bölme (`/`)

## Beklenen Davranışlar

1. Kullanıcıdan iki sayısal değer ve desteklenen bir aritmetik işlem alınmalıdır.
2. Toplama, çıkarma, çarpma ve bölme işlemleri yapılabilmelidir.
3. İşlemin sonucu anlaşılır biçimde gösterilmelidir.
4. Kullanıcı yeni hesaplamalar yapabilmeli veya programdan çıkmayı seçebilmelidir.
5. Geçersiz sayısal girdiler ve desteklenmeyen işlemler fark edilmeli, bu
   durumlarda yanıltıcı bir sonuç gösterilmemelidir.
6. Sıfıra bölme engellenmeli ve hata anlaşılır biçimde bildirilmelidir.
7. Program, düzeltilebilir girdi ve hesaplama hatalarından sonra kullanılmaya
   devam edilebilmelidir.

Etkileşim tasarımı, ekranda kullanılacak ifadeler, programın iç yapısı,
uygulama programlama arayüzleri (API), sayısal veri gösterimi ve test araçları
bilinçli olarak geliştiricinin kararına bırakılmıştır.

## Örnek Etkileşim

Aşağıdaki akış yalnızca olası bir etkileşim örneğidir. Programın aynı
ifadeleri veya ekran düzenini kullanması gerekmez.

```text
Birinci sayıyı girin: 10
İşlemi girin (+, -, *, /): +
İkinci sayıyı girin: 5
Sonuç: 10 + 5 = 15

Devam etmek istiyor musunuz? (e/h): h
```

## Değerlendirme Ölçütleri

- Desteklenen dört işlem, farklı girdilerle doğru sonuçlar üretmelidir.
- Geçersiz girdiler ve sıfıra bölme, tanımsız veya yanıltıcı davranışa yol
  açmadan ele alınmalıdır.
- Kullanıcı art arda hesaplamalar yapabilmeli ve istediğinde programdan
  çıkabilmelidir.
- Çözüm, deponun belgelendirme, test ve derleme standartlarını karşılamalıdır.
