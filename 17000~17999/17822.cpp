#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class Disc {
   private:
    std::vector<std::optional<int>> numbers;
    int curTop = 0;

    std::optional<int>& operator[](std::size_t i) {
        return numbers[(curTop + i + numbers.size()) % numbers.size()];
    }

    bool shouldErase(std::size_t i) {
        return ((*this)[i] == (*this)[i - 1]) ||
               ((*this)[i] == (*this)[i + 1]) ||
               (prev && (*this)[i] == (*prev)[i]) ||
               (next && (*this)[i] == (*next)[i]);
    }

    void erase(std::size_t i) {
        int x = (*this)[i].value();
        (*this)[i].reset();

        if ((*this)[i - 1] == x) erase(i - 1);
        if ((*this)[i + 1] == x) erase(i + 1);
        if (prev && (*prev)[i] == x) prev->erase(i);
        if (next && (*next)[i] == x) next->erase(i);
    }

   public:
    Disc* prev = nullptr;
    Disc* next = nullptr;

    Disc(const std::vector<int>& numbers)
        : numbers(numbers.begin(), numbers.end()) {}

    void rotate(bool dir, int amount) {
        if (dir)
            curTop = (curTop + amount) % numbers.size();
        else
            curTop = (curTop - amount + numbers.size()) % numbers.size();
    }

    bool sanitize() {
        bool isErased = false;
        for (std::size_t i = 0; i < numbers.size(); ++i)
            if ((*this)[i] && shouldErase(i)) {
                erase(i);
                isErased = true;
            }

        return isErased;
    }

    void calibrate(double sum) {
        for (auto& x : numbers)
            if (x && x < sum)
                x = x.value() + 1;
            else if (x && x > sum)
                x = x.value() - 1;
    }

    int getSum() const {
        return std::accumulate(numbers.begin(), numbers.end(), 0,
                               [](const int& acc, const auto& x) {
                                   return x ? acc + x.value() : acc;
                               });
    }

    double getAverage() const {
        int sum = 0;
        int count = 0;

        auto* cur = this;
        while (cur) {
            for (std::size_t i = 0; i < cur->numbers.size(); ++i)
                if (cur->numbers[i]) {
                    sum += cur->numbers[i].value();
                    ++count;
                }
            cur = cur->next;
        }

        return static_cast<double>(sum) / count;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, T;
    std::cin >> N >> M >> T;

    std::vector<Disc> discs;
    for (int i = 0; i < N; ++i) {
        std::vector<int> numbers(M);
        for (auto& number : numbers) std::cin >> number;
        discs.emplace_back(numbers);
    }

    discs[0].next = &discs[1];
    discs[N - 1].prev = &discs[N - 2];
    for (int i = 1; i < N - 1; ++i) {
        discs[i].prev = &discs[i - 1];
        discs[i].next = &discs[i + 1];
    }

    for (int i = 0; i < T; ++i) {
        int x, d, k;
        std::cin >> x >> d >> k;

        bool isErased = false;
        for (int j = x - 1; j < N; j += x) discs[j].rotate(d, k);
        for (auto& disc : discs) isErased |= disc.sanitize();

        if (!isErased) {
            double avg = discs[0].getAverage();
            for (auto& disc : discs) disc.calibrate(avg);
        }
    }

    std::cout << std::accumulate(discs.begin(), discs.end(), 0,
                                 [](const int& acc, const auto& disc) {
                                     return acc + disc.getSum();
                                 })
              << '\n';

    return 0;
}
