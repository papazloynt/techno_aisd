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

int bin_search(int left, int right, int el, const Array& A) {
    if (right >= left) {
        int middle = left + (right - left) / 2;
        if (el == A.arr[middle]) {
            if (middle > A.size - 1)
                return -1;
            return middle;
        }
        if (el > A.arr[middle]) {
            return bin_search(middle + 1, right, el, A);
        }
        return bin_search(left, middle - 1, el, A);
    }
    return -1;
}

int exponential_search(int& left, const int el, const Array& A) {
    if (el <= A.arr[left]) return left;
    // + 1, чтобы избавиться от бесконечного цикла, когда left = 0;
    int tmp_right = left + 1;
    // Чтобы не было выхода за пределы массива A[...]
    while (tmp_right < A.size && el > A.arr[tmp_right >= A.size ? A.size - 1 : tmp_right]){
        left = tmp_right;
        tmp_right *= 2;
    }
    if (tmp_right >= A.size) {
        tmp_right = A.size - 1;
    }
    return tmp_right;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
