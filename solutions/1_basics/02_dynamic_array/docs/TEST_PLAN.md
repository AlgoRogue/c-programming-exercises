# Dinamik Dizi ve Bellek Yönetimi — Test Planı

## 1. Belgenin Amacı

Bu belge, `PRD.md` içinde tanımlanan gereksinimlerin ve `DESIGN.md` içinde
verilen teknik kararların nasıl doğrulandığını açıklar.

## 2. Test Kapsamı

Testler aşağıdaki davranışları kapsar:

- `init`, `push_back`, `get`, `size`, `remove_at`, `free` fonksiyonlarının
  başarılı yollarını.
- Her fonksiyonun `NULL`/geçersiz argüman durumlarını.
- Sınır dışı `index` durumlarını (`get`, `remove_at`).
- Kapasite büyütme sırasında mevcut verilerin korunmasını.
- `remove_at` sonrası eleman sırasının korunmasını.
- `free` sonrası dizinin güvenli (sıfırlanmış) durumunu ve tekrar `free`
  çağrısına dayanıklılığını.

Genel amaçlı eleman türü desteği ve `insert_at` gibi kapsam dışı işlemler
test kapsamına alınmaz.

## 3. Test Yaklaşımı

Modül tek bir birim test düzeyinde doğrulanır: `tests/test_dynamic_array.c`,
harici bir test kütüphanesi kullanmadan, bu çözüme özgü bir yardımcı katman
(`test_helpers.h`) üzerinden çalışır. Testler `make test` komutuyla derlenip
çalıştırılır; başarısız bir test sıfırdan farklı çıkış kodu üretir.

Test dosyaları:

```text
tests/
├── test_dynamic_array.c
└── test_helpers.h
```

## 4. Birim Testleri (DYNARR-01–19)

| Kimlik | Fonksiyon | Durum | Beklenen davranış |
|---|---|---|---|
| DYNARR-01 | `init` | Kapasite 4 ile ilklendirme | `SUCCESS`; `size=0`, `capacity=4` |
| DYNARR-02 | `init` | Kapasite 0 ile ilklendirme | `SUCCESS`; `size=0`, `capacity=0` |
| DYNARR-03 | `init` | `arr == NULL` | `INVALID_ARGUMENT` |
| DYNARR-04 | `push_back` | Kapasiteyi aşan art arda 5 ekleme (başlangıç kapasitesi 2) | `SUCCESS`; `size=5`; `capacity >= size`; tüm değerler sırayla korunur |
| DYNARR-05 | `push_back` | `arr == NULL` | `INVALID_ARGUMENT` |
| DYNARR-06 | `push_back` | Kapasite 0 iken ilk ekleme | `SUCCESS`; `size=1`; değer doğru |
| DYNARR-07 | `get` | Geçerli konumdan okuma | `SUCCESS`; değer doğru |
| DYNARR-08 | `get` | Sınır dışı `index` | `OUT_OF_BOUNDS` |
| DYNARR-09 | `get` | `arr == NULL` | `INVALID_ARGUMENT` |
| DYNARR-10 | `get` | `out_value == NULL` | `INVALID_ARGUMENT` |
| DYNARR-11 | `size` | 3 eleman eklendikten sonra sorgulama | `3` döner |
| DYNARR-12 | `size` | `arr == NULL` | `0` döner (durum kodu yok) |
| DYNARR-13 | `remove_at` | Orta konumdan çıkarma (3 elemanlı dizi, index 1) | `SUCCESS`; `size` azalır; kalan elemanlar sırayla korunur |
| DYNARR-14 | `remove_at` | Sınır dışı `index` | `OUT_OF_BOUNDS` |
| DYNARR-15 | `remove_at` | `arr == NULL` | `INVALID_ARGUMENT` |
| DYNARR-16 | `remove_at` | Son elemanı çıkarma | `SUCCESS`; kalan eleman korunur |
| DYNARR-17 | `free` | Elemanlı dizide serbest bırakma | `data=NULL`, `size=0`, `capacity=0` |
| DYNARR-18 | `free` | Kapasitesiz (`capacity=0`) dizide serbest bırakma | `data=NULL`, `capacity=0` (no-op benzeri, güvenli) |
| DYNARR-19 | `free` | `arr == NULL` | Çökme yok; no-op |

## 5. Bellek Güvenliği

Otomatik testler kapsamında bellek sızıntısı denetimi için özel bir araç
entegre edilmemiştir. Bellek sızıntısı ve geçersiz erişim, gerektiğinde
`valgrind ./build/tests/1_basics/02_dynamic_array/test_dynamic_array` ile
elle doğrulanabilir; bu adım CI'a dahil değildir.

## 6. Sürekli Entegrasyon

CI iş akışı `.github/workflows/dynamic-array-ci.yml` dosyasında tanımlıdır:

- `push` (`main`) ve `pull_request` (`main`) olaylarında çalışır.
- `ubuntu-latest` runner'ında `permissions: contents: read` ile çalışır.
- Yalnız `make -C solutions/1_basics/02_dynamic_array test` komutunu çağırır.
- Derleme veya test başarısız olduğunda iş akışı başarısız sayılır.

## 7. Başarı Ölçütleri

- Bütün otomatik testler geçer (19 DYNARR test).
- `make test` sıfır çıkış kodu üretir.
- Test derlemesinde proje tarafından etkinleştirilen uyarılar (`-Wall
  -Wextra -Werror`) oluşmaz.
- `.github/workflows/dynamic-array-ci.yml` `dynamic-array-tests` işini
  tanımlar.
