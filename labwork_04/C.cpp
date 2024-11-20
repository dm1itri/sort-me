#include <cstdio>
struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int value = 0;
  int size = 0;
};

Node *GetMinimumNode(Node *root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node *Insert(Node *root, int value) {
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        return root;
    }
    if (value > root->value) {
        root->right = Insert(root->right, value);
        root->size++;
    } else if (value < root->value) {
        root->left = Insert(root->left, value);
    }
    return root;
}

Node *Delete(Node *root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->value) {
        root->left = Delete(root->left, key);
    } else if (key > root->value) {
        root->size--;
        root->right = Delete(root->right, key);
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
        root->size--;
        root->right = Delete(root->right, node->value);
    }
    return root;
}

void PrintKMaximum(Node *node, int k) {
    while (node != nullptr) {
        if (k < node->size + 1) {
            node = node->right;
        } else if (k > node->size + 1) {
            k -= node->size + 1;
            node = node->left;
        } else {
            printf("%d\n", node->value);
            return;
        }
    }
}

int main() {
    int symbol;
    int value;
    int n;
    Node *head = nullptr;
    scanf("%d", &n);
    for (size_t i = 0; i < n; i++) {
        scanf("%d %d", &symbol, &value);
        if (symbol == 1) head = Insert(head, value);
        else if (symbol == -1) head = Delete(head, value);
        else PrintKMaximum(head, value);
    }
}