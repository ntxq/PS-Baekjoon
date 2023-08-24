#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    std::string ip;
    std::cin >> ip;

    auto double_pos =
        std::adjacent_find(ip.begin(), ip.end(),
                           [](char a, char b) { return a == ':' && b == ':'; });

    if (double_pos != ip.end()) {
        int to_insert = 8 - std::count_if(ip.begin(), ip.end(),
                                          [](char c) { return c == ':'; });
        int insert_pos = double_pos - ip.begin();

        ip.erase(double_pos);

        for (int i = 0; i < to_insert; ++i) ip.insert(insert_pos, ":0000");
    }

    std::vector<std::string> blocks = {"0000", "0000", "0000", "0000",
                                       "0000", "0000", "0000", "0000"};
    for (unsigned i = ip.size() - 1, j = 3, block = 7; i < ip.size();
         --i, --j) {
        if (ip[i] == ':') {
            --block;
            j = 4;
            continue;
        }

        blocks[block][j] = ip[i];
    }

    std::cout << blocks[0];
    for (int i = 1; i < 8; ++i) std::cout << ':' << blocks[i];
    std::cout << '\n';

    return 0;
}