#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

std::deque<int> get_sequence(std::vector<std::vector<int>> numbers, int N) {
    if (numbers[0].size() > (N + 1) / 2) return {-1};
    if (numbers[0].empty() && !numbers[1].empty() && !numbers[2].empty())
        return {-1};

    std::deque<int> output;
    if (!numbers[0].empty()) {
        output.push_back(numbers[0].back());
        numbers[0].pop_back();
    }

    while (!numbers[1].empty()) {
        output.push_front(numbers[1].back());
        numbers[1].pop_back();
        if (!numbers[0].empty()) {
            output.push_front(numbers[0].back());
            numbers[0].pop_back();
        }
    }

    while (!numbers[2].empty()) {
        output.push_back(numbers[2].back());
        numbers[2].pop_back();
        if (!numbers[0].empty()) {
            output.push_back(numbers[0].back());
            numbers[0].pop_back();
        }
    }

    return output;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> numbers(3);
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;

        numbers[x % 3].push_back(x);
    }

    for (int i : get_sequence(numbers, N)) std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}