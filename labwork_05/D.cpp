#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  char value[100];
  int height = 1;
};

int memory = 0;
int countUnique[75] = {0};

int GetHeight(Node *node) {
    return node ? node->height : 0;
}

int GetMaxHeight(Node *node) {
    return std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

int GetBalance(Node *node) {
    return node ? GetHeight(node->right) - GetHeight(node->left) : 0;
}

Node *LeftRotate(Node *node) {
    Node *node_copy = node->right;
    node->right = node_copy->left;
    node_copy->left = node;
    node->height = GetMaxHeight(node);
    node_copy->height = GetMaxHeight(node_copy);
    return node_copy;
}

Node *RightRotate(Node *node) {
    Node *node_copy = node->left;
    node->left = node_copy->right;
    node_copy->right = node;
    node->height = GetMaxHeight(node);
    node_copy->height = GetMaxHeight(node_copy);
    return node_copy;
}

Node *Balance(Node *root) {
    int balance = GetBalance(root);
    if (balance == -2) {
        if (GetBalance(root->left) == 1) {
            root->left = LeftRotate(root->left);
        }
        return RightRotate(root);
    } else if (balance == 2) {
        if (GetBalance(root->right) == -1) {
            root->right = RightRotate(root->right);
        }
        return LeftRotate(root);
    }
    return root;
}

Node *Insert(Node *root, const char *value) {
    if (root == nullptr) {
        Node *node = new Node;
        strcpy(node->value, value);
        return node;
    }
    if (strcmp(value, root->value) < 0) {
        root->left = Insert(root->left, value);
    } else if (strcmp(value, root->value) > 0) {
        root->right = Insert(root->right, value);
    } else {
        int index = 0;
        while (value[index] != '\0') {
            countUnique[value[index] - '0'] = 1;
            index++;
        }
        for (int &i : countUnique) {
            memory += i;
            i = 0;
        }
        return root;
    }
    root->height = GetMaxHeight(root);
    return Balance(root);
}

int main() {
    int n;
    std::cin >> n;
    char symbols[100];
    Node *head = nullptr;
    for (size_t i = 0; i < n; i++) {
        std::cin >> symbols;
        head = Insert(head, symbols);
    }
    std::cout << memory;
}


