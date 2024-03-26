#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string ip;
    std::cin >> ip;

    std::vector<std::array<std::string, 4>> ip_blocks;
    for (int i = 1; i < ip.size(); ++i)
        for (int j = i + 1; j < ip.size(); ++j)
            for (int k = j + 1; k < ip.size(); ++k)
                ip_blocks.push_back({ip.substr(0, i), ip.substr(i, j - i),
                                     ip.substr(j, k - j), ip.substr(k)});

    int count = 0;
    for (int i = 0; i < ip_blocks.size(); ++i)
        if (std::all_of(ip_blocks[i].begin(), ip_blocks[i].end(),
                        [](const std::string& x) {
                            const auto n = std::stoi(x);
                            if (n == 0) return x.size() == 1;
                            return 0 <= n && n <= 255 && x[0] != '0';
                        }))
            ++count;

    std::cout << count << '\n';

    return 0;
}
