#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::map<std::string, int> days;
    days["Mon"] = 0;
    days["Tue"] = 1;
    days["Wed"] = 2;
    days["Thu"] = 3;
    days["Fri"] = 4;

    int t, n;
    std::cin >> t >> n;

    for (int i = 0; i < n; ++i) {
        std::string from, to;
        int sleep, wake;

        std::cin >> from >> sleep >> to >> wake;

        t -= (days[to] - days[from] - 1) * 24 + (24 - sleep) + wake;
    }

    if (t < 0)
        std::cout << 0;
    else if (t > 48)
        std::cout << -1;
    else
        std::cout << t;
    std::cout << '\n';

    return 0;
}
