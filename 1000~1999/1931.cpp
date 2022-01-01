#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<std::pair<int, int>> meetings(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> meetings[i].second >> meetings[i].first;
    }

    std::sort(meetings.begin(), meetings.end());

    int count = 0;
    for (int i = 0, curEnd = 0; i < size; ++i) {
        if (meetings[i].second >= curEnd) {
            ++count;
            curEnd = meetings[i].first;
        }
    }

    std::cout << count;

    return 0;
}