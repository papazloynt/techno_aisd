/*2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
 * значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
 * Найти m за O(log m).
 * Требования:  Время работы O(log m). Внимание!
 * В этой задаче сначала нужно определить диапазон для бинарного поиска размером
 * порядка m с помощью экспоненциального поиска,
 * а потом уже в нем делать бинарный поиск.*/
#include <iostream>

struct Array{
    int* arr;
    int size = 0;

    Array(const int n) : size(n) {
        arr = new int[n];
    }

    ~Array(){
        delete [] arr;
    }
};

int bin_search(const Array& a, int left, int right) {
    int mid = left + (right - left) / 2;
    if (a.arr[mid] > a.arr[mid + 1] &&
        a.arr[mid] > a.arr[mid - 1])
        return mid;

    if (a.arr[mid] > a.arr[mid + 1])
        return bin_search(a, left, mid);
    return bin_search(a, mid + 1, right);
}

// Search Interval
int exponential_search(const Array& a) {
    // check size = 2
    if (a.size == 1) {
        if (a.arr[0] < a.arr[1])
            return 1;
        return 0;
    }

    // if seq is up always
    if (a.arr[0] > a.arr[1]) { return 0; }

    // if seq is down always
    if (a.arr[a.size - 2] < a.arr[a.size - 1]) { return a.size - 1; }

    int tmp_left = 1;
    while (tmp_left < a.size - 1) {
        if (a.arr[tmp_left - 1] > a.arr[tmp_left]) {
            return bin_search(a, tmp_left / 2, tmp_left);
        } else if (a.arr[tmp_left] > a.arr[tmp_left + 1]) {
            return tmp_left;
        } else
            tmp_left *= 2;
    }
    return bin_search(a, tmp_left / 2, a.size - 1);
}

int main() {
    int size = 0;
    std::cin >> size;
    Array a(size);

    for (int i = 0; i < size; ++i)
        std::cin >> a.arr[i];

    std::cout << exponential_search(a) << std::endl;
    return 0;
}
