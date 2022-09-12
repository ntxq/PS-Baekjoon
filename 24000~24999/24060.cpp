#include <deque>
#include <iostream>
#include <vector>

std::vector<int> A;
int K;
int ans = -1;

void merge_sort(int, int);
void merge(int, int, int);

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N >> K;

    A.resize(N);
    for (auto& i : A) std::cin >> i;

    merge_sort(0, N - 1);
    std::cout << ans << '\n';

    return 0;
}

void merge_sort(int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(p, q);
        merge_sort(q + 1, r);
        merge(p, q, r);
    }
}

void merge(int p, int q, int r) {
    std::deque<int> left(A.begin() + p, A.begin() + q + 1);
    std::deque<int> right(A.begin() + q + 1, A.begin() + r + 1);

    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            A[p++] = left.front();
            left.pop_front();
        } else {
            A[p++] = right.front();
            right.pop_front();
        }
        --K;
        if (!K) ans = A[p - 1];
    }

    while (!left.empty()) {
        A[p++] = left.front();
        left.pop_front();
        --K;
        if (!K) ans = A[p - 1];
    }

    while (!right.empty()) {
        A[p++] = right.front();
        right.pop_front();
        --K;
        if (!K) ans = A[p - 1];
    }
}