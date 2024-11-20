#include <iostream>

int pre_order[10000000];
int in_order[10000000];
int post_order[10000000];
bool correct = true;
struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int value = 0;
};

Node *Insert(int &index, int n, int left, int right) {
    if (index == n || pre_order[index] < left || pre_order[index] > right) return nullptr;
    Node *node = new Node{nullptr, nullptr, pre_order[index]};
    index++;
    node->left = Insert(index, n, left, pre_order[index - 1] - 1);
    node->right = Insert(index, n, pre_order[index - 1], right);
    return node;
}

void SomeOrder(Node *node, int &index_in, int &index_post) {
    if (node != nullptr) {
        SomeOrder(node->left, index_in, index_post);
        if (in_order[index_in] != node->value) correct = false;
        index_in++;
        SomeOrder(node->right, index_in, index_post);
        if (post_order[index_post] != node->value) correct = false;
        index_post++;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    for (size_t i = 0; i < n; i++) std::cin >> pre_order[i];
    for (size_t i = 0; i < n; i++) std::cin >> in_order[i];
    for (size_t i = 0; i < n; i++) std::cin >> post_order[i];
    int index = 0;
    Node *head = Insert(index, n, 0, in_order[n - 1]);
    int index_in = 0;
    int index_post = 0;
    SomeOrder(head, index_in, index_post);
    std::cout << (correct ? "YES" : "NO");
}