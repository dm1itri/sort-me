#include <iostream>
using namespace std;

int gsd(int a, int b) {
    while (a > 0 && b > 0) {
        if (a >= b) a %= b;
        else b %= a;
    }
    if (a >= b) return a;
    else return b;
}

int main() {
    int n, k, count_steps;
    cin >> n >> k;
    k %= n;
    if (k < 0) k += n;
    count_steps = n / gsd(n, k);  // сколько перестановок до попадания в бывшую точку
    int sp[n];
    for (int &i : sp) cin >> i;
    int old_x = sp[0];
    for (int i = 1, index = k; i <= n; i++) {
        int x = sp[index % n];
        sp[index % n] = old_x;
        if (count_steps > 1 && i % count_steps == 0) {
            index++;
            index %= n;
            x = sp[index];
        } else if (index >= n) index %= n;
        old_x = x;
        index += k;
    }
    for (int &i : sp) cout << i << " ";
}