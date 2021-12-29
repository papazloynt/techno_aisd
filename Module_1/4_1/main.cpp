/* 4.1 Слияние массивов.
Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
Требования: время работы O(N * logK). Ограничение на размер кучи O(K). */
#include <iostream>
#include <cassert>

template <class T>
struct DArray{
    DArray() :
            arr(nullptr), size(0), capacity(0) {};

    DArray(int _cap) :
            size(0), capacity(_cap) {
        arr = new T[capacity];
    }

    DArray(const DArray& d_a) :
            size(d_a.size), capacity(d_a.capacity) {
        arr = new T[capacity];
        std::copy(d_a.arr, d_a.arr + size, arr);
    };

    ~DArray() {
        if(arr) {
            delete[] arr;
            arr = nullptr;
        }
    }

    T& operator[] (const int index){
        assert(index >= 0 && index < size);

        return arr[index];
    }

    DArray& operator=(const DArray& d_a) {
        if (&d_a != this) {
            if (capacity != 0) {
                delete[] arr;
                size = 0;
                capacity = 0;
            }
            arr = new T[d_a.capacity];
            std::copy(d_a.arr, d_a.arr + size, arr);
            size = d_a.size;
            capacity = d_a.capacity;
        }
        return *this;
    }

    void add(const T& el){
        if (size + 1 > capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            std::copy(arr, arr + size, new_arr);
            delete[] arr;
            arr = new_arr;
        }
        arr[size++] = el;
    }

    [[nodiscard]] bool empty() const{
        return size == 0;
    }

    [[nodiscard]] T last() const{
        return arr[size - 1];
    }

    void delete_last(){
        --size;
    }

    T* arr;
    int size;
    int capacity;
};

template <class T>
class Heap {
public:
    explicit Heap(bool (*comp) (const T&, const T&) = isLessDefault);
    explicit Heap(const DArray<T>& _arr, bool (*comp) (const T&, const T&) = isLessDefault);
    ~Heap() = default;

    //Добавление в кучу элемента O(log n)
    void Insert(const T& el);

    //Извлечь максимум из кучи за O(log n)
    T ExtractMax();

    // Посмотреть значение максимума в куче за О(1)
    T PeekMax();

    static bool isLessDefault (const T& l, const T& r){
        return l <= r;
    }

    bool IsEmpty() {
        return arr.size == 0;
    }
private:
    DArray<T> arr;

    bool (*isLess) (const T&, const T&);

    void buildHeap();
    void siftDown(int i);
    void siftUp(int i);
};


template <class T>
Heap<T>::Heap(bool (*comp) (const T&, const T&)) :
        arr(), isLess(comp) {}

template <class T>
Heap<T>::Heap(const DArray<T>& _arr, bool (*comp) (const T&, const T&)) :
        arr(_arr), isLess(comp) { buildHeap(); }

template <class T>
void Heap<T>::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
    int largest = i;
    if( left < arr.size && isLess(arr[i], arr[left]) )
        largest = left;
    if( right < arr.size && isLess(arr[largest], arr[right]))
        largest = right;
// Если больший сын есть, то проталкиваем корень в него.
    if( largest != i ) {
        std::swap( arr[i], arr[largest] );
        siftDown( largest );
    }
}

// Построение кучи.
template <class T>
void Heap<T>::buildHeap() {
    for( int i = arr.size/2 - 1; i >= 0; --i){
        siftDown( i );
    }
}

template <class T>
void Heap<T>::siftUp( int index ) {
    while( index > 0 ) {
        int parent = ( index - 1) / 2;
        if( isLess(arr[index], arr[parent]) )
            return;
        std::swap( arr[index], arr[parent] );
        index = parent;
    }
}

template <class T>
void Heap<T>::Insert(const T& element ) {
    arr.add( element );
    siftUp( arr.size - 1 );
}

template <class T>
T Heap<T>::ExtractMax() {
    assert( !arr.empty() );
// Запоминаем значение корня.
    T result = arr[0];
// Переносим последний элемент в корень.
    arr[0] = arr.last();
    arr.delete_last();
// Вызываем SiftDown для корня.
    if( !arr.empty() ) {
        siftDown( 0 );
    }
    return result;
}

template <class T>
T Heap<T>::PeekMax() {
    assert (!arr.empty());
    return arr[0];
}

// Храним тройку:
// el - элемент массива
// i - номер массива откуда взяли
// pos - позиция элемента в i-ом массиве
struct SolveType {
    int el;
    int i;
    int pos;

    SolveType() : el(-1), i(-1), pos(-1) {}
    SolveType(int el_, int i_, int pos_) : el(el_), i(i_), pos(pos_) {}
};

static bool isLessSolveType (const SolveType& l, const SolveType& r){
    return l.el >= r.el;
}

int main() {
    int number_arrays;
    std::cin >> number_arrays;
    // массив массивов
    DArray<int>* arrays = new DArray<int>[number_arrays];

    for (int i = 0; i < number_arrays; ++i) {
        int array_size;
        std::cin >> array_size;
        arrays[i] = DArray<int>(array_size);
        for (int j = 0; j < array_size; ++j) {
            int push_el;
            std::cin >> push_el;
            arrays[i].add(push_el);
        }
    }

    DArray<SolveType> fill_heap(number_arrays);

    for (int i = 0; i < number_arrays; ++i) {
        fill_heap.add({arrays[i][0], i, 0});
    }

    Heap<SolveType> tree(fill_heap, isLessSolveType);

    while (!tree.IsEmpty()) {
        SolveType node = tree.ExtractMax();
        std::cout << node.el << " ";
        if (node.pos < arrays[node.i].size - 1) {
            tree.Insert({arrays[node.i][node.pos + 1], node.i, node.pos + 1});
        }
    }

    delete[] arrays;

    return 0;
}
