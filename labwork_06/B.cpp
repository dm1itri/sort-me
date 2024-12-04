#include <iostream>
#include <vector>

void SiftUp(int index, std::vector<int> &queue) {
    while (index > 0 && queue[index] < queue[(index - 1) / 2]) {
        std::swap(queue[index], queue[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void SiftDown(int index, std::vector<int> &queue) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int smallest = index;
    if (left_child < queue.size() && queue[left_child] < queue[smallest])
        smallest = left_child;
    if (right_child < queue.size() && queue[right_child] < queue[smallest])
        smallest = right_child;
    if (smallest != index) {
        std::swap(queue[index], queue[smallest]);
        SiftDown(smallest, queue);
    }
}

void Insert(int x, std::vector<int> &queue) {
    queue.push_back(x);
    SiftUp(queue.size() - 1, queue);
}

void Delete(std::vector<int> &queue) {
    if (queue.empty()) {
        std::cout << '*' << '\n';
        return;
    }
    std::swap(queue[0], queue[queue.size() - 1]);
    std::cout << queue[queue.size() - 1] << '\n';
    queue.pop_back();
    SiftUp(0, queue);
    SiftDown(0, queue);
}

void Merge(std::vector<std::vector<int>> &arr, std::vector<int> &queue1, std::vector<int> &queue2) {
    std::vector<int> new_queue;
    for (int i : queue1) Insert(i, new_queue);
    for (int i : queue2) Insert(i, new_queue);
    arr.push_back(new_queue);
}

void DecreaseKey(std::vector<int> &queue, int x, int y) {
    for (int i = 0; i < queue.size(); i++) {
        if (x == queue[i]) {
            queue[i] = y;
            SiftUp(i, queue);
            break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::vector<std::vector<int>> arr;
    char cmd[13];
    while (std::cin >> cmd) {
        if (strncmp(cmd, "create", 6) == 0) {
            arr.emplace_back();
        } else if (strncmp(cmd, "insert", 6) == 0) {
            int k, x;
            std::cin >> k >> x;
            Insert(x, arr[k]);
        } else if (strncmp(cmd, "extract-min", 11) == 0) {
            int k;
            std::cin >> k;
            Delete(arr[k]);
        } else if (strncmp(cmd, "merge", 5) == 0) {
            int k, m;
            std::cin >> k >> m;
            Merge(arr, arr[k], arr[m]);
        } else if (strncmp(cmd, "decrease-key", 12) == 0) {
            int k, x, y;
            std::cin >> k >> x >> y;
            DecreaseKey(arr[k], x, y);
        }
    }
}