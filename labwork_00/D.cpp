#include <iostream>
using namespace std;
int main() {
    int n, x, my_x, delta_x=10000;
    cin >> n;
    int sp[n];
    for (int &i: sp) cin >> i;
    cin >> x;
    for (int &i: sp) {
        if (i > x && i - x < delta_x) {
            delta_x = i - x;
            my_x = i;
        } else if (i <= x && x - i < delta_x) {
            delta_x = x - i;
            my_x = i;
        }
    }
    cout << my_x;
    return 0;
}