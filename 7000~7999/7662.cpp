#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int cases;
    std::cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int size;
        std::cin >> size;

        std::priority_queue<std::pair<int, int>> max_heap;
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
            min_heap;

        std::vector<bool> valid(size, false);

        for (int j = 0; j < size; ++j) {
            char op;
            int value;

            std::cin >> op >> value;
            if (op == 'I') {
                max_heap.push({value, j});
                min_heap.push({value, j});
                valid[j] = true;
            } else {
                if (value == 1) {
                    if (!max_heap.empty()) {
                        valid[max_heap.top().second] = 0;
                        max_heap.pop();
                    }
                } else {
                    if (!min_heap.empty()) {
                        valid[min_heap.top().second] = false;
                        min_heap.pop();
                    }
                }
            }
            while (!max_heap.empty() && !valid[max_heap.top().second])
                max_heap.pop();
            while (!min_heap.empty() && !valid[min_heap.top().second])
                min_heap.pop();
        }
        if (max_heap.empty())
            std::cout << "EMPTY\n";
        else
            std::cout << max_heap.top().first << ' ' << min_heap.top().first
                      << '\n';
    }

    return 0;
}