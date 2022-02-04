#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, s;
    std::cin >> n >> s;

    std::vector<int> seq(n);
    for (int& i : seq) std::cin >> i;

    int sum = seq[0];
    int minLength = sum >= s;
    for (int i = 0, j = 0; j < n;) {
        if (sum < s)
            sum += seq[++j];
        else {
            if (j - i + 1 < minLength || !minLength) 
                minLength = j - i + 1;
            sum -= seq[i++];
        }
    }

    std::cout << minLength;

    return 0;
}