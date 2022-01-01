#include <iostream>
#include <string>

int main() {
    std::string a;
    std::string b;
    std::cin >> a >> b;

    char tmp = a[2];
    a[2] = a[0];
    a[0] = tmp;

    tmp = b[2];
    b[2] = b[0];
    b[0] = tmp;

    std::cout << (a > b ? a : b);

    return 0;
}