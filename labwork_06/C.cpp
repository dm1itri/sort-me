#include <iostream>
struct Shawarmist{
  long long salary = 0;
  int end = 0;
};

long long total_salary = 0;

void SiftUp(int index, Shawarmist *arr) {
    while (index > 0 && arr[index].salary < arr[(index - 1) / 2].salary) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void SiftUpByTime(int index, Shawarmist *arr) {
    while (index > 0 && arr[index].end < arr[(index - 1) / 2].end) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void SiftDown(int index, int size, Shawarmist *arr) {
    int i, l, r;
    while (index < size) {
        i = index;
        l = index * 2 + 1;
        r = l + 1;
        if (l < size && arr[i].salary > arr[l].salary) {
            i = l;
        }
        if (r < size && arr[i].salary > arr[r].salary) {
            i = r;
        }
        if (i == index) break;
        std::swap(arr[index], arr[i]);
        index = i;
    }
}

void SiftDownByTime(int index, int size, Shawarmist *arr) {
    int i, l, r;
    while (index < size) {
        i = index;
        l = index * 2 + 1;
        r = l + 1;
        if (l < size && arr[i].end >= arr[l].end) {
            i = l;
        }
        if (r < size && arr[i].end >= arr[r].end) {
            i = r;
        }
        if (i == index) break;
        std::swap(arr[index], arr[i]);
        index = i;
    }
}

void Insert(Shawarmist element, int index, Shawarmist *arr) {
    arr[index] = element;
    SiftUp(index, arr);
}

void InsertByTime(Shawarmist element, int index, Shawarmist *arr) {
    arr[index] = element;
    SiftUpByTime(index, arr);
}

void PopInsert(int time, int &size, int &size_salary, Shawarmist *arr, Shawarmist *arr_salary) {
    while (size != 0 && time >= arr[0].end) {
        Insert(arr[0], size_salary++, arr_salary);
        std::swap(arr[0], arr[--size]);
        SiftDownByTime(0, size, arr);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Shawarmist min_heap_salary[n];
    int min_heap_salary_size = n;
    for (Shawarmist &i : min_heap_salary) std::cin >> i.salary;
    for (int i = n / 2; i >= 0; i--) {
        SiftUp(i, min_heap_salary);
        SiftDown(i, min_heap_salary_size, min_heap_salary);
    }

    Shawarmist min_heap_duration[n];
    int min_heap_duration_size = 0;
    int start, duration;
    for (int i = 0; i < m; i++) {
        std::cin >> start >> duration;
        PopInsert(start, min_heap_duration_size, min_heap_salary_size, min_heap_duration, min_heap_salary);
        if (min_heap_salary_size > 0) {
            total_salary += min_heap_salary[0].salary * duration;
            min_heap_salary[0].end = start + duration;
            InsertByTime(min_heap_salary[0], min_heap_duration_size++, min_heap_duration);
            std::swap(min_heap_salary[0], min_heap_salary[--min_heap_salary_size]);
            SiftDown(0, min_heap_salary_size, min_heap_salary);
        }
    }
    std::cout << total_salary;
}
