# Dinamik Dizi ve Bellek Yönetimi — Ürün Gereksinimleri Belgesi

## 1. Ürün Tanımı

Bu çözüm, boyutu çalışma zamanında büyüyebilen, tamsayı (`int`) değerler
tutan bir dinamik dizi kütüphanesidir. Bir komut satırı arayüzü sunmaz;
`struct DynamicArray` ve buna karşılık gelen fonksiyonlar üzerinden
kullanılan bir modül olarak gerçekleştirilir.

## 2. Amaç

Amaç, sabit boyutlu C dizilerinin yetersiz kaldığı durumlarda güvenli,
öngörülebilir ve bellek sızıntısı üretmeyen bir dinamik dizi sağlamaktır.
Geçersiz kullanım (NULL işaretçi, sınır dışı erişim, bellek ayırma hatası)
tanımsız davranışa yol açmadan bildirilmelidir.

## 3. Hedef Kullanıcı

Bu depo içindeki diğer çözümler veya test kodu tarafından bir yapı taşı
olarak kullanılan, C ile dinamik veri yapısı pratiği yapan geliştirici.

## 4. Kapsam

Modül aşağıdaki işlemleri destekler:

- `dynamic_array_init`: Diziyi verilen başlangıç kapasitesiyle ilklendirme.
- `dynamic_array_push_back`: Dizinin sonuna eleman ekleme; kapasite dolduğunda
  otomatik büyütme.
- `dynamic_array_remove_at`: Belirtilen konumdaki elemanı çıkarma; sonraki
  elemanları kaydırma.
- `dynamic_array_get`: Belirtilen konumdaki elemanı okuma.
- `dynamic_array_size`: Geçerli eleman sayısını sorgulama.
- `dynamic_array_free`: Dizinin kullandığı belleği serbest bırakma.

## 5. Kullanıcı Akışı

1. Çağıran kod `struct DynamicArray` örneğini `dynamic_array_init` ile
   ilklendirir.
2. `dynamic_array_push_back` ile elemanlar eklenir; kapasite dolduğunda
   dizi kendiliğinden büyür.
3. `dynamic_array_get` ve `dynamic_array_size` ile dizi sorgulanır.
4. `dynamic_array_remove_at` ile istenen konumdaki eleman çıkarılır.
5. Kullanım bittiğinde `dynamic_array_free` çağrılarak ayrılan bellek
   serbest bırakılır.

## 6. İşlevsel Gereksinimler

- `dynamic_array_init`, `arr == NULL` durumunda
  `DYN_ARRAY_STATUS_INVALID_ARGUMENT` döndürmelidir.
- `initial_capacity == 0` ile ilklendirme geçerlidir; `data` `NULL`,
  `capacity` `0` olarak ayarlanmalıdır.
- `dynamic_array_push_back`, kapasite dolduğunda mevcut elemanları koruyarak
  belleği büyütmelidir.
- Bellek ayırma başarısız olursa `DYN_ARRAY_STATUS_ALLOCATION_FAILURE`
  döndürülmeli, dizinin önceki durumu bozulmamalıdır.
- `dynamic_array_get` ve `dynamic_array_remove_at`, sınır dışı bir `index`
  için `DYN_ARRAY_STATUS_OUT_OF_BOUNDS` döndürmelidir.
- `dynamic_array_get`, `out_value == NULL` durumunda
  `DYN_ARRAY_STATUS_INVALID_ARGUMENT` döndürmelidir.
- `dynamic_array_size`, `arr == NULL` durumunda `0` döndürmelidir (durum kodu
  yoktur).
- `dynamic_array_free`, `arr == NULL` durumunda güvenle no-op olmalı; aksi
  halde `data`'yı serbest bırakıp `data`'yı `NULL`, `size` ve `capacity`'yi
  `0` yapmalıdır.
- Tüm fonksiyonlar, geçersiz argümanlarda dahi tanımsız davranışa yol
  açmamalıdır.

## 7. Kapsam Dışındakiler

- Genel amaçlı (jenerik) eleman türü desteği; yalnızca `int` desteklenir.
- Dizinin ortasına ekleme (`insert_at`).
- Kapasiteyi küçültme (`shrink_to_fit`).
- Eşzamanlılık/thread-safety garantisi.
- Komut satırı arayüzü.

## 8. Kabul Ölçütleri

- `init`/`push_back`/`get`/`size`/`remove_at`/`free` fonksiyonlarının tümü
  belirtilen durum kodlarını doğru döndürmelidir.
- Kapasite büyütme, mevcut verileri bozmadan çalışmalıdır.
- Sınır dışı erişim ve `NULL` argüman durumları güvenle ele alınmalıdır.
- `dynamic_array_free` sonrası dizi tekrar `dynamic_array_free` ile
  çağrılabilir (çift serbest bırakmaya karşı güvenli) — `data` zaten `NULL`
  olduğundan `free(NULL)` güvenlidir.
- Bellek sızıntısı bulunmamalıdır.
