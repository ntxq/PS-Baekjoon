#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

double lerp(double a, double b, double t) { return a + (b - a) * t; }

struct Cube {
    int p, q, r;

    static const std::vector<Cube> direction_vectors;
    static Cube cube_direction(int direction) {
        return direction_vectors[direction];
    }
    static Cube cube_neighbor(const Cube& cube, int direction) {
        return cube + cube_direction(direction);
    }
    static int cube_distance(const Cube& a, const Cube& b) {
        return (std::abs(a.p - b.p) + std::abs(a.q - b.q) +
                std::abs(a.r - b.r)) /
               2;
    }
    static Cube cube_lerp(const Cube& a, const Cube& b, double t) {
        double q = lerp(a.p, b.p, t);
        double r = lerp(a.q, b.q, t);
        double s = lerp(a.r, b.r, t);

        int qi = static_cast<int>(std::lround(q));
        int ri = static_cast<int>(std::lround(r));
        int si = static_cast<int>(std::lround(s));

        double q_diff = std::abs(qi - q);
        double r_diff = std::abs(ri - r);
        double s_diff = std::abs(si - s);

        if (q_diff > r_diff && q_diff > s_diff) {
            qi = -ri - si;
        } else if (r_diff > s_diff) {
            ri = -qi - si;
        } else {
            si = -qi - ri;
        }

        return {qi, ri, si};
    }
    static std::vector<Cube> cube_linedraw(const Cube& a, const Cube& b) {
        int N = cube_distance(a, b);
        std::vector<Cube> results;
        results.reserve(N + 1);
        double step = 1.0 / std::max(N, 1);
        for (int i = 0; i <= N; ++i) {
            results.push_back(cube_lerp(a, b, step * i));
        }
        return results;
    }
    static Cube idx_to_cube(int idx) {
        if (idx == 1) return {0, 0, 0};

        int ring_idx = 1;
        --idx;

        while (idx > 6 * ring_idx) {
            idx -= 6 * ring_idx;
            ++ring_idx;
        }

        Cube cube{-ring_idx + 1, -1, ring_idx};
        --idx;

        for (int i = 1; idx && i < ring_idx; ++i, --idx)
            cube = cube_neighbor(cube, 1);

        for (int i = 0; idx && i < ring_idx; ++i, --idx)
            cube = cube_neighbor(cube, 0);

        for (int i = 5; i > 1 && idx; --i)
            for (int j = 0; idx && j < ring_idx; ++j, --idx)
                cube = cube_neighbor(cube, i);

        return cube;
    }
    static int cube_to_idx(const Cube& a) {
        int ring_idx = cube_distance({0, 0, 0}, a);
        if (ring_idx == 0) return 1;

        int idx = 1;
        for (int i = 1; i < ring_idx; ++i) idx += 6 * i;

        Cube cube{-ring_idx + 1, -1, ring_idx};
        for (int i = 1; cube != a && i < ring_idx; ++i, ++idx)
            cube = cube_neighbor(cube, 1);
        for (int i = 0; cube != a && i < ring_idx; ++i, ++idx)
            cube = cube_neighbor(cube, 0);
        for (int i = 5; i > 1 && cube != a; --i)
            for (int j = 0; cube != a && j < ring_idx; ++j, ++idx)
                cube = cube_neighbor(cube, i);

        return idx + 1;
    }

    friend Cube operator+(const Cube& lhs, const Cube& rhs) {
        return {lhs.p + rhs.p, lhs.q + rhs.q, lhs.r + rhs.r};
    }
    friend Cube operator-(const Cube& lhs, const Cube& rhs) {
        return {lhs.p - rhs.p, lhs.q - rhs.q, lhs.r - rhs.r};
    }
    friend bool operator!=(const Cube& lhs, const Cube& rhs) {
        return lhs.p != rhs.p || lhs.q != rhs.q || lhs.r != rhs.r;
    }
};

const std::vector<Cube> Cube::direction_vectors{
    {1, 0, -1}, {1, -1, 0}, {0, -1, 1}, {-1, 0, 1}, {-1, 1, 0}, {0, 1, -1}};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int s, t;
    std::cin >> s >> t;

    Cube a = Cube::idx_to_cube(s);
    Cube b = Cube::idx_to_cube(t);

    auto path = Cube::cube_linedraw(a, b);
    for (const auto& cube : path) std::cout << Cube::cube_to_idx(cube) << ' ';
    std::cout << '\n';

    return 0;
}
