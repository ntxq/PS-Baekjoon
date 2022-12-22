#include <iostream>
#include <list>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::list editor(s.begin(), s.end());
    auto cursor = editor.end();

    int M;
    std::cin >> M;

    while (M--) {
        char c;
        std::cin >> c;

        switch (c) {
            case 'L':
                if (cursor != editor.begin()) --cursor;
                break;

            case 'D':
                if (cursor != editor.end()) ++cursor;
                break;

            case 'B':
                if (cursor != editor.begin()) cursor = editor.erase(--cursor);
                break;

            case 'P':
                char ch;
                std::cin >> ch;
                editor.insert(cursor, ch);
                break;
        }
    }

    for (const auto& ch : editor) std::cout << ch;
    std::cout << '\n';

    return 0;
}