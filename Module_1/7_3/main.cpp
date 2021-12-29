/*7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел.
 Количество чисел не больше 10^6.
 Отсортировать массив методом MSD по битам (бинарный QuickSort).*/
#include <iostream>

typedef unsigned long long ullong;

// Проверяем текущую позицию бита на равенство нулю
bool isNull(ullong number, int current_index) {
    return number & ((ullong)1 << current_index);
}

void binaryQuickSort(ullong* arr, int l, int r, int index) {
    if (r <= l || index < 0) { return; }
    int i = l , j = r;
    // Упорядочиваем текущий разряд, сначала нули, заием еденицы
    while(j != i) {
        while ( !isNull(arr[i], index) && (i < j) ) { ++i; }
        while ( isNull(arr[j], index) && (j > i) ) { --j; }
        std::swap(arr[i], arr[j]);
    }
    if ( !isNull(arr[r], index) ) { ++j; }
    // Рекурсивно выполняем для остальных разрядов чисел
    binaryQuickSort(arr, l, j - 1, index - 1);
    binaryQuickSort(arr, j, r, index - 1);
}

int main() {
    int size;
    std::cin >> size;
    auto* arr = new ullong[size];

    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    // Константная переменная для просмотра разрядов чисел
    // Начальная позиция константная,
    // её значение можно получить сдвинув поразрядно еденицу на 63 бита влево
    const int BITCHECK = 64 - 1;
    binaryQuickSort(arr, 0, size - 1, BITCHECK);

    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
    delete[] arr;
    return 0;
}
