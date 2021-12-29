/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root;
иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

2_1. Выведите элементы в порядке in-order (слева направо).
*/
#include <iostream>
#include <stack>
#include <queue>

template <class T>
bool compare(const T& l, const T& r){
    return l > r;
}

template <class T>
class BinTree{
public:
    explicit BinTree(bool _func(const T&, const T&));
    ~BinTree();

    void Add(T key);
    void InOrderDFS(void visit (T));

    int getMaxDepth();

private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        Node(T _key) : key( _key ), left( nullptr ), right( nullptr ) {}
    };

    bool (*func)(const T&, const T&);
    Node* root;
    void PostOrder( void visit (Node* node) );
};

template <class T>
BinTree<T>::BinTree(bool _func (const T&, const T&)) : func(_func), root(nullptr) {}

template <class T>
BinTree<T>::~BinTree() {
    PostOrder([] (Node* node) {delete node;});
}

template <class T>
void BinTree<T>::Add(T key) {
    // Инциализация корня, если его нет
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    // Ищем элемент куда можно всавить key
    Node* node = root;
    Node* nodeParent;
    while (node != nullptr) {
        nodeParent = node;
        node = (func(nodeParent->key, key) ? nodeParent->left : nodeParent->right);
    }
    // Вставка
    if (func(nodeParent->key, key)) {
        nodeParent->left = new Node(key);
    } else {
        nodeParent->right = new Node(key);
    }
}

template <class T>
void BinTree<T>::InOrderDFS(void visit(T)) {
    // Если нету элементов - выход, ничего не печатаем
    if (root == nullptr) return;
    // Составляем стек элементов и печатем их в заданном порядке
    std::stack<Node*> st;
    Node* current = root;
    while ( !st.empty() || current != nullptr ) {
        if (current != nullptr) {
            st.push(current);
            current = current->left;
        } else {
            current = st.top();
            st.pop();
            visit(current->key);
            current = current->right;
        }
    }
}

template <class T>
int BinTree<T>::getMaxDepth(){
    if (root == nullptr) return 0;

    std::queue<Node*> layerNodes;
    layerNodes.push(root);
    int j = 0;
    while (!layerNodes.empty()) {
        int num = layerNodes.size();
        for (size_t i = 0; i < num; ++i) {
            Node* cur = layerNodes.front();
            if (cur->left != nullptr) {
                layerNodes.push(cur->left);
            }
            if (cur->right != nullptr) {
                layerNodes.push(cur->right);
            }
            layerNodes.pop();
        }
        ++j;
    }
    return j;
}

template <class T>
void BinTree<T>::PostOrder( void visit (Node* node) ){
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
            if(current->right != nullptr && lastNodeVisited != current->right){
                current = current->right;
            } else {
                st.pop();
                lastNodeVisited = current;
                visit(current);
                current = nullptr;
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    BinTree<int> tree(compare);
    for (size_t i = 0; i < n; ++i) {
        int key;
        std::cin >> key;
        tree.Add( key );
    }
    tree.InOrderDFS([] (int key) {std::cout << key << " ";});
    return 0;
}
