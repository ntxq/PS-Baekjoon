#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::string site, password;
    std::unordered_map<std::string, std::string> map;
    for (int i = 0; i < n; ++i) {
        std::cin >> site >> password;

        map[site] = password;
    }

    for (int i = 0; i < m; ++i) {
        std::cin >> site;

        std::cout << map[site] << '\n';
    }

    return 0;
}