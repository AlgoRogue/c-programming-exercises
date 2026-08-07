# Temel Hesap Makinesi — Teknik Tasarım Belgesi

## 1. Belgenin Amacı

Bu belge, `PRD.md` içinde tanımlanan gereksinimlerin teknik olarak nasıl
gerçekleştirileceğini açıklar. Ürün kapsamını değiştirmez; uygulama
sırasında verilecek tasarım kararlarını kaydeder.

## 2. Tasarım Hedefleri

- Girdi, hesaplama ve kullanıcı etkileşimi sorumluluklarını anlaşılır
  biçimde ayırmak
- Etkileşimli ve tek işlemli komut kullanımında aynı ayrıştırma ve hesaplama
  kurallarını uygulamak
- Geçersiz girdileri ve hesaplama hatalarını kontrollü biçimde ele almak
- Hesaplama davranışını otomatik olarak test edilebilir tutmak
- Kaynak ve bellek kullanımını açıkça yönetmek

## 3. Genel Mimari

Uygulama, yalnızca mevcut sorumlulukları ayırmak için üç bileşenden
oluşacaktır:

- `main`: Komut argümanlarını, kullanıcı mesajlarını, çalışma modu seçimini
  ve etkileşimli işlem döngüsünü yönetir.
- `input`: Dinamik satır okuma, metin ayrıştırma ve girdi doğrulama
  sorumluluklarını taşır. Aynı ayrıştırma fonksiyonları etkileşimli girdiler
  ve komut argümanları için kullanılır.
- `calculator`: Dört temel aritmetik işlemi ve hesaplamaya özgü hata
  kontrollerini gerçekleştirir.

`main`, `input` ve `calculator` modüllerini kullanır. İşlem türü
`calculator.h` içinde tanımlanır. `input`, işlem metnini bu türe dönüştürmek
için `calculator.h` arayüzüne bağımlıdır; `calculator` ise `input` modülüne
bağımlı değildir. Kullanıcı arayüzü ile hesaplama mantığı bu tek yönlü
bağımlılık sayesinde ayrı test edilebilir.

Ayrı bir çıktı, loglama, işlem kaydı veya eklenti sistemi oluşturulmayacaktır.

Modüllerin açık arayüzleri ve gerçekleştirimleri ayrı dizinlerde tutulacaktır:

```text
include/
├── calculator.h
└── input.h
src/
├── main.c
├── calculator.c
└── input.c
```

Derleme sistemi, header dosyalarının bulunabilmesi için `include/` dizinini
arama yoluna ekleyecektir.

**Durum:** Karar verildi.

## 4. Sayısal Veri Gösterimi

Kullanıcıdan alınan sayısal değerler ve hesaplama sonuçları program içinde
`double` veri türüyle temsil edilecektir.

Geçerli değerlerin sınırları ve özel kayan nokta değerlerinin nasıl
reddedileceği, girdi doğrulama kurallarıyla tanımlanmıştır.

**Durum:** Karar verildi.

## 5. Girdi Okuma ve Ayrıştırma

Etkileşimli moddaki kullanıcı girdisi standart girdiden `getline` ile
okunacaktır. Girdi tamponu dinamik olarak ayrılacak ve daha uzun girdiler
için gerektiğinde `getline` tarafından büyütülecektir. POSIX.1-2008
bildirimlerini etkinleştirmek için `_POSIX_C_SOURCE=200809L` tanımı
kullanılacaktır.

Okunan metin `strtod` ile `double` değere dönüştürülecektir. Dönüşümün
başarısı, dönüşümün durduğu konum ve aralık hataları kontrol edilecektir.

Satır okuma ile ayrıştırma ayrı fonksiyonlar tarafından gerçekleştirilecektir:

- Satır okuma fonksiyonu yalnızca `getline` ve okuma durumlarından sorumludur.
- Sayı ayrıştırma fonksiyonu, verilen metni bir `double` değere dönüştürür.
- İşlem ayrıştırma fonksiyonu, verilen metni desteklenen işlem enum'una
  dönüştürür.
- Devam seçimi ayrıştırma fonksiyonu, `e` ve `h` girdilerini uygun seçim
  değerine dönüştürür.

Ayrıştırma fonksiyonları standart girdiden okuma yapmaz ve kendilerine verilen
metni değiştirmez.

`strtod`, uygulamanın kabul etmediği bilimsel gösterim, `inf` ve `nan` gibi
girdileri de ayrıştırabildiği için ayrı bir girdi biçimi doğrulaması
yapılacaktır.

Geçerli bir sayı girdisi:

- İsteğe bağlı olarak `+` veya `-` işaretiyle başlayabilir.
- En fazla bir ondalık noktası içerebilir.
- En az bir rakam içermelidir.
- Başında ve sonunda boşluk karakterleri bulunabilir.
- Sayının kendi içinde boşluk karakteri içeremez.
- `.5` ve `5.` gibi gösterimleri kullanabilir.

Baştaki ve sondaki boşluklar yeni bir metin oluşturularak normalize
edilmeyecektir. `strtod` baştaki boşlukları geçecek; dönüşüm sonrasında kalan
boşluklar kontrol edilerek girdinin sonuna ulaşıldığı doğrulanacaktır.

Virgüllü ondalık gösterimi, bilimsel gösterim, `inf`, `nan`, aralık dışı
değerler ve kurala uymayan diğer tüm girdiler reddedilecektir.

İşlem ayrıştırıcısı `+`, `-`, `*`, `x` ve `/` sembollerini kabul edecektir.
`*` ile `x` aynı çarpma enum değerine dönüştürülecektir. Baştaki ve sondaki
boşluklar kabul edilecek, başka karakterler reddedilecektir.

Devam seçimi ayrıştırıcısı, başındaki ve sonundaki boşluklardan sonra yalnızca
küçük `e` veya `h` karakterini kabul edecektir. Büyük harfler ve diğer tüm
girdiler reddedilecektir.

Sayı ve işlem ayrıştırma fonksiyonları, komut argümanları için de değişiklik
yapılmadan kullanılacaktır.

**Durum:** Karar verildi.

## 6. Hesaplama Modeli

Hesaplama arayüzü, işlem sonucunu bir `double` çıktı parametresi üzerinden
iletecektir. Fonksiyonun dönüş değeri ise hesaplamanın başarı durumunu belirten
bir `enum` olacaktır.

Başarı durumunda çıktı parametresi hesaplanan sonucu içerir. Hata durumunda
çıktı parametresindeki değer geçerli bir sonuç olarak kullanılmaz.

Desteklenen işlemler `calculator.h` içinde tanımlanan bir `enum` ile temsil
edilecektir. Bu enum toplama, çıkarma, çarpma ve bölme değerlerini
içerecektir. `input` modülü kullanıcının girdiği işlem sembolünü uygun enum
değerine dönüştürecek; `calculator` modülü kullanıcı arayüzü sembollerine
bağımlı olmayacaktır. Yalnızca bu tipi paylaşmak için ek bir ortak tür dosyası
oluşturulmayacaktır.

**Durum:** Karar verildi.

## 7. Hata Yönetimi

Hesaplama modülü en az aşağıdaki durumları ayırt eden bir `enum` sonuç kodu
kullanacaktır:

- Başarılı hesaplama
- Desteklenmeyen işlem
- Sıfıra bölme

Hesaplama modülü kullanıcıya doğrudan mesaj yazmayacaktır. Durum kodunu
kullanıcı mesajına dönüştürme sorumluluğu `main` bileşenine ait olacaktır.

Girdi modülü aşağıdaki durumları ayırt eden ayrı bir `enum` kullanacaktır:

- Başarılı okuma ve ayrıştırma
- Geçersiz kullanıcı girdisi
- Dosya sonu (`EOF`)
- Girdi/çıktı hatası
- Bellek ayırma hatası

Okunan veya ayrıştırılan değerler çıktı parametreleriyle iletilecek ve
yalnızca başarı durumunda geçerli kabul edilecektir. Girdi modülü kullanıcıya
doğrudan hata mesajı yazmayacaktır. Durum kodunu mesaja ve program akışına
dönüştürme sorumluluğu `main` bileşenine ait olacaktır.

Tek işlem modunda başarılı sonuç standart çıktıya; hata ve kullanım bilgileri
standart hata çıktısına yazılacaktır. Etkileşimli modda kullanıcı yönlendirme
mesajlarını `main` yönetecektir.

**Durum:** Karar verildi.

## 8. Program Akışı

`main`, kullanıcı tarafından verilen argüman sayısına göre çalışma modunu
seçecektir:

- Yalnızca program adı varsa (`argc == 1`) etkileşimli mod açılır.
- Program adına ek olarak üç argüman varsa (`argc == 4`) tek işlem modu
  çalışır. Argümanlar sırasıyla birinci sayı, işlem ve ikinci sayıdır.
- Diğer argüman sayılarında kullanım bilgisi standart hata çıktısına yazılır
  ve program başarısız durum koduyla sonlanır.

Tek işlem modunda argümanlar `input` ayrıştırma fonksiyonlarıyla doğrulanır ve
hesaplama bir kez yapılır. Başarılı sonuç iki ondalık basamakla standart
çıktıya yazılır ve program başarıyla sonlanır. Geçersiz girdi, desteklenmeyen
işlem veya sıfıra bölme durumunda açıklama standart hata çıktısına yazılır
ve program başarısız durum koduyla sonlanır.

Etkileşimli mod bir hesaplama döngüsü içinde çalışır. Her döngüde iki sayı
ve bir işlem alınır. Başarılı hesaplamadan sonra kullanıcıdan `e` ile devam
veya `h` ile çıkış seçimi istenir.

Etkileşimli moddaki hata akışı şöyledir:

- Geçersiz kullanıcı girdisinde aynı alan yeniden istenir.
- Sıfıra bölmede mevcut işlem iptal edilir ve yeni hesaplamaya geçilir.
- Geçersiz devam/çıkış seçiminde seçim yeniden istenir.
- `EOF`, kullanıcının oturumu bitirdiği kabul edilerek normal çıkışa yol açar.
- Girdi/çıktı veya bellek ayırma hatasında hata mesajı gösterilir ve program
  başarısız durum koduyla sonlandırılır.

Normal veya hatalı her çıkış yolunda sahip olunan kaynaklar serbest
bırakılacaktır.

**Durum:** Karar verildi.

## 9. Bellek Yönetimi

Etkileşimli modda `getline` tarafından ayrılan girdi tamponu, program çalıştığı
sürece yeni girdiler için yeniden kullanılacaktır. Tamponun sahibi `main`
bileşenidir. `input` modülü, kendisine iletilen tamponu ve kapasite bilgisini
`getline` ile kullanabilir ve gerektiğinde güncelleyebilir. Tek işlem
modunda komut argümanları doğrudan ayrıştırıldığı için dinamik girdi
tamponuna ihtiyaç yoktur.

Programın normal ve hatalı bütün çıkış yollarında tamponu tek noktadan serbest
bırakma sorumluluğu `main` bileşenine aittir.

**Durum:** Karar verildi.

## 10. Platform Uyumluluğu

Uygulama, POSIX uyumlu işletim sistemlerini hedefler. Geliştirme ve
doğrulama macOS üzerinde yapılacak, Linux uyumluluğu korunacaktır.
Gerektiğinde POSIX.1-2008 tarafından sunulan işlevler kullanılabilir.

Kaynak kod C17 standardına göre derlenecektir. POSIX.1-2008 işlevleri,
`_POSIX_C_SOURCE=200809L` tanımıyla etkinleştirilecektir.

Windows desteği kapsam dışındadır.

**Durum:** Karar verildi.

## 11. Test Edilebilirlik

Testler harici bir test kütüphanesine bağımlı olmayacaktır. Birim testleri için
küçük bir yardımcı katman kullanılacak ve testler `make test` komutuyla tek
adımda derlenip çalıştırılacaktır.

Testler sorumluluklara göre ayrılacaktır:

```text
tests/
├── test_calculator.c
├── test_input.c
├── test_helpers.h
└── test_cli.sh
```

- `calculator` testleri dört işlemi ve hesaplama hata durumlarını doğrular.
- `input` testleri geçerli ve geçersiz sayı, işlem ve devam seçimi girdilerini
  doğrular.
- `test_cli.sh`, tek işlem ve etkileşimli mod akışlarını; çıktılarını ve
  çıkış kodlarını doğrular.
- `double` sonuçları uygun bir toleransla karşılaştırılır.
- Testlerin başarısızlık durumunda sıfırdan farklı bir çıkış kodu üretmesi
  gerekir.

Girdi ayrıştırma fonksiyonları terminal etkileşiminden bağımsız olarak
doğrudan test edilecektir.

**Durum:** Karar verildi.
