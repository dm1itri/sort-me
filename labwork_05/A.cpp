#include <iostream>
struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int value = 0;
  int delta = 0;
};

Node *arr[200000];
Node *arr_child[200001];

int GetMaxHeight(Node *node) {
    if (node == nullptr) return 0;
    int l_height = GetMaxHeight(node->left);
    int r_height = GetMaxHeight(node->right);
    node->delta = r_height - l_height;
    return std::max(l_height, r_height) + 1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    int K, L, R;
    std::cin >> n;
    std::cin >> K >> L >> R;
    Node *head = new Node{nullptr, nullptr, K};
    arr[0] = head;
    arr_child[L] = head;
    arr_child[R] = head;
    for (size_t i = 2; i <= n; i++) {
        std::cin >> K >> L >> R;
        if (K > arr_child[i]->value) {
            arr_child[i]->right = new Node{nullptr, nullptr, K};
            arr[i - 1] = arr_child[i]->right;
            arr_child[L] = arr_child[i]->right;
            arr_child[R] = arr_child[i]->right;
        } else {
            arr_child[i]->left = new Node{nullptr, nullptr, K};
            arr[i - 1] = arr_child[i]->left;
            arr_child[L] = arr_child[i]->left;
            arr_child[R] = arr_child[i]->left;
        }
    }
    GetMaxHeight(arr[0]);
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i]->delta << '\n';
    }
}