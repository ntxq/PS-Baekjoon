#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int a, b;
    while (cin >> a >> b, a || b) cout << (a > b ? "Yes\n" : "No\n");

    return 0;
}