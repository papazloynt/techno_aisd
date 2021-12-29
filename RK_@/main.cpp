#include <iostream>
#include <algorithm>
#include <queue>

class TNode {
public:
    TNode(int key_) : key(key_) {}

    int key;
    TNode* left = nullptr;
    TNode* right = nullptr;
};

class TTree {
public:
    TTree() : root(nullptr) {}

    ~TTree() {
        DestroyNodeReqursive(root);
    }

    void Insert(int data) {
        root = InsertNode(root, data);
    }

    int MinDep() {
        return MinDepth(root);
    }
private:
    static void DestroyNodeReqursive(TNode* node) {
        if (node) {
            DestroyNodeReqursive(node->left);
            DestroyNodeReqursive(node->right);
            delete node;
        }
    }

    TNode* InsertNode(TNode* root, int data) {
        if (root == nullptr) {
            root = new TNode(data);
            return root;
        }

        std::queue<TNode*> q;
        q.push(root);

        while (!q.empty()) {
            TNode* temp = q.front();
            q.pop();

            if (temp->left != nullptr)
                q.push(temp->left);
            else {
                temp->left = new TNode(data);
                return root;
            }
            if (temp->right != NULL)
                q.push(temp->right);
            else {
                temp->right = new TNode(data);
                return root;
            }
        }
    }

    int MinDepth(TNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int lDepth = MinDepth(node->left);
            int rDepth = MinDepth(node->right);
            // use the larger one
            if (lDepth > rDepth) return(rDepth+1);
            else return(lDepth+1);
        }
    }

private:
    TNode* root;
};

int main() {
    TTree tree;
    int num;
    while (std::cin >> num) {
        tree.Insert(num);
    }

    std::cout << tree.MinDep() << std::endl;
    return 0;
}