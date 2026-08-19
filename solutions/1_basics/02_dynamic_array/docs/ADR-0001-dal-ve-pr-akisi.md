# ADR-0001: Dal ve PR akışı ile geliştirme

## Durum

Kabul edildi.

## Bağlam

`01_calculator` çözümünde geliştirme, dal + PR akışıyla ilerleyip `main`'e
PR ile birleştirildi (PR #5). `02_dynamic_array` çözümünün ilk beş
fonksiyonu (`init`, `push_back`, `get`, `size`, `remove_at`) ise doğrudan
`main`'e commit edilerek geliştirildi (commit `aeca06d`, oturum 8) — bu,
depoda o ana kadar süregelen fiili kalıptı.

`dynamic_array_free` fonksiyonuna geçilirken kullanıcı, bu iş için ayrı bir
dal (`feature/dynamic-array-free`) açıp PR (#6) ile `main`'e birleştirme
akışını seçti; bu, önceki oturumlardaki doğrudan `main`'e commit kalıbından
kasıtlı bir sapmaydı.

## Karar

Bundan sonra bu depoda kod geliştirme `main` üzerinde doğrudan yapılmaz.
Her spec kendi dalında geliştirilir, `main`'e PR ile girer, merge sonrası
dal silinir. Küçük depo bakımı (belge, yapılandırma değişiklikleri) bu
kuralın dışındadır ve doğrudan `main`'de yapılabilir.

Bu karar, kullanıcının kalıcı hafıza sisteminde (`core/preferences`) genel
bir çalışma tercihi olarak da kayıtlıdır; bu ADR, kararın bu spesifik
çözüm bağlamındaki gerekçesini ve geçiş noktasını belgeler.

## Sonuçlar

- PR akışı, gözden geçirme noktası ekler ve geri alma maliyetini düşürür.
- `01_calculator` ve `02_dynamic_array`'in ilk beş fonksiyonu bu kararın
  gerisinde kalmıştır; geriye dönük olarak dallara taşınmamıştır çünkü
  zaten `main`'e merge edilmiş durumdaydı.
- Sonraki her spec (ör. yeni bir problem çözümü) bu akışı baştan
  uygulayacaktır.
