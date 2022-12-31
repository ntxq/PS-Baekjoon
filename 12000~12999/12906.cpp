#include <compare>
#include <iostream>
#include <queue>
#include <set>
#include <string>

struct State {
    std::string poleA, poleB, poleC;
    std::strong_ordering operator<=>(const State& that) const = default;
};

bool isGoal(const State& state) {
    auto isAllSame = [](const std::string& pole, char target) {
        return std::all_of(pole.begin(), pole.end(),
                           [target](char c) { return c == target; });
    };

    return isAllSame(state.poleA, 'A') && isAllSame(state.poleB, 'B') &&
           isAllSame(state.poleC, 'C');
}
    
int bfs(const State& init) {
    std::queue<State> q;
    std::set<State> visited;

    q.push(init);
    visited.insert(init);

    int curDist = 0;
    int curSize = 1;

    while (!q.empty()) {
        int nextSize = 0;
        while (curSize--) {
            auto curState = q.front();
            auto [poleA, poleB, poleC] = curState;
            q.pop();

            if (isGoal(curState)) return curDist;

            if (!poleA.empty()) {
                State toB{
                    poleA.substr(0, poleA.size() - 1),
                    poleB + poleA.back(),
                    poleC,
                };
                if (!visited.contains(toB)) {
                    q.push(toB);
                    visited.insert(toB);
                    ++nextSize;
                }

                State toC{
                    poleA.substr(0, poleA.size() - 1),
                    poleB,
                    poleC + poleA.back(),
                };
                if (!visited.contains(toC)) {
                    q.push(toC);
                    visited.insert(toC);
                    ++nextSize;
                }
            }

            if (!poleB.empty()) {
                State toA{
                    poleA + poleB.back(),
                    poleB.substr(0, poleB.size() - 1),
                    poleC,
                };
                if (!visited.contains(toA)) {
                    q.push(toA);
                    visited.insert(toA);
                    ++nextSize;
                }

                State toC{
                    poleA,
                    poleB.substr(0, poleB.size() - 1),
                    poleC + poleB.back(),
                };
                if (!visited.contains(toC)) {
                    q.push(toC);
                    visited.insert(toC);
                    ++nextSize;
                }
            }

            if (!poleC.empty()) {
                State toA{
                    poleA + poleC.back(),
                    poleB,
                    poleC.substr(0, poleC.size() - 1),
                };
                if (!visited.contains(toA)) {
                    q.push(toA);
                    visited.insert(toA);
                    ++nextSize;
                }

                State toB{
                    poleA,
                    poleB + poleC.back(),
                    poleC.substr(0, poleC.size() - 1),
                };
                if (!visited.contains(toB)) {
                    q.push(toB);
                    visited.insert(toB);
                    ++nextSize;
                }
            }
        }

        ++curDist;
        curSize = nextSize;
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int _;
    State init;
    if (std::cin >> _ && _) std::cin >> init.poleA;
    if (std::cin >> _ && _) std::cin >> init.poleB;
    if (std::cin >> _ && _) std::cin >> init.poleC;

    std::cout << bfs(init) << '\n';

    return 0;
}
