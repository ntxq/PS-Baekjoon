#include <cctype>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::map<std::string, int> pokemonMap;
    std::map<int, std::string> pokemonMapReverse;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        pokemonMap[name] = i;
        pokemonMapReverse[i] = name;
    }

    for (int i = 0; i < m; ++i) {
        std::string q;
        std::cin >> q;
        if (std::isdigit(q[0])) {
            int pos = std::stoi(q);
            std::cout << pokemonMapReverse[pos - 1] << '\n';
        } else {
            std::cout << pokemonMap[q] + 1 << '\n';
        }
    }

    return 0;
}