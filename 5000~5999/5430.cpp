#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::string p;
        int n;
        std::cin >> p >> n;

        std::deque<int> seq(n);
        if (char tmp; std::cin >> tmp && n)
            for (auto& i : seq) std::cin >> i >> tmp;
        else
            std::cin >> tmp;

        bool isReversed = false;
        bool isError = false;
        for (unsigned i = 0; i < p.size() && !isError; ++i)
            if (p[i] == 'R')
                isReversed = !isReversed;
            else if (!seq.size())
                isError = true;
            else if (isReversed)
                seq.pop_back();
            else
                seq.pop_front();

        if (isError) {
            std::cout << "error\n";
        } else {
            std::cout << '[';
            if (isReversed)
                for (unsigned i = seq.size() - 1; i < seq.size(); --i)
                    if (i)
                        std::cout << seq[i] << ',';
                    else
                        std::cout << seq[i];
            else
                for (unsigned i = 0; i < seq.size(); ++i)
                    if (i + 1 < seq.size())
                        std::cout << seq[i] << ',';
                    else
                        std::cout << seq[i];
            std::cout << "]\n";
        }
    }

    return 0;
}