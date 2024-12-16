#include <iostream>
#include <vector>


struct Segment {
  double left = 0;
  double right = 0;
};

double ArithmeticCoding(std::string &letters, std::vector <double> &probability, std::string &s) {
    Segment segment[letters.length()];
    double l = 0;
    for (int i = 0; i < letters.length(); i++) {
        segment[i].left = l;
        segment[i].right = l + probability[i];
        l = segment[i].right;
    }
    l = 0;
    double r = 1;
    for (int i = 0; i < s.length(); i ++) {
        double new_right = l + (r - l) * segment[letters.find(s[i])].right;
        double new_left = l + (r - l) * segment[letters.find(s[i])].left;
        l = new_left;
        r = new_right;
     }
    return l;
}

int main() {
    std::string s;
    double length = 0;
    int counter[26];
    for (int &i : counter) i = 0;
    std::cin >> s;
    for (char &i: s) {
        counter[i - 'a'] += 1;
        length++;
    }

    std::vector <double> prob;
    std::string lets;
    for (int i = 0; i < 26; i++) {
        if (counter[i] > 0) {
            prob.push_back(counter[i] / length);
            lets.push_back(i + 'a');
        }
    }
    std::cout.precision(6);
    std::cout << std::fixed << ArithmeticCoding(lets, prob, s);
}