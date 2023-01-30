#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int N, Q;
std::vector<int> sequence(100001);

int BUCKET_SIZE = 1800;
std::vector<std::vector<int>> buckets(60);

void updateBucket(int bucketIdx, int value, int replacement) {
    auto& bucket = buckets[bucketIdx];
    auto it = std::find(bucket.begin(), bucket.end(), value);
    bucket.erase(it);

    it = std::lower_bound(bucket.begin(), bucket.end(), replacement);
    bucket.insert(it, replacement);
}

void update(int idx, int replacement) {
    updateBucket(idx / BUCKET_SIZE, sequence[idx], replacement);
    sequence[idx] = replacement;
}

int query(int s, int e, int k) {
    int s_bucket = s / BUCKET_SIZE;
    int e_bucket = e / BUCKET_SIZE;

    if (s_bucket == e_bucket) {
        int count = 0;
        for (int i = s; i <= e; ++i)
            if (sequence[i] > k) ++count;
        return count;
    }

    int count = 0;
    for (int i = s; i < s_bucket * BUCKET_SIZE + BUCKET_SIZE; ++i)
        if (sequence[i] > k) ++count;
    for (int j = e; j >= e_bucket * BUCKET_SIZE; --j)
        if (sequence[j] > k) ++count;
    for (int i = s_bucket + 1; i < e_bucket; ++i) {
        auto& bucket = buckets[i];
        auto it = std::upper_bound(bucket.begin(), bucket.end(), k);
        count += bucket.end() - it;
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> sequence[i];
    for (int i = 1; i <= N; ++i)
        buckets[i / BUCKET_SIZE].push_back(sequence[i]);
    for (auto& bucket : buckets) std::sort(bucket.begin(), bucket.end());

    std::cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int idx, replacement;
            std::cin >> idx >> replacement;
            update(idx, replacement);
        } else {
            int s, e, k;
            std::cin >> s >> e >> k;
            std::cout << query(s, e, k) << '\n';
        }
    }

    return 0;
}
