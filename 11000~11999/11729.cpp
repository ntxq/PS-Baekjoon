#include <algorithm>
#include <iostream>

void solveHanoi(char from, char to, char aux, int size) {
    if (!size) return;

    solveHanoi(from, aux, to, size - 1);
    std::cout << from << ' ' << to << '\n';
    solveHanoi(aux, to, from, size - 1);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::cout << (1U << N) - 1 << '\n';
    solveHanoi('1', '3', '2', N);

    return 0;
}
