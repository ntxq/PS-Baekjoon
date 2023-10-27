#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (T--) {
        std::string line;
        std::getline(std::cin, line);

        std::vector<int> leap_years;

        size_t i = 0;
        while (i < line.size()) {
            size_t j = i;
            while (j < line.size() && line[j] != ',') ++j;

            int year = std::stoi(line.substr(i, j - i));
            if (year % 4 == 0) leap_years.push_back(year);

            i = j + 1;
        }

        for (int year : leap_years) std::cout << year << ' ';
        std::cout << '\n';
    }

    return 0;
}
