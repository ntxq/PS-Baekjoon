#include <iostream>
#include <vector>

int main() {
    int size, limit;
    std::cin >> size >> limit;

    std::vector<int> deck;
    for (int i = 0, card; i < size; ++i) {
        std::cin >> card;
        deck.push_back(card);
    }

    int max = 0;
    for (unsigned i = 0; i < deck.size(); ++i)
        for (unsigned j = i + 1; j < deck.size(); ++j)
            for (unsigned k = j + 1; k < deck.size(); ++k)
                if (deck[i] + deck[j] + deck[k] <= limit &&
                    deck[i] + deck[j] + deck[k] > max)
                    max = deck[i] + deck[j] + deck[k];

    std::cout << max;

    return 0;
}