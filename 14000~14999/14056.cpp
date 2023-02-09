#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <string>
#include <vector>

std::string findKthGoodString(const std::string& s, int k) {
    std::vector<std::set<std::string>> goodStrings(75);

    if (s.length() >= 2) goodStrings[0] = {"()"};

    for (int i = 1; i < 75; ++i) {
        for (const auto& base : goodStrings[i - 1]) {
            std::string derived = base;
            while (derived.length() <= s.length() - 2) {
                goodStrings[i].insert("(" + derived + ")");
                derived += base;
            }
        }
    }

    for (auto i = goodStrings.rbegin(); i != goodStrings.rend(); ++i)
        for (const auto& goodString : *i) {
            auto sit = goodString.begin();
            auto git = s.begin();

            while (sit != goodString.end() && git != s.end())
                if (*sit == *git)
                    ++sit, ++git;
                else
                    ++git;

            if (sit == goodString.end()) --k;

            if (k == 0) return goodString;
        }

    return "-1";
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::set<std::string>> goodStrings(75);

    std::string s;
    int k;
    std::cin >> s >> k;

    std::cout << findKthGoodString(s, k) << '\n';

    return 0;
}
