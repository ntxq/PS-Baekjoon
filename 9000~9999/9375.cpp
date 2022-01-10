#include <iostream>
#include <map>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;

        std::map<std::string, int> m;
        for (int j = 0; j < n; ++j) {
            std::string name, type;
            std::cin >> name >> type;
            ++m[type];
        }

        int days = 0;
        for (const auto& clothes : m)
            if (!days)
                days = clothes.second + 1;
            else
                days *= clothes.second + 1;

        std::cout << (days ? days - 1 : 0) << '\n';
    }

    return 0;
}