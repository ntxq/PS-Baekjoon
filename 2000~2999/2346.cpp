#include <algorithm>
#include <iostream>

struct Node {
   public:
    Node* prev;
    Node* next;
    int dist;
    int index;

    Node(Node* prev, Node* next, int dist, int index)
        : prev(prev), next(next), dist(dist), index(index) {}
    Node(int index) : Node(nullptr, nullptr, 0, index) {}
};

void progress(Node* cur) {
    std::cout << cur->index << ' ';
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;

    int curDist = cur->dist;
    Node* target = cur;

    while (curDist > 0) {
        target = target->next;
        curDist--;
    }

    while (curDist < 0) {
        target = target->prev;
        curDist++;
    }

    delete cur;
    if (cur != target) progress(target);

    return;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    Node* head = new Node(1);
    std::cin >> head->dist;

    Node* cur = head;
    for (int i = 1; i < N; ++i) {
        int dist;
        std::cin >> dist;
        cur->next = new Node(cur, nullptr, dist, i + 1);
        cur = cur->next;
    }

    cur->next = head;
    head->prev = cur;

    progress(head);

    return 0;
}