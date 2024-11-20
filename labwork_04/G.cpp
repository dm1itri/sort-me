#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  long long value = 0;
};

Node *GetMinimumNode(Node *root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node *Insert(Node *root, long long value) {
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        return root;
    }
    if (value > root->value) {
        root->right = Insert(root->right, value);
    } else if (value < root->value) {
        root->left = Insert(root->left, value);
    }
    return root;
}

Node *Delete(Node *root, long long value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->value) {
        root->left = Delete(root->left, value);
    } else if (value > root->value) {
        root->right = Delete(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node *root_right = root->right;
            delete root;
            return root_right;
        } else if (root->right == nullptr) {
            Node *root_left = root->left;
            delete root;
            return root_left;
        }
        Node *node = GetMinimumNode(root->right);
        root->value = node->value;
        root->right = Delete(root->right, node->value);
    }
    return root;
}

void Merge(Node *&Nikola, Node *Stepan, Node *&HeadStepan) {
    if (Stepan != nullptr) {
        Merge(Nikola, Stepan->left, HeadStepan);
        Merge(Nikola, Stepan->right, HeadStepan);
        Nikola = Insert(Nikola, Stepan->value);
        HeadStepan = Delete(HeadStepan, Stepan->value);
    }
}

void PrintAscending(Node *node, long long &count) {
    if (node != nullptr) {
        PrintAscending(node->left, count);
        if (count == 0) {
            std::cout << node->value;
            count++;
        }
        else std::cout << ' ' << node->value;
        PrintAscending(node->right, count);
    }
}

int main() {
    long long n;
    std::cin >> n;
    long long a, ID, task;
    Node *headNikola = nullptr;
    Node *headStepan = nullptr;
    for (size_t i = 0; i < n; i++) {
        std::cin >> a;
        if (a == 0) {
            std::cin >> ID >> task;
            if (ID == 0) headNikola = Insert(headNikola, task);
            else headStepan = Insert(headStepan, task);
        } else if (a == 1) {
            std::cin >> ID >> task;
            if (ID == 0) headNikola = Delete(headNikola, task);
            else headStepan = Delete(headStepan, task);
        } else {
            long long count = 0;
            Merge(headNikola, headStepan, headStepan);
            PrintAscending(headNikola, count);
            if (count) std::cout << std::endl;
        }
    }
}

