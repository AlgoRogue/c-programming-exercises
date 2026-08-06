# Hesap Makinesi — Ürün Gereksinimleri Belgesi

## 1. Ürün Vizyonu

Bu proje, kullanıcının komut satırı üzerinden matematiksel hesaplamalar
yapabilmesini sağlayan, zaman içinde yeni işlem türleriyle genişleyebilecek bir
hesap makinesi uygulamasıdır.

Uzun vadede uygulamanın logaritma gibi daha ileri matematiksel işlemleri de
desteklemesi hedeflenmektedir. İlk kullanılabilir sürüm (MVP) ise yalnızca dört
temel aritmetik işleme odaklanır.

## 2. Amaç

MVP'nin amacı, kullanıcının ondalıklı sayılarla temel hesaplamaları güvenilir
ve anlaşılır biçimde yapabilmesini sağlamaktır. Bu sürüm aynı zamanda ileride
eklenecek matematiksel işlemler için sağlam bir başlangıç oluşturmalıdır.

## 3. Hedef Kullanıcı

Komut satırında hızlı ve basit matematiksel hesaplamalar yapmak isteyen
kullanıcılar.

## 4. MVP Kapsamı

MVP aşağıdaki işlemleri destekler:

- Toplama (`+`)
- Çıkarma (`-`)
- Çarpma (`*`)
- Bölme (`/`)

Tüm işlemler ondalıklı sayılarla çalışabilmelidir.

## 5. Kullanıcı Akışı

1. Kullanıcı ilk sayısal değeri girer.
2. Kullanıcı desteklenen işlemlerden birini seçer.
3. Kullanıcı ikinci sayısal değeri girer.
4. Program sonucu gösterir veya oluşan hatayı açıklar.
5. Kullanıcı yeni bir hesaplama yapmayı veya programdan çıkmayı seçer.

## 6. İşlevsel Gereksinimler

- Program iki sayısal değer ve bir işlem kabul etmelidir.
- Program ondalıklı sayıları desteklemelidir.
- Ondalıklı sayılar nokta ile yazılmalıdır (`12.5` gibi).
- Program desteklenen dört işlemi doğru biçimde gerçekleştirmelidir.
- Program hesaplama sonucunu iki ondalık basamakla göstermelidir.
- Program tek oturum içinde art arda hesaplamalar yapılmasına izin vermelidir.
- Program kullanıcının bilinçli olarak çıkış yapabilmesini sağlamalıdır.
- Program geçersiz sayısal girdileri fark etmelidir.
- Program desteklenmeyen işlemleri reddetmelidir.
- Program sıfıra bölmeyi engellemeli ve hatayı açıkça bildirmelidir.
- Düzeltilebilir bir hata, programın beklenmedik biçimde sonlanmasına neden
  olmamalıdır.

## 7. MVP Kapsamı Dışındakiler

Aşağıdaki özellikler ürün vizyonunun parçası olabilir ancak MVP kapsamında
değildir:

- Logaritmik işlemler
- Üs alma ve kök alma
- Trigonometrik işlemler
- Bilimsel gösterimle yazılan sayılar (`1.5e3` gibi)
- Sonsuzluk ve sayı olmayan değerler (`inf` ve `nan`)
- Virgülün ondalık ayırıcı olarak kullanılması (`12,5` gibi)
- Parantezli veya birden fazla işlem içeren ifadeler
- İşlem geçmişi
- Grafik kullanıcı arayüzü
- Sonuçların kalıcı olarak saklanması

## 8. Kabul Ölçütleri

- Pozitif, negatif ve ondalıklı sayılarla dört temel işlem yapılabilmelidir.
- Geçersiz sayı girdilerinde yanıltıcı bir sonuç gösterilmemelidir.
- Desteklenmeyen bir işlem seçildiğinde kullanıcı bilgilendirilmelidir.
- Sıfıra bölme girişimi sonucu program sonlanmamalıdır.
- Kullanıcı bir hata sonrasında veya başarılı bir hesaplamadan sonra yeni
  bir işlem yapabilmelidir.
- Kullanıcı istediğinde programdan normal biçimde çıkabilmelidir.
- Başarılı hesaplama sonuçları iki ondalık basamakla gösterilmelidir.
