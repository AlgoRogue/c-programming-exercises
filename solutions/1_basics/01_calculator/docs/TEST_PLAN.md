# Temel Hesap Makinesi — Test Planı

## 1. Belgenin Amacı

Bu belge, `PRD.md` içinde tanımlanan gereksinimlerin ve `DESIGN.md`
içinde verilen teknik kararların nasıl doğrulanacağını açıklar.

## 2. Test Kapsamı

Testler aşağıdaki davranışları kapsar:

- Dört temel aritmetik işlemin doğruluğu
- Sıfıra bölme ve desteklenmeyen işlem durumları
- Geçerli sayı ve işlem girdilerinin ayrıştırılması
- Geçersiz veya kapsam dışı girdilerin reddedilmesi
- Argümansız başlatılan etkileşimli kullanım
- Komut argümanlarıyla yapılan tek işlemli kullanım
- Başarılı işlem, düzeltilebilir hata, yeni hesaplama ve çıkış akışları
- Sonuçların iki ondalık basamakla gösterilmesi
- Normal ve hatalı çıkışlarda kaynakların serbest bırakılması

Problem kapsamı dışındaki matematiksel işlemler ve platformlar test kapsamına
alınmaz.

## 3. Test Yaklaşımı

Uygulama iki test düzeyinde doğrulanacaktır:

1. `calculator` ve `input` modülleri otomatik birim testleriyle doğrulanır.
2. Etkileşimli ve tek işlemli komut akışları otomatik kabul testleriyle
   doğrulanır.

Harici bir test kütüphanesi kullanılmaz. Otomatik testler `make test`
komutuyla derlenip çalıştırılır. Başarısız bir test, sıfırdan farklı çıkış
kodu üretir.

Test dosyaları şu yapıda tutulur:

```text
tests/
├── test_calculator.c
├── test_input.c
├── test_input_read.c
├── test_helpers.h
├── fake_runtime.c
├── test_cli.sh
└── test_resources.sh
```

`test_cli.sh` (CMD-01–10, ACC-01–10), `test_resources.sh` (RES-01–04) kabul
testlerini; C test binary’leri (`test_calculator`, `test_input`, `test_input_read`)
birim test sorumluluğunu taşır. Birim ve kabul testlerinin tamamı `make test`
komutuna dahildir.

## 4. Hesaplama Birim Testleri

| Kimlik | Durum | Beklenen davranış |
|---|---|---|
| CALC-01 | İki pozitif sayıyı toplama | Doğru toplam ve başarı durumu |
| CALC-02 | Negatif ve ondalıklı sayılarla toplama | Doğru toplam ve başarı durumu |
| CALC-03 | Sonucu negatif olan çıkarma | Doğru fark ve başarı durumu |
| CALC-04 | Negatif sayılarla çıkarma | Doğru fark ve başarı durumu |
| CALC-05 | Ondalıklı sayılarla çarpma | Doğru çarpım ve başarı durumu |
| CALC-06 | Sıfırla çarpma | Sıfır sonucu ve başarı durumu |
| CALC-07 | Ondalıklı sayılarla bölme | Doğru bölüm ve başarı durumu |
| CALC-08 | Sıfıra bölme | Sıfıra bölme durumu; sonuç kullanılmaz |
| CALC-09 | Tanımsız işlem enum değeri | Desteklenmeyen işlem durumu; sonuç kullanılmaz |
| CALC-10 | `NULL` sonuç işaretçisi | Geçersiz argüman durumu; işaretçi kullanılmaz |

`double` sonuçları doğrudan eşitlik yerine `1e-9` mutlak toleransla
karşılaştırılır. Bu yaklaşım temel aritmetik testleri için yeterlidir.

## 5. Sayı Ayrıştırma Birim Testleri

### 5.1 Geçerli girdiler

| Kimlik | Girdi sınıfı | Örnek |
|---|---|---|
| NUM-01 | Pozitif tam sayı | `12` |
| NUM-02 | Negatif tam sayı | `-12` |
| NUM-03 | Artı işaretli sayı | `+12.5` |
| NUM-04 | Ondalıklı sayı | `12.5` |
| NUM-05 | Tam kısmı olmayan ondalık | `.5` |
| NUM-06 | Kesir kısmı olmayan ondalık | `5.` |
| NUM-07 | Başında ve sonunda boşluk bulunan sayı | `  -2.5  ` |
| NUM-08 | Sıfırın geçerli gösterimleri | `0`, `-0`, `0.0` |

Her durumda ayrıştırma başarılı olmalı ve beklenen `double` değerini
üretmelidir.

### 5.2 Geçersiz girdiler

| Kimlik | Girdi sınıfı | Örnek |
|---|---|---|
| NUM-09 | Boş veya yalnızca boşluk içeren girdi | `""`, `"   "` |
| NUM-10 | Rakam içermeyen işaret veya nokta | `+`, `-`, `.` |
| NUM-11 | Birden fazla ondalık noktası | `1.2.3` |
| NUM-12 | Sayının içinde boşluk | `1 2`, `- 2` |
| NUM-13 | Virgüllü ondalık gösterim | `12,5` |
| NUM-14 | Bilimsel gösterim | `1.5e3` |
| NUM-15 | Özel kayan nokta değeri | `inf`, `nan` |
| NUM-16 | Sayıdan sonra başka karakter | `12abc` |
| NUM-17 | `double` aralığı dışındaki değer | Aşırı büyük (`9...9`) veya aşırı küçük (`0.0...01`) sayı metni |
| NUM-18 | İki `NULL` argümanı (`parse_number`) | `INPUT_STATUS_INVALID_ARGUMENT`; çıktı kullanılamaz |

Her durumda ayrıştırma geçersiz girdi durumu döndürmeli ve çıktı değeri
kullanılmamalıdır.

## 6. İşlem Ayrıştırma Birim Testleri

| Kimlik | Girdi | Beklenen davranış |
|---|---|---|
| OP-01 | `+` | Toplama işlemine dönüşür |
| OP-02 | `-` | Çıkarma işlemine dönüşür |
| OP-03 | `*` | Çarpma işlemine dönüşür |
| OP-04 | `x` | Çarpma işlemine dönüşür |
| OP-05 | `/` | Bölme işlemine dönüşür |
| OP-06 | Başında veya sonunda boşluk bulunan geçerli sembol | Uygun işleme dönüşür |
| OP-07 | Boş girdi | Geçersiz girdi durumu |
| OP-08 | Desteklenmeyen sembol | Geçersiz girdi durumu |
| OP-09 | Birden fazla karakter veya sembol | Geçersiz girdi durumu |
| OP-10 | `NULL` giriş ve/veya çıktı işaretçisi | `INPUT_STATUS_INVALID_ARGUMENT`; çıktı kullanılmaz |

## 7. Devam ve Çıkış Ayrıştırma Birim Testleri

| Kimlik | Girdi | Beklenen davranış |
|---|---|---|
| CONT-01 | `e` | Yeni hesaplama seçimine dönüşür |
| CONT-02 | `h` | Çıkış seçimine dönüşür |
| CONT-03 | Başında veya sonunda boşluk bulunan `e` ya da `h` | Uygun seçime dönüşür |
| CONT-04 | Büyük harf veya başka bir karakter | Geçersiz girdi durumu |
| CONT-05 | Boş veya birden fazla karakterli girdi | Geçersiz girdi durumu |
| CONT-06 | `NULL` giriş ve/veya çıktı işaretçisi | `INPUT_STATUS_INVALID_ARGUMENT`; çıktı kullanılmaz |

## 8. Satır Okuma Birim Testleri (LINE-01–LINE-05)

`read_line(FILE*, char**, size_t*)` public sınırı `getline` tabanlıdır; test
derlemesinde `-Dgetline=test_getline` ile değiştirilebilir. `fake_runtime.c`
(`test_getline`, `test_free`) yalnız test binary’lerinde kullanılır; üretim
binary’sine girmez.

| Kimlik | Kurulum | Beklenti |
|---|---|---|
| LINE-01 | Başarı modu; başlangıçta `buffer=NULL`, `capacity=0` | `INPUT_STATUS_SUCCESS`; buffer tam satır; kapasite metni ve `\0` alır |
| LINE-02 | EOF modu ve boş `tmpfile()` | `INPUT_STATUS_END_OF_FILE` |
| LINE-03 | I/O modu (`errno=EIO`) | `INPUT_STATUS_IO_ERROR` |
| LINE-04 | Bellek modu (`errno=ENOMEM`) | `INPUT_STATUS_MEMORY_ERROR` |
| LINE-05 | `stream`, `buffer`, `capacity` için `NULL`; non-NULL sentinel | Her çağrı `INPUT_STATUS_INVALID_ARGUMENT`; output değişmez; çağrı sayısı 0 |

## 9. Tek İşlem Modu Kabul Testleri

Program tam olarak üç argümanla çalıştırıldığında bunları birinci sayı, işlem
ve ikinci sayı olarak yorumlar; sonucu gösterdikten sonra kapanır. Başarılı
bir işlemde standart çıktıya yalnızca iki ondalık basamakla biçimlendirilmiş
sonuç yazılır. Hata durumunda açıklama standart hata çıktısına yazılır ve
program sıfırdan farklı çıkış koduyla sonlanır.

| Kimlik | Komut | Beklenen davranış |
|---|---|---|
| CMD-01 | `calc 3 + 4` | `7.00` sonucu gösterilir ve program başarıyla sonlanır |
| CMD-02 | `calc 3 - 4` | `-1.00` sonucu gösterilir ve program başarıyla sonlanır |
| CMD-03 | `calc 3 x 4` | `12.00` sonucu gösterilir ve program başarıyla sonlanır |
| CMD-04 | `calc 3 '*' 4` | `12.00` sonucu gösterilir ve program başarıyla sonlanır |
| CMD-05 | `calc 3 / 4` | `0.75` sonucu gösterilir ve program başarıyla sonlanır |
| CMD-06 | Negatif veya ondalıklı argümanlarla geçerli işlem | Doğru sonuç gösterilir ve program başarıyla sonlanır |
| CMD-07 | Geçersiz sayı argümanı | Hata standart hata çıktısına yazılır ve program başarısızlık durumuyla sonlanır |
| CMD-08 | Desteklenmeyen işlem argümanı | Hata standart hata çıktısına yazılır ve program başarısızlık durumuyla sonlanır |
| CMD-09 | Sıfıra bölme | Hata standart hata çıktısına yazılır ve program başarısızlık durumuyla sonlanır |
| CMD-10 | Üçten farklı sayıda argüman | Kullanım bilgisi (`Kullanım:`) standart hata çıktısına yazılır ve program başarısızlık durumuyla sonlanır |

`*` karakterinin kabuk tarafından dosya adı desenine dönüştürülmesini önlemek
için komutta tırnak içinde kullanılması gerekir. `x`, çarpma işleminin tırnak
gerektirmeyen alternatifidir.

## 10. Etkileşimli Mod Kabul Testleri

Program argüman verilmeden yalnızca `calc` olarak çalıştırıldığında
etkileşimli modu açar.

| Kimlik | Senaryo | Beklenen davranış |
|---|---|---|
| ACC-01 | Geçerli iki sayı ve dört işlemden biri girilir | Sonuç iki ondalık basamakla gösterilir |
| ACC-02 | Geçersiz birinci sayı girilir, ardından düzeltilir | Aynı alan yeniden istenir ve hesaplama sürer |
| ACC-03 | Geçersiz işlem girilir, ardından düzeltilir | İşlem yeniden istenir ve hesaplama sürer |
| ACC-04 | Geçersiz ikinci sayı girilir, ardından düzeltilir | Aynı alan yeniden istenir ve hesaplama sürer |
| ACC-05 | Sıfıra bölme denenir | `Sıfıra bölme` hatası bildirilir ve yeni hesaplamaya geçilir |
| ACC-06 | Başarılı işlemden sonra `e` girilir | Yeni hesaplama başlar (`Sonuç:` iki kez görünür) |
| ACC-07 | Devam sorusuna `h` girilir | Program başarı durumuyla sonlanır; ikinci sonuç görünmez |
| ACC-08 | Devam sorusuna geçersiz yanıt, ardından `e` veya `h` girilir | `Geçersiz devam seçimi` yeniden istenir; geçerli yanıta göre davranılır |
| ACC-09 | Girdi sırasında `EOF` oluşur | Program normal biçimde sonlanır |
| ACC-10 | 64 karakterden uzun girdi verilir | Dinamik tampon gerektiğinde büyür; girdi güvenli biçimde okunur ve doğrulanır |

Kabul testlerinde kullanıcıya gösterilen metnin birebir eşleşmesinden çok,
mesajın doğru durumu açıkça anlatması doğrulanır.

## 11. Kaynak ve Hata Kontrolleri (RES-01–RES-04)

`fake_runtime.c` (`test_getline`, `test_free`) test-only; production binary
`getline` veya `free` substitution içermez. `tests/test_resources.sh`,
fault binary (`-Dgetline=test_getline -Dfree=test_free`) kullanarak fail-at
`2` ile sahip olunan (`non-NULL`) dinamik buffer’ın `free` edildiğini ve
hata durumunda sıfırdan farklı çıkış üretildiğini doğrular.

| Kimlik | Girdi / fault | Beklenen davranış |
|---|---|---|
| RES-01 | `1\n+\n2\nh\n`, fault yok | Status 0; stdout `Sonuç: 3.00`; `free` log 1 |
| RES-02 | `1\n` + EOF, fault yok | Status 0; `free` log 1 |
| RES-03 | `1\n`, fail-at `2`, error `io` | Status 1; stderr `Girdi okunamadı`; `free` log 1 |
| RES-04 | `1\n`, fail-at `2`, error `memory` | Status 1; stderr `Bellek ayrılamadı`; `free` log 1 |

Otomatik testler derleyici uyarıları etkinleştirilerek (`-Wall -Wextra -Werror`)
derlenmelidir.

## 12. Sürekli Entegrasyon

CI iş akışı `.github/workflows/calculator-ci.yml` dosyasında tanımlıdır:

- `push` (`main`) ve `pull_request` (`main`) olaylarında çalışır.
- `ubuntu-latest` runner’ında `permissions: contents: read` ile çalışır.
- Yalnız `make -C solutions/1_basics/01_calculator test` komutunu çağırır.
- Derleme veya test başarısız olduğunda iş akışı başarısız sayılır.

İlk sürümde ek işletim sistemi matrisi, otomatik dağıtım, yayınlama,
coverage, lint veya Doxygen adımları eklenmemiştir; kök test aggregator
da yoktur.

## 13. Başarı Ölçütleri

Testler şu koşullarda başarılı kabul edilir:

- Bütün otomatik testler geçer (`10 CALC + 34 parser + 5 LINE + 20 CMD/ACC + 4 RES = 73` case).
- `make test` sıfır çıkış kodu üretir.
- Bütün kabul testleri beklenen davranışı gösterir.
- Test derlemesinde proje tarafından etkinleştirilen uyarılar oluşmaz.
- `.github/workflows/calculator-ci.yml` `calculator-tests` işini tanımlar.
