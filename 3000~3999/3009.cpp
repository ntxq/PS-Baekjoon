#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> X;
    std::vector<int> Y;

    for (int i = 0; i < 3; ++i) {
        int x, y;
        std::cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
    }

    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());

    if (X[0] != X[1])
        std::cout << X[0] << ' ';
    else
        std::cout << X[2] << ' ';

    if (Y[0] != Y[1])
        std::cout << Y[0] << '\n';
    else
        std::cout << Y[2] << '\n';


    return 0;
}
