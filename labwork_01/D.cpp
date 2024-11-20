#include <iostream>
using namespace std;
int main() {
    int n, index = 0;
    cin >> n;
    long long sp[n + 2];
    sp[0] = 0;
    cin >> sp[1];
    for (int i = 2, x; i < n + 1; i++) {
        cin >> x;
        sp[i] = sp[i - 1] + x;
    }
    sp[n + 1] = sp[n];
    for (int i = 1; i < n + 2; i++) {
        if (sp[i - 1] == sp[n + 1] - sp[i]) {
            index = i;
            break;
        }
    }
    cout << index - 1;
}
