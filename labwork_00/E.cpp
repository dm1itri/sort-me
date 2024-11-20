#include <iostream>
using namespace std;
int main() {
    int n, min_0, min_1;
    cin >> n;
    int sp[n];
    for (int &i: sp) cin >> i;
    min_0 = sp[0];
    min_1 = sp[1];
    for (int &i: sp) {
        if (i < min_0) {
            min_1 = min_0;
            min_0 = i;
        } else if (i < min_1) {
            min_1 = i;
        }
    }
    cout << min_0 << " " << min_1;
    return 0;
}