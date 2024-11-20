#include <iostream>
using namespace std;
int main() {
    int n, count = 0;
    cin >> n;
    int sp[n];
    for (int &i: sp) cin >> i;
    for (int i=1; i < n - 1; i++) {
        if (sp[i-1] < sp[i] && sp[i] > sp[i+1]) count ++;
    }
    cout << count;
    return 0;
}