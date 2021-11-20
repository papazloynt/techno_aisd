/*3_2. Реализовать дек с динамическим зацикленным буфером.
Требования: Дек должен быть реализован в виде класса.*/

#include <iostream>
#include <algorithm>

template <typename T>
class Deque{
public:
    Deque();
    Deque(const Deque& deq) = delete;
    ~Deque();

    Deque& operator = (const Deque&) = delete;

    bool empty();
    void reserve(size_t tmp_size);

    // front
    void push_front(const T& el);
    void pop_front();

    // back
    void push_back(const T& el);
    void pop_back();

    T front();
    T back();

private:
    T* buffer;
    int head;
    int tail;

    size_t size;
    size_t capacity;
    const size_t start_capacity = 2;
};

template <typename T>
Deque<T>::Deque() : size(0), capacity(0), buffer(nullptr),
                    head(0), tail(0)  {}

template <typename T>
Deque<T>::~Deque() {
    delete[] buffer;
}

template <typename T>
bool Deque<T>::empty() {
    if (size)
        return false;
    return true;
}

template <typename T>
void Deque<T>::reserve(const size_t tmp_size) {
    if (tmp_size != 0) {
        T* tmp_buffer = new T[tmp_size];

        if (head < tail) {
            std::copy(buffer + head, buffer + tail, tmp_buffer);
        }
        else {
            std::copy(buffer + head, buffer + capacity, tmp_buffer);
            std::copy(buffer, buffer + tail, tmp_buffer + capacity - head);
        }

        // Delete trash
        delete[] buffer;

        // Initialization
        buffer = tmp_buffer;
        head = 0;
        tail = size;
        capacity = tmp_size;
    } else {
        // Start numbers of elements is 2;
        buffer = new T[start_capacity];
        capacity = start_capacity;
        head = tail = 0;
    }
}

template <typename T>
void Deque<T>::push_front(const T& el) {
    if (size == capacity) {
        // The most optimal variant of multiplication by 2
        reserve(capacity * 2);
    }
    if (!empty()) {
        if (head == 0) {
            head = capacity;
        }
        buffer[--head] = el;
    } else {
        buffer[head] = el;
        ++tail;
    }
    ++size;
}

template <typename T>
void Deque<T>::pop_front() {
    if (!empty()) {
        head = (head + 1) % capacity;
        --size;
    }
}

template <typename T>
void Deque<T>::push_back(const T &el) {
    if (size == capacity) {
        // The most optimal variant of multiplication by 2
        reserve(capacity * 2);
    }

    tail %= capacity;
    buffer[tail++] = el;
    ++size;
}

template <typename T>
void Deque<T>::pop_back() {
    if (!empty()) {
        if (tail == 0) {
            tail = capacity;
        }
        --tail;
        --size;
    }
}

template <typename T>
T Deque<T>::front() {
    return buffer[head];
}

template <typename T>
T Deque<T>::back() {
    return tail == 0 ? buffer[capacity - 1] : buffer[tail - 1];
}

int main() {
    Deque<int> deque;
    int n, command, number;
    bool flag = true;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> command >> number;
        switch (command) {
            case 1:
                deque.push_front(number);
                break;
            case 2:
                if (deque.empty()) {
                    if (number != -1) {
                        flag = false;
                    }
                } else {
                    int tmp = deque.front();
                    deque.pop_front();
                    if (number != tmp) {
                        flag = false;
                    }
                }
                break;
            case 3:
                deque.push_back(number);
                break;
            case 4:
                if (deque.empty()) {
                    if (number != -1) {
                        flag = false;
                    }
                }
                else {
                    int n = deque.back();
                    deque.pop_back();
                    if (number != n) {
                        flag = false;
                    }
                }
            default:
                break;
        }
    }

    if (!flag) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES";
    }

    std::cout << std::endl;

    return 0;
}