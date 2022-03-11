#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

long long direction(long long xi, long long yi, long long xj, long long yj, long long xk, long long yk) {
    return (xk - xi) * (yj - yi) - (yk - yi) * (xj - xi);
}

bool onSegment(long long xi, long long yi, long long xj, long long yj, long long xk, long long yk) {
    long long xmin = std::min(xi, xj);
    long long xmax = std::max(xi, xj);
    long long ymin = std::min(yi, yj);
    long long ymax = std::max(yi, yj);

    if (xmin <= xk && xk <= xmax && ymin <= yk && yk <= ymax) return true;

    return false;
}

bool segmentsIntersect(const std::vector<long long>& i, const std::vector<long long>& j,
                       const std::vector<long long>& k, const std::vector<long long>& l) {
    long long d1 = direction(k[0], k[1], l[0], l[1], i[0], i[1]);
    long long d2 = direction(k[0], k[1], l[0], l[1], j[0], j[1]);
    long long d3 = direction(i[0], i[1], j[0], j[1], k[0], k[1]);
    long long d4 = direction(i[0], i[1], j[0], j[1], l[0], l[1]);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    else if (!d1 && onSegment(k[0], k[1], l[0], l[1], i[0], i[1]))
        return true;
    else if (!d2 && onSegment(k[0], k[1], l[0], l[1], j[0], j[1]))
        return true;
    else if (!d3 && onSegment(i[0], i[1], j[0], j[1], k[0], k[1]))
        return true;
    else if (!d4 && onSegment(i[0], i[1], j[0], j[1], l[0], l[1]))
        return true;

    return false;
}

long long find(long long x, std::vector<long long>& parents) {
    long long root = x;
    while (parents[root] != root) root = parents[root];

    while (parents[x] != root) {
        long long temp = parents[x];
        parents[x] = root;
        x = temp;
    }

    return root;
}

void unite(long long x, long long y, std::vector<long long>& parents, std::vector<long long>& sizes,
           long long& maxSize, long long& groupCount) {
    long long xroot = find(x, parents);
    long long yroot = find(y, parents);

    if (xroot == yroot) return;

    --groupCount;
    if (sizes[xroot] < sizes[yroot]) {
        parents[xroot] = yroot;
        sizes[yroot] += sizes[xroot];

        if (sizes[yroot] > maxSize) maxSize = sizes[yroot];
    } else {
        parents[yroot] = xroot;
        sizes[xroot] += sizes[yroot];

        if (sizes[xroot] > maxSize) maxSize = sizes[xroot];
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long n;
    std::cin >> n;

    std::vector<std::vector<std::vector<long long>>> segments(
        n, std::vector<std::vector<long long>>(2, std::vector<long long>(2)));
    for (auto& segment : segments)
        std::cin >> segment[0][0] >> segment[0][1] >> segment[1][0] >>
            segment[1][1];

    std::vector<long long> parents(n);
    std::iota(parents.begin(), parents.end(), 0);
    std::vector<long long> sizes(n, 1);

    long long maxSize = 1;
    long long groupCnt = n;

    for (long long i = 0; i < n; ++i)
        for (long long j = i + 1; j < n; ++j)
            if (segmentsIntersect(segments[i][0], segments[i][1],
                                  segments[j][0], segments[j][1]))
                unite(i, j, parents, sizes, maxSize, groupCnt);

    std::cout << groupCnt << '\n' << maxSize << '\n';

    return 0;
}
