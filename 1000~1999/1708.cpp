#include <algorithm>
#include <iostream>
#include <vector>

long long dist(const std::pair<long long, long long>& p,
               const std::pair<long long, long long>& q) {
    return (p.first - q.first) * (p.first - q.first) +
           (p.second - q.second) * (p.second - q.second);
}

long long direction(const std::pair<long long, long long>& i,
                    const std::pair<long long, long long>& j,
                    const std::pair<long long, long long>& k) {
    return (k.first - i.first) * (j.second - i.second) -
           (k.second - i.second) * (j.first - i.first);
}

bool isCounterClockwise(const std::pair<long long, long long>& p,
                        const std::pair<long long, long long>& q,
                        const std::pair<long long, long long>& r) {
    long long dir = direction(p, q, r);
    if (!dir) return dist(p, q) < dist(p, r);

    return dir > 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<long long, long long>> q(n);
    for (auto& [x, y] : q) std::cin >> x >> y;

    int p0 = 0;
    for (int i = 1; i < n; ++i)
        if (q[i].second < q[p0].second ||
            (q[i].first < q[p0].first && q[i].second == q[p0].second))
            p0 = i;
    std::swap(q[p0], q[0]);

    std::sort(q.begin() + 1, q.end(), [&](const auto& a, const auto& b) {
        return isCounterClockwise(q[0], a, b);
    });

    std::vector<std::pair<long long, long long>> s;
    s.push_back(q[0]);
    s.push_back(q[1]);

    for (int i = 2; i < n; ++i) {
        while (s.size() > 1 &&
               direction(s[s.size() - 2], s[s.size() - 1], q[i]) <= 0)
            s.pop_back();
        s.push_back(q[i]);
    }

    std::cout << s.size() << '\n';

    return 0;
}
