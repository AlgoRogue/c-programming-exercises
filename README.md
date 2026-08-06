# 🎯 C Programlama Alıştırmaları

Bu depo, C programlama dilini öğrenirken profesyonel yazılım geliştirme
uygulamalarını deneyimlemek için oluşturulmuştur. Her problem, karmaşıklık
düzeyinden bağımsız olarak, gerçek bir yazılım projesi ciddiyetiyle ele alınır.

## 🌟 Depo Yaklaşımı

- Her alıştırmada profesyonel yazılım geliştirme standartları uygulanır.
- Bakımı kolay, belgelenmiş ve test edilmiş kod yazmaya odaklanılır.
- Programlama kavramları ile yazılım mühendisliği uygulamaları birlikte öğrenilir.
- Problem tanımları, ne yapılması gerektiğini ve bunun neden değerli
  olduğunu açıklar.
- Uygulamanın nasıl geliştirileceği, geliştiricinin kararına ve
  yaratıcılığına bırakılır.

## 📂 Depo Yapısı

```text
c-programming-exercises/
├── problems/               # Problem tanımları ve gereksinimler
│   ├── 1_basics/           # Temel C programlama kavramları
│   ├── 2_intermediate/     # Sistem programlamaya giriş
│   └── 3_advanced/         # Ağ ve ileri sistem programlama
└── solutions/              # Problemlerin gerçekleştirilmiş çözümleri
    ├── 1_basics/           # Temel problemlerin çözümleri
    ├── 2_intermediate/     # Orta düzey problemlerin çözümleri
    └── 3_advanced/         # İleri düzey problemlerin çözümleri
```

Numaralandırılmış zorluk klasörleri, önerilen öğrenme sırasını gösterir.
Her klasörün içindeki alıştırmalar da numaralandırılır. Aynı zorluk
düzeyinde yer alan problemler arasında da kademeli bir karmaşıklık artışı
olabilir.

## 🏗️ Profesyonel Standartlar

Zorluk düzeyinden bağımsız olarak her çözümün aşağıdaki nitelikleri
göstermesi beklenir:

1. **📚 Belgelendirme**
   - Kapsamlı Doxygen belgeleri
   - Anlaşılır fonksiyon ve modül açıklamaları
   - Kullanım örnekleri ve rehberler
   - `main` dalında tutulan belge kaynakları
   - `doxygen-docs` dalında yayımlanan HTML belgeleri
   - [GitHub Pages](https://algorogue.github.io/c-programming-exercises/)
     üzerinden çevrim içi belgeler

2. **🔧 Kod Düzeni**
   - Başlık dosyaları (header files) kullanan modüler bir tasarım
   - Sorumlulukların anlaşılır biçimde ayrılması
   - Tutarlı bir kodlama biçimi

3. **🧪 Test**
   - Seçilen tasarıma uygun otomatik testler
   - Testlerin tek komutla çalıştırılabilmesi
   - Sınır durumlarının (edge cases) ele alınması

4. **⚙️ Derleme Sistemi**
   - Derleme ve test işlemleri için Makefile
   - Anlaşılır derleme talimatları
   - Farklı platformlarla uyumluluk

5. **📝 Sürüm Kontrolü**
   - Kod için `main` dalı
   - Üretilmiş Doxygen HTML belgeleri için `doxygen-docs` dalı
   - Yapılan değişikliği açıklayan değişiklik kaydı (commit) mesajları
   - Geliştirme sırasında özellik dallarının (feature branches) kullanılması

## 📊 Zorluk Düzeyleri

### 🌱 Temel — C Programlamanın Temelleri

- Temel C kavramlarına odaklanır.
- Her problem, depo standartlarına uygun tam bir proje olarak ele alınır.
- Örnek konular:
  - Modüler hesap makinesi
  - Testleri bulunan sıcaklık dönüştürücü
  - Bellek yönetimini dikkate alan kelime sayacı

### 🌿 Orta — Sistem Programlama

- Sistem programlama kavramlarına odaklanır.
- Dosya işlemleri, bellek yönetimi ve veri yapılarını kapsar.
- Örnek konular:
  - Dosya işlemleri kullanan telefon rehberi
  - Basit bir veri tabanı gerçekleştirimi
  - Özel veri yapıları

### 🌳 İleri — Ağ Programlama

- Soket programlama
- Çok iş parçacıklı programlama (multithreading)
- Süreçler arası iletişim (inter-process communication)
- Örnek konular:
  - Sohbet uygulaması
  - Web sunucusu
  - FTP istemcisi

## 📁 Çözümlerin Konumu

Her çözüm, ait olduğu problemin numaralandırılmış yolunu takip eder.
Örneğin:

```text
problems/1_basics/01_calculator.md
solutions/1_basics/01_calculator/
```

Modüller, uygulama programlama arayüzleri (API), veri türleri ve test yaklaşımı
dâhil olmak üzere çözümün iç yapısı geliştiriciye aittir. Seçilen yapının
deponun kalite standartlarını karşılaması yeterlidir.

## 🚀 Başlangıç

1. Depoyu klonlayın:

   ```bash
   git clone https://github.com/AlgoRogue/c-programming-exercises.git
   ```

2. Uygun zorluk düzeyinden bir problem seçin.
3. Problemin amacını ve gereksinimlerini dikkatlice okuyun.
4. Kendi tasarım kararlarınızla çözümü geliştirin.
5. Çözümü derleyin ve test edin:

   ```bash
   cd proje_dizini
   make
   make test
   ```

## 🛠️ Gereksinimler

- GCC derleyicisi
- GNU Make
- Git
- Doxygen
- Temel komut satırı bilgisi

## 📖 Belgelendirme

- Belgeler `make docs` komutuyla yerel olarak oluşturulabilir. Ayrıntılar için
  [`docs/README.md`](docs/README.md) dosyasına bakın.
- [GitHub Pages üzerindeki çevrim içi belgeler](https://algorogue.github.io/c-programming-exercises/)
- Her proje ayrıntılı gereksinimler ve kullanım rehberleri içerir.
- Uygulama kararları ve önemli ayrıntılar belgelenir.
- Derleme ve test talimatları çözümle birlikte sunulur.

## 🤝 Katkıda Bulunma

Katkılar kabul edilir. Bir katkının:

1. Deponun yerleşik düzenini takip etmesi,
2. Gerekli belgeleri içermesi,
3. Yeterli otomatik testlere sahip olması,
4. Deponun profesyonel standartlarını koruması beklenir.

## 📄 Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Ayrıntılar için `LICENSE` dosyasına
bakın.

## 📫 İletişim

Soru ve öneriler için:

- GitHub: [@AlgoRogue](https://github.com/AlgoRogue)
