#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int max_num = 0;
    std::vector<bool> numbers(1000001);

    for (int i = 0; i < N; ++i) {
        int number;
        std::cin >> number;

        max_num = std::max(max_num, number);
        numbers[number] = true;
    }

    int count = 0;
    for (int i = 1; i <= max_num; ++i)
        for (int j = 1; i * j <= max_num && j <= i; ++j)
            if (numbers[i * j] && (i - j) % 2 == 0 && numbers[(i - j) / 2])
                ++count;

    std::cout << count << '\n';

    return 0;
}
