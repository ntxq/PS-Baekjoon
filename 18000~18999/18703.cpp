#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::unordered_map<std::string, int> files;

        for (int i = 0; i < N; ++i) {
            std::string file_name;
            int file_id;

            std::cin >> file_name >> file_id;

            if (files.contains(file_name))
                files[file_name] = std::min(files[file_name], file_id);
            else
                files[file_name] = file_id;
        }

        std::vector<int> file_ids;
        for (const auto& [_, file_id] : files) file_ids.push_back(file_id);

        std::sort(file_ids.begin(), file_ids.end());
        for (const auto& file_id : file_ids) std::cout << file_id << '\n';
    }

    return 0;
}
