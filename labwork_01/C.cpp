#include <iostream>
using namespace std;
int main() {
    int n, correct_0 = 0, correct_1 = 0;
    cin >> n;
    char string[n];
    for (char &i : string) cin >> i;
    for (int i = 0, delta = 0; i < n / 2 + n % 2; i++) { // убираем с левой стороны символ
        if (string[i] != string[n - i - 1 + delta]) {
            correct_0++;
            delta++;
        }
    }
    for (int i = 0, delta = 0; i < n / 2 + n % 2; i++) {   // либо убираем с правой стороны символ
        if (string[i - delta] != string[n - i - 1]) {
            correct_1++;
            delta++;
        }
    }
    if (correct_0 < 2 || correct_1 < 2) printf("YES");
    else printf("NO");
    return 0;
}
