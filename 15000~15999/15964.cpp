#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long A, B;
    std::cin >> A >> B;
    
    std::cout << (A + B) * (A - B) << '\n';
    
    return 0;
}
