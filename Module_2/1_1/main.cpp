/* 1_2. Для разрешения коллизий используйте двойное хеширование. */
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#define PRIME_1 11
#define PRIME_2 13

template <class T>
unsigned int hash1(const T& keys, size_t size) {
    unsigned int hash = 0;
    for (int i = 0; i < keys.size(); ++i) {
        hash += (PRIME_1 * hash + keys[i]) % size;
    }
    return hash % size;
}

template<class T>
unsigned int hash2(const T& keys, size_t size) {
    unsigned int hash = 0;
    for (int i = 0; i < keys.size(); ++i) {
        hash += (PRIME_2 * hash + keys[i]) % size;
    }
    return (hash * 2 + 1) % size;
}

template <class T>
class HashTable {
public:
    explicit HashTable();

    HashTable(const HashTable& table) = delete;
    HashTable& operator=(const HashTable& table) = delete;

    ~HashTable() = default;

    bool Add(const T& data);
    bool Has(const T& data);
    bool Delete(const T& data);

private:
    struct HashTableElement {
        T Data;
        enum Status {
            empty,
            deleted,
            key
        } st;

        HashTableElement() : Data(), st(empty) {}
        HashTableElement(const T data) : Data(data), st(key) {}
    };

    void growTable();

    std::vector<HashTableElement> table;
    int keysCount;
};

template <class T>
HashTable<T>::HashTable() : keysCount(0) {
    table.resize(8);
}

template <class T>
bool HashTable<T>::Add(const T &data) {
    if (keysCount / (float)table.size() >= 0.75){
        growTable();
    }

    unsigned int i = 0, j = 0;
    int DelPos = -1;

    unsigned int h1 = hash1(data, table.size());
    unsigned int h2 = hash2(data, table.size());

    while (table[h1].st != HashTableElement::empty && i < table.size()) {
        if (table[h1].Data == data && table[h1].st != HashTableElement::deleted) {
            return false;
        }
        if (table[h1].st == HashTableElement::deleted && j != 1) {
            DelPos = static_cast<int>(h1);
            ++j;
        }
        h1 = (h1 + h2) % table.size();
        ++i;
    }

    if (DelPos != -1) {
        table[DelPos] = HashTableElement(std::move(data));
    } else {
        table[h1] = HashTableElement(std::move(data));
    }
    ++keysCount;
    return true;
}

template <class T>
bool HashTable<T>::Has(const T &data) {
    unsigned int i = 0;
    unsigned int h1 = hash1(data, table.size());
    unsigned int h2 = hash2(data, table.size());

    while (table[h1].st != HashTableElement::empty && i < table.size()){
        if (table[h1].Data == data && table[h1].st != HashTableElement::deleted){
            return true;
        }
        h1 = (h1 + h2) % table.size();
        ++i;
    }
    return false;
}

template <class T>
bool HashTable<T>::Delete(const T &data) {
    unsigned int i = 0;
    unsigned int h1 = hash1(data, table.size());
    unsigned int h2 = hash2(data, table.size());

    while (table[h1].st != HashTableElement::empty && i < table.size()){
        if (table[h1].Data == data && table[h1].st != HashTableElement::deleted){
            table[h1].st = HashTableElement::deleted;
            --keysCount;
            return true;
        }
        h1 = (h1 + h2) % table.size();
        ++i;
    }
    return false;
}

template <class T>
void HashTable<T>::growTable() {
    std::vector<HashTableElement> tmp_table;
    // Для степеней двоек
    tmp_table.resize(table.size() * 2);
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].st != HashTableElement::empty && table[i].st != HashTableElement::deleted) {
            int h1 = hash1(table[i].Data, tmp_table.size());
            int	h2 = hash2(table[i].Data, tmp_table.size());
            size_t j = 0;
            while (tmp_table[h1].st != HashTableElement::empty && j < tmp_table.size()) {
                h1 = (h1 + h2) % tmp_table.size();
                ++j;
            }
            tmp_table[h1] = table[i];
        }
        table[i].st = HashTableElement::empty;
    }
    table = std::move(tmp_table);
}

int main() {
    HashTable<std::string> table;
    while (true) {
        char command = 0;
        std::string value;
        std::cin >> command >> value;
        if (std::cin.fail()) {
            break;
        }
        switch (command) {
            case '?':
                std::cout << ( table.Has( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '+':
                std::cout << ( table.Add( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '-':
                std::cout << ( table.Delete( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            default:
                assert(false);
        }
    }

    return 0;
}
