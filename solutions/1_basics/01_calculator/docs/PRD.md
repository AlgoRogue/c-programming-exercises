# Temel Hesap Makinesi — Ürün Gereksinimleri Belgesi

## 1. Ürün Tanımı

Bu proje, komut satırından kullanılan ve dört temel aritmetik işlemi yapan bir
hesap makinesi uygulamasıdır. Kullanıcı uygulamayı etkileşimli olarak veya tek
bir işlemi komut argümanlarıyla vererek kullanabilir.

## 2. Amaç

Amaç, kullanıcının tam ve ondalıklı sayılarla temel hesaplamaları güvenilir ve
anlaşılır biçimde yapabilmesidir. Geçersiz girdiler yanıltıcı sonuç üretmeden
ele alınmalıdır.

## 3. Hedef Kullanıcı

Komut satırında hızlı ve basit aritmetik hesaplamalar yapmak isteyen
kullanıcılar.

## 4. Kapsam

Uygulama aşağıdaki işlemleri destekler:

- Toplama (`+`)
- Çıkarma (`-`)
- Çarpma (`*` veya `x`)
- Bölme (`/`)

Tüm işlemler ondalıklı sayılarla çalışabilmelidir.

Uygulamanın iki kullanım biçimi vardır:

- `calc`: Etkileşimli modu açar ve aynı oturumda art arda hesaplamalar
  yapılmasını sağlar.
- `calc 3 + 4`: Verilen işlemi bir kez yapar, sonucu gösterir ve kapanır.

## 5. Kullanıcı Akışları

### 5.1 Etkileşimli Mod

1. Kullanıcı `calc` komutunu argümansız çalıştırır.
2. Kullanıcı ilk sayısal değeri girer.
3. Kullanıcı desteklenen işlemlerden birini seçer.
4. Kullanıcı ikinci sayısal değeri girer.
5. Program sonucu gösterir veya oluşan hatayı açıklar.
6. Kullanıcı `e` ile yeni bir hesaplama yapar veya `h` ile programdan çıkar.

### 5.2 Tek İşlem Modu

1. Kullanıcı iki sayı ve aralarındaki işlemi komut argümanları olarak verir.
2. Program girdileri doğrular ve hesaplamayı yapar.
3. Başarılıysa yalnızca sonucu iki ondalık basamakla standart çıktıya yazar.
4. Hata varsa açıklamayı standart hata çıktısına yazar ve başarısız çıkış
   koduyla sonlanır.

Çarpma işleminde kabuğun `*` karakterini yorumlamasını önlemek için
`calc 3 '*' 4` yazılabilir. `calc 3 x 4` kullanımı tırnak gerektirmez.

## 6. İşlevsel Gereksinimler

- Program iki sayısal değer ve desteklenen bir işlem kabul etmelidir.
- Program pozitif, negatif ve ondalıklı sayıları desteklemelidir.
- Ondalıklı sayılar nokta ile yazılmalıdır (`12.5` gibi).
- Program dört temel aritmetik işlemi doğru biçimde gerçekleştirmelidir.
- Program sonuçları iki ondalık basamakla göstermelidir.
- Argümansız çalıştırıldığında etkileşimli modu açmalıdır.
- Tam olarak üç kullanıcı argümanıyla çalıştırıldığında tek işlem modunu
  kullanmalıdır.
- Geçersiz argüman sayısında kullanım bilgisi göstermelidir.
- Etkileşimli mod art arda hesaplamalara izin vermelidir.
- Etkileşimli modda `e` devam, `h` çıkış anlamına gelmelidir.
- Program geçersiz sayısal girdileri fark etmelidir.
- Program desteklenmeyen işlemleri reddetmelidir.
- Program sıfıra bölmeyi engellemeli ve hatayı açıkça bildirmelidir.
- Düzeltilebilir bir etkileşimli mod hatası programı beklenmedik biçimde
  sonlandırmamalıdır.

## 7. Kapsam Dışındakiler

- Dört temel işlem dışındaki matematiksel işlemler
- Bilimsel gösterimle yazılan sayılar (`1.5e3` gibi)
- Sonsuzluk ve sayı olmayan değerler (`inf` ve `nan`)
- Virgülün ondalık ayırıcı olarak kullanılması (`12,5` gibi)
- Parantezli veya birden fazla işlem içeren ifadeler
- İşlem geçmişi veya sonuçların kalıcı olarak saklanması
- Grafik kullanıcı arayüzü
- Windows desteği

## 8. Kabul Ölçütleri

- Pozitif, negatif ve ondalıklı sayılarla dört temel işlem yapılabilmelidir.
- `calc` komutu etkileşimli modu açmalıdır.
- `calc 3 + 4` komutu standart çıktıda `7.00` üretmelidir.
- `*` ve `x` aynı çarpma işlemini gerçekleştirmelidir.
- Geçersiz sayı girdilerinde yanıltıcı bir sonuç gösterilmemelidir.
- Desteklenmeyen bir işlem seçildiğinde kullanıcı bilgilendirilmelidir.
- Sıfıra bölme girişimi etkileşimli modu sonlandırmamalıdır.
- Kullanıcı bir hata veya başarılı hesaplama sonrasında yeni işlem
  yapabilmelidir.
- Kullanıcı etkileşimli moddan `h` ile normal biçimde çıkabilmelidir.
- Tek işlem modundaki hatalar standart hata çıktısına yazılmalı ve program
  sıfırdan farklı çıkış koduyla sonlanmalıdır.
