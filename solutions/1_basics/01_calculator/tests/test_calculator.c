#include <stdio.h>
#include <math.h>
#include "calculator.h"

// Çıktıların tolerans aralığında eşit olup olmadığını kontrol eden yardımcı sabit
#define TOLERANS 1e-9

int main(void)
{
    double result = 0.0;
    enum CalcStatus status;

    // --- TEST 1: CALC-01 (İki pozitif sayıyı toplama) ---
    status = calculate(3.0, 4.0, TOPLA, &result);

    if (status != CALC_BASARILI || fabs(result - 7.0) >= TOLERANS)
    {
        printf("HATA: CALC-01 (Toplama) testi başarısız oldu!\n");
        return 1; // 1 döndürerek terminale/Makefile'a testin kaldığını bildiriyoruz
    }

    printf("CALC-01 Testi Başarılı!\n");

    // Tüm testler geçtiyse 0 (başarılı) döndür
    return 0;
}
