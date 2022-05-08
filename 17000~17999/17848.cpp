#include <algorithm>
#include <iostream>
#include <string>

void recurse(int depth, int limit) {
    static const std::string pre[] = {
        "\"재귀함수가 뭔가요?\"",
        "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 "
        "선인이 있었어.",
        "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 "
        "대답해 주었지.",
        "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 "
        "찾아와서 물었어.\""};

    static const std::string suf = "라고 답변하였지.";

    if (depth == limit) {
        for (int j = 0; j < depth; ++j) std::cout << "____";
        std::cout << pre[0] << '\n';
        for (int j = 0; j < depth; ++j) std::cout << "____";
        std::cout << "\"재귀함수는 자기 자신을 호출하는 함수라네\"\n";
        for (int j = 0; j < depth; ++j) std::cout << "____";
        std::cout << suf << '\n';
        return;
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < depth; ++j) std::cout << "____";
        std::cout << pre[i] << '\n';
    }

    recurse(depth + 1, limit);

    for (int j = 0; j < depth; ++j) std::cout << "____";
    std::cout << suf << '\n';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n";
    recurse(0, N);

    return 0;
}