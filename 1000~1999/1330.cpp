#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    const char* c = (a < b ? "<" : (a > b ? ">" : "=="));
    std::cout << c;

    return 0;
}