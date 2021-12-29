/*6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
  Функцию Partition реализуйте методом прохода двумя итераторами от
  начала массива к концу.
  Дано множество целых чисел из [0..10^9] размера n.
  Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
  10%  перцентиль
  медиана
  90%  перцентиль
Требования: к дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.
*/
#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

#define PERCENTILE_10 10
#define MEDIAN 50
#define PERCENTILE_90 90

template <typename T>
bool IsLessDefault(const T& l, const T& r) {
    return l < r;
}

[[maybe_unused]] int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

template <class T>
size_t Partition(T* arr, const size_t l, const size_t r,
                 bool isLess(const T&, const T&) = IsLessDefault) {
    size_t pivot_index = getRandomNumber(static_cast<int>(l), static_cast<int>(r));
    int pivot = arr[pivot_index];

    // меняем последний и пивот местами
    std::swap(arr[pivot_index], arr[r]);

    size_t i = l;
    size_t j = l;
    while (true) {
        while (i < r && (isLess(arr[i], pivot) || arr[i] == pivot)) { ++i; }
        while (j < r && isLess(pivot, arr[j]) || i > j) { ++j; }
        if (j < r && (isLess(arr[j], pivot) || arr[j] == pivot)) {
            std::swap(arr[i], arr[j]);
            ++i;
            ++j;
        } else {
            std::swap(arr[i], arr[r]);
            return i;
        }
    }
}

template <class T>
T KStat(T* arr, size_t l, size_t r, const size_t k,
        bool isLess(const T&, const T&) = IsLessDefault) {
    size_t pivot_pos = Partition(arr, l, r, isLess);
    while (pivot_pos != k) {
        if (k < pivot_pos) {
            r = pivot_pos - 1;
        } else {
            l = pivot_pos + 1;
        }
        // новая пивот позиция
        pivot_pos = Partition(arr, l, r, isLess);
    }
    return arr[pivot_pos];
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int size = 0;
    std::cin >> size;
    int* array = new int[size];

    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }

    std::cout << KStat(array, 0, size - 1, PERCENTILE_10 * size / 100) << std::endl
              << KStat(array, 0, size - 1, MEDIAN * size / 100) << std::endl
              << KStat(array, 0, size - 1, PERCENTILE_90 * size / 100) << std::endl;

    delete[] array;
    return 0;
}
