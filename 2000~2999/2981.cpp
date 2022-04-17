#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    for (unsigned i = 0; i < A.size() - 1; ++i)
        A[i] = std::abs(A[i + 1] - A[i]);
    A.pop_back();

    int factor = (A.size() > 1 ? gcd(A[0], A[1]) : A[0]);
    for (unsigned i = 2; i < A.size(); ++i) factor = gcd(factor, A[i]);

    std::vector<int> answers;
    for (int i = 2; i <= std::sqrt(factor); ++i)
        if (factor % i == 0) {
            answers.push_back(i);
            if (i * i != factor) answers.push_back(factor / i);
        }
    answers.push_back(factor);

    std::sort(answers.begin(), answers.end());
    for (int& i : answers) std::cout << i << ' ';

    return 0;
}
