#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& a : A) std::cin >> a;

    int B, C;
    std::cin >> B >> C;

    long long count = N;
    for (int i = 0; i < N; ++i)
        if (A[i] > B) {
            count += (A[i] - B) / C;
            count += (A[i] - B) % C == 0 ? 0 : 1;
        }

    std::cout << count << '\n';

    return 0;
}