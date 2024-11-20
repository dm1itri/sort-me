#include <cstdint>
#include <cstdio>
uint32_t arr[26] = {0};
char c[10000001];

struct Multiplier {
  Multiplier *prev = nullptr;
  uint32_t mult = 1;
};

void ReadString() {

    uint32_t last_index = 0;
    scanf("%c", &c[last_index]);
    while (c[last_index] != '\0') {
        scanf("%c", &c[++last_index]);
    }
    last_index--;
    uint32_t count = 0;
    uint32_t count_multiplier = 1;
    Multiplier *m_last = new Multiplier{};
    for (int32_t i = last_index; i >= 0; i--) {
        while (0 <= c[i] - '0' && c[i] - '0' <= 9) {
            count += (c[i] - '0') * count_multiplier;
            count_multiplier *= 10;
            i--;
        }
        if (0 <= c[i] - 'A' && c[i] - 'A' < 26) {
            arr[c[i] - 'A'] += (count + (count == 0)) * m_last->mult;
        } else if (c[i] == ')') {
            Multiplier *mult = new Multiplier;
            mult->mult = m_last->mult * count;
            mult->prev = m_last;
            m_last = mult;
        } else {
            Multiplier *m_last_prev = m_last->prev;
            delete m_last;
            m_last = m_last_prev;
        }
        count = 0;
        count_multiplier = 1;
    }

}

int main() {
    ReadString();
    for (uint8_t i = 0; i < 26; i++) {
        if (arr[i] > 1) printf("%c%i", i + 'A', arr[i]);
        else if (arr[i] == 1) printf("%c", i + 'A');
    }
}