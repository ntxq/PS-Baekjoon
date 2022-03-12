#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> wires(n);
    for (int i = 0; i < n; ++i) std::cin >> wires[i].first >> wires[i].second;

    std::sort(wires.begin(), wires.end());

    std::vector<int> p;
    std::vector<int> m;
    for (int i = 0; i < n; ++i) {
        auto it = std::lower_bound(m.begin(), m.end(), wires[i].second);

        p.push_back(it - m.begin());

        if (it == m.end())
            m.push_back(wires[i].second);
        else
            *it = wires[i].second;
    }

    std::cout << n - m.size() << '\n';

    int ansSize = m.size() - 1;
    m.clear();

    std::vector<int> badWires;
    while (!p.empty()) {
        if (p.back() == ansSize)
            --ansSize;
        else
            badWires.push_back(wires[p.size() - 1].first);

        p.pop_back();
    }

    while (!badWires.empty()) {
        std::cout << badWires.back() << '\n';
        badWires.pop_back();
    }

    return 0;
}
