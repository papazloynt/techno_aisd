/*1.2 Вернуть значение бита в числе N по его номеру K.*/

#include <iostream>

int main() {
    unsigned int n;
    unsigned int k;
    std::cin >> n >> k;

    std::cout << ((n >> k ) & 1);
    return 0;
}
