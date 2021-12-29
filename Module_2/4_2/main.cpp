/*
 4_2. Порядковые статистики. Дано число N и N строк. Каждая строка
 содержит команду добавления или удаления натуральных чисел, а также
 запрос на получение k-ой порядковой статистики. Команда добавления числа A
 задается положительным числом A, команда удаления числа A задается
 отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики
 задается числом k.
 Требования: скорость выполнения запроса - O(log n).
*/

#include <iostream>
#include <utility>
#include <stack>

template <class T>
bool compare (const T& l, const T& r){
    return l < r;
}

template <class T>
class AvlTree {
public:
    explicit AvlTree(bool _func (const T&, const T&));
    ~AvlTree();

    void Insert(T key);
    void Remove(T key);
    [[nodiscard]] int GetStatistic(int s) const;

private:
    struct Node {
        T key;
        unsigned char height;
        int size;
        Node* left;
        Node* right;
        explicit Node(T _key) : key(_key), height(1), size(1),
                                left(nullptr), right(nullptr) {}
    };
    // func for work with height
    unsigned char height(Node* ptr) const ;
    int balanceFactor(Node* ptr) const ;
    void fixHeight(Node* ptr);

    // For ex.
    int getSize(Node* ptr) const ;
    void fixSize(Node* ptr);

    // Tiny Rotate
    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* q);

    // Balance using rotate
    Node* balance(Node* p);

    // Insert using balance
    Node* insert(Node*& ptr, T key );

    // Remove help function
    std::pair<Node*, Node*> minFindRemove(Node* ptr);

    // Remove!!!
    Node* remove(Node* ptr, T key);

    // root
    Node* root;
    bool (*comp)(const T&, const T&);
};

template <class T>
AvlTree<T>::AvlTree(bool _func (const T&, const T&)) : root(nullptr), comp(_func) {}

template <class T>
AvlTree<T>::~AvlTree() {
    if (root == nullptr) return;
    std::stack<Node*> st;
    Node* current = root;
    Node* lastNodeVisited = nullptr;
    while (!st.empty() || current != nullptr) {
        if (current != nullptr) {
            st.push( current );
            current = current->left;
        } else {
            current = st.top();
            //Если нету правого элемента, то удаляем данный, если он есть, то идём к нему
            if (current->right != nullptr && lastNodeVisited != current->right) {
                current = current->right;
            } else {
                st.pop();
                lastNodeVisited = current;
                delete current;
                current = nullptr;
            }
        }
    }
}

template <class T>
void AvlTree<T>::Insert(T key) {
    root = insert(root, key);
}

template <class T>
void AvlTree<T>::Remove(T key) {
    root = remove(root, key);
}

template <class T>
unsigned char AvlTree<T>::height(Node* ptr) const {
    return ptr != nullptr ? ptr->height : 0;
}

template <class T>
int AvlTree<T>::balanceFactor(Node* ptr) const {
    return height(ptr->right) - height(ptr->left);
}

template <class T>
void AvlTree<T>::fixHeight(Node* ptr) {
    unsigned char hl = height(ptr->left);
    unsigned char hr = height(ptr->right);
    ptr->height = (hl > hr ? hl : hr) + 1;
}

template <class T>
int AvlTree<T>::getSize(Node* ptr) const {
    return ptr != nullptr ? ptr->size : 0;
}

template <class T>
void AvlTree<T>::fixSize(Node* ptr) {
    ptr->size = getSize(ptr->left) + getSize(ptr->right) + 1;
}

template <class T>
typename AvlTree<T>::Node* AvlTree<T>::rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;

    fixHeight(p);
    fixSize(p);

    fixHeight(q);
    fixSize(q);

    return q;
}

template <class T>
typename AvlTree<T>::Node* AvlTree<T>::rotateLeft(Node *q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;

    fixHeight(q);
    fixSize(q);

    fixHeight(p);
    fixSize(p);

    return p;
}

template <class T>
typename AvlTree<T>::Node* AvlTree<T>::balance(Node* p) {
    fixHeight(p);
    fixSize(p);
    if (balanceFactor(p) == 2) {
        if (balanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (balanceFactor(p) == -2) {
        if (balanceFactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

template <class T>
typename AvlTree<T>::Node* AvlTree<T>::insert(Node*& ptr, T key) {
    if (ptr == nullptr) {
        return ptr = new Node(key);
    }
    if (comp(key, ptr->key)){
        ptr->left = insert(ptr->left, key);
    } else {
        ptr->right = insert(ptr->right, key);
    }
    return balance(ptr);
}


// Первый элемент - указатель на узел с удалённым элементом,
// Второй элемент - минимальный
template <class T>
std::pair<typename AvlTree<T>::Node*, typename AvlTree<T>::Node*> AvlTree<T>::minFindRemove(Node* ptr) {
    if (ptr->left == nullptr) {
        return std::make_pair(ptr->right, ptr);
    }
    std::pair<Node*, Node*> tmp_pair = minFindRemove(ptr->left);
    ptr->left = tmp_pair.first;
    return std::make_pair(balance(ptr), tmp_pair.second);
}

template <class T>
typename AvlTree<T>::Node* AvlTree<T>::remove(Node* ptr, T key) {
    if (ptr == nullptr) {
        return nullptr;
    }
    if (comp(key, ptr->key)) {
        ptr->left = remove(ptr->left, key);
    } else if (key == ptr->key) {
        Node* l = ptr->left;
        Node* r = ptr->right;
        delete ptr;
        // Если нету правого поддерева, возвращаем левое
        if (r == nullptr) {
            return l;
        }
        std::pair<Node*, Node*> min_pair = minFindRemove(r);
        Node* min = min_pair.second;
        min->right = min_pair.first;
        min->left = l;
        return balance(min);
    } else {
        ptr->right = remove(ptr->right, key);
    }
    return balance(ptr);
}

template <class T>
int AvlTree<T>::GetStatistic(int s) const {
    int res = -1;
    if (s < getSize(root)) {
        Node* current = root;
        int i = getSize(root->left);
        while (i != s) {
            if (s > i) {
                current = current->right;
                i += 1 + getSize(current->left);
            } else {
                current= current->left;
                i -= 1 + getSize(current->right);
            }
        }
        res = current->key;
    } else if (s == getSize(root)) {
        return root->key;
    }
    return res;
}

int main() {

    int num;
    std::cin >> num;
    AvlTree<int> tree(compare);

    for (size_t i = 0; i < num; ++i) {
        int key;
        int s;

        std::cin >> key >> s;

        if (key < 0) {
            tree.Remove(abs(key));
        } else {
            tree.Insert(key);
        }

        std::cout << tree.GetStatistic(s) << std::endl;
    }
    return 0;
}