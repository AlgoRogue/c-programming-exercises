#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

struct DynamicArray
{
    int *data;
    size_t size;
    size_t capacity;
};

enum DynArrayStatus
{
    DYN_ARRAY_STATUS_SUCCESS,
    DYN_ARRAY_STATUS_OUT_OF_BOUNDS,
    DYN_ARRAY_STATUS_ALLOCATION_FAILURE,
    DYN_ARRAY_STATUS_INVALID_ARGUMENT
};

/**
 * @brief Dinamik diziyi verilen başlangıç kapasitesiyle ilklendirir.
 *
 * @param arr İlklendirilecek dizi; `NULL` verildiğinde
 *            `DYN_ARRAY_STATUS_INVALID_ARGUMENT` döner.
 * @param initial_capacity Başlangıç kapasitesi.
 *
 * @return İşlemin durum kodu.
 */
enum DynArrayStatus dynamic_array_init(struct DynamicArray *arr, size_t initial_capacity);

/**
 * @brief Dizinin sonuna bir eleman ekler; gerekirse kapasiteyi büyütür.
 *
 * @param arr Üzerinde işlem yapılacak dizi.
 * @param value Eklenecek değer.
 *
 * @return İşlemin durum kodu.
 */
enum DynArrayStatus dynamic_array_push_back(struct DynamicArray *arr, int value);

/**
 * @brief Belirtilen konumdaki elemanı diziden çıkarır.
 *
 * @param arr Üzerinde işlem yapılacak dizi.
 * @param index Çıkarılacak elemanın konumu.
 *
 * @return İşlemin durum kodu.
 */
enum DynArrayStatus dynamic_array_remove_at(struct DynamicArray *arr, size_t index);

/**
 * @brief Belirtilen konumdaki elemanın değerini okur.
 *
 * @param arr Sorgulanacak dizi.
 * @param index Okunacak elemanın konumu.
 * @param out_value Değerin yazılacağı işaretçi.
 *
 * @return İşlemin durum kodu.
 */
enum DynArrayStatus dynamic_array_get(const struct DynamicArray *arr, size_t index, int *out_value);

/**
 * @brief Dizideki geçerli eleman sayısını döner.
 *
 * @param arr Sorgulanacak dizi.
 *
 * @return Eleman sayısı.
 */
size_t dynamic_array_size(const struct DynamicArray *arr);

/**
 * @brief Dizinin kullandığı belleği serbest bırakır.
 *
 * @param arr Serbest bırakılacak dizi.
 */
void dynamic_array_free(struct DynamicArray *arr);

#endif // DYNAMIC_ARRAY_H
