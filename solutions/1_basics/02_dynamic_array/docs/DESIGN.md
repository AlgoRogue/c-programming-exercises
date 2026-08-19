# Dinamik Dizi ve Bellek Yönetimi — Teknik Tasarım Belgesi

## 1. Belgenin Amacı

Bu belge, `PRD.md` içinde tanımlanan gereksinimlerin teknik olarak nasıl
gerçekleştirildiğini açıklar.

## 2. Tasarım Hedefleri

- Basit ve tahmin edilebilir bir bellek büyütme stratejisi kullanmak.
- Her fonksiyonda geçersiz argümanları ve sınır durumlarını tutarlı bir
  durum koduyla bildirmek.
- Bellek sahipliğini tek bir yapıda (`struct DynamicArray`) toplamak ve
  serbest bırakmayı tek bir fonksiyonda yönetmek.
- Harici bağımlılık olmadan, yalnızca standart kütüphane (`stdlib.h`) ile
  çalışmak.

## 3. Veri Yapısı

```c
struct DynamicArray
{
    int *data;
    size_t size;
    size_t capacity;
};
```

- `data`: Ayrılan bellek bloğuna işaretçi; `capacity == 0` iken `NULL`
  olabilir.
- `size`: Geçerli eleman sayısı.
- `capacity`: `data`'nın tutabileceği toplam eleman sayısı.

Yapı, çağıran kod tarafından yığın (stack) üzerinde tutulur; modül kendi
başına `struct DynamicArray` ayırmaz. Bu, `calculator` çözümündeki girdi
tamponu sahipliği yaklaşımıyla tutarlıdır: sahiplik her zaman çağıranda
kalır, modül yalnızca çağıranın verdiği belleği yönetir.

**Durum:** Karar verildi.

## 4. Durum Kodları

```c
enum DynArrayStatus
{
    DYN_ARRAY_STATUS_SUCCESS,
    DYN_ARRAY_STATUS_OUT_OF_BOUNDS,
    DYN_ARRAY_STATUS_ALLOCATION_FAILURE,
    DYN_ARRAY_STATUS_INVALID_ARGUMENT
};
```

`dynamic_array_size` ve `dynamic_array_free` dışındaki tüm fonksiyonlar bu
enum türünden bir durum döndürür. `dynamic_array_size`'ın dönüş değeri
doğrudan eleman sayısıdır; hata durumu ayrımı gerekmediği için (yalnızca
`NULL` girişte `0` döner) ayrı bir durum koduna ihtiyaç yoktur.
`dynamic_array_free`'nin dönüş değeri yoktur çünkü serbest bırakma
işleminin başarısız olabileceği bir durum söz konusu değildir.

**Durum:** Karar verildi.

## 5. Büyüme Stratejisi

`dynamic_array_push_back` çağrıldığında `size == capacity` ise kapasite
büyütülür:

- `capacity == 0` ise yeni kapasite `DYN_ARRAY_DEFAULT_GROWTH_CAPACITY` (4)
  olur.
- Aksi halde yeni kapasite `capacity * 2` olur (katlanarak büyüme).

Katlanarak büyüme, `push_back`'in amortize edilmiş sabit zamanlı
karmaşıklığını korumak için seçilmiştir; her eklemede sabit miktarda
büyütme (`capacity + 1`) yerine `realloc` çağrı sayısını `O(log n)`'e
indirir.

`realloc` başarısız olursa dönen `NULL` işaretçi orijinal `arr->data`'nın
üzerine yazılmaz; `arr` önceki geçerli durumunda kalır ve
`DYN_ARRAY_STATUS_ALLOCATION_FAILURE` döndürülür.

**Durum:** Karar verildi.

## 6. Silme Stratejisi

`dynamic_array_remove_at`, çıkarılan konumdan sonraki tüm elemanları bir
konum sola kaydırır (`O(n)`). Dizinin eleman sırasını koruma gereksinimi
(PRD §6, "geri kalan elemanlar tutarlı ve erişilebilir kalmalı") nedeniyle
son elemanla yer değiştirme (`O(1)` ama sırayı bozan) yöntemi yerine bu
tercih edilmiştir. Kapasite küçültme yapılmaz; bu, PRD'de kapsam dışı
bırakılmıştır (§7).

**Durum:** Karar verildi.

## 7. Bellek Yönetimi ve Sahiplik

`data` alanının sahibi her zaman `struct DynamicArray` örneğidir.
`dynamic_array_free`:

- `arr == NULL` ise no-op'tur (güvenle çağrılabilir).
- Aksi halde `free(arr->data)` çağrılır (`data == NULL` olsa da `free(NULL)`
  güvenlidir); ardından `data = NULL`, `size = 0`, `capacity = 0` atanır.

`data`'nın `NULL`'a sıfırlanması, `dynamic_array_free`'nin aynı örnek
üzerinde tekrar çağrılmasını (çift serbest bırakma olmadan) güvenli kılar.
Bu davranış DYNARR-17/18/19 testleriyle doğrulanmıştır.

**Durum:** Karar verildi.

## 8. Platform Uyumluluğu

Kaynak kod C17 standardına göre, `-Wall -Wextra -Werror` uyarılarıyla
derlenir (bkz. `Makefile`). `calculator` çözümüyle aynı derleyici
bayraklarını paylaşır; POSIX'e özgü bir işlev kullanılmadığı için
`_POSIX_C_SOURCE` tanımı yalnızca tutarlılık amacıyla `CFLAGS`'e
eklenmiştir.

**Durum:** Karar verildi.

## 9. Test Edilebilirlik

Testler harici bir kütüphaneye bağımlı değildir; `01_calculator`
çözümündeki yardımcı test katmanının (`test_helpers.h`) `int`/`size_t`
karşılaştırma yardımcılarını içeren, bu çözüme özgü bir kopyası kullanılır
(çözümler arası paylaşılan bir test kütüphanesi henüz yoktur). Testler
`make test` ile tek adımda derlenip çalıştırılır.

**Durum:** Karar verildi.
