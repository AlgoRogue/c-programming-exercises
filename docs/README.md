# Doxygen Belgelendirme Rehberi

Bu depo, kaynak koddan HTML belgeleri oluşturmak için Doxygen kullanır.
Kaynak kod yorumları ve `Doxyfile`, belgelediği kodla birlikte `main` dalında
tutulur. Üretilen HTML dosyaları ise yayın aşamasında `doxygen-docs` dalına
aktarılır.

## Gerekli Araçlar

- Doxygen
- Graphviz

macOS ve Homebrew kullanıyorsanız araçları şu komutla kurabilirsiniz:

```bash
brew install doxygen graphviz
```

## Belgeleri Oluşturma

Depo kök dizininde aşağıdaki komutu çalıştırın:

```bash
make docs
```

Oluşturulan belgelerin başlangıç sayfası:

```text
build/docs/doxygen/html/index.html
```

## Oluşturulan Dosyaları Temizleme

```bash
make docs-clean
```

`build/` dizini Git tarafından izlenmez. Bu nedenle yerel olarak oluşturulan
HTML dosyaları yanlışlıkla `main` dalına eklenmez.

## Dal Düzeni

- `main`: Kaynak kod, Doxygen yorumları, `Doxyfile` ve bu rehber
- `doxygen-docs`: GitHub Pages için üretilmiş HTML dosyaları

Belgeler aşağıdaki adreste yayındadır:

<https://algorogue.github.io/c-programming-exercises/>

GitHub Pages, `doxygen-docs` dalının kök dizininden yayın yapar. Bu dala
gönderilen her yeni belge sürümü otomatik olarak yeniden yayımlanır. Doxygen
çıktısının `main` dalından üretilip `doxygen-docs` dalına aktarılması ise
şu anda elle yapılır; ileride ayrı bir otomasyon eklenebilir.
