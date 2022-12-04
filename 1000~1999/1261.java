package introduction_to_java_programming;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.Scanner;

public class Main {
    static List<List<Integer>> adj = new ArrayList<>();
    static boolean[] visited;

    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            var M = sc.nextInt();
            var N = sc.nextInt();

            var maze = new boolean[N][M];
            for (var i = 0; i < N; ++i) {
                var line = sc.next();
                for (var j = 0; j < M; ++j)
                    maze[i][j] = line.charAt(j) == '1';
            }

            System.out.println(new AlgoSpot(N, M, maze).solve());
        }
    }
}

class AlgoSpot {
    boolean[][] maze;
    final int N;
    final int M;

    AlgoSpot(int N, int M, boolean[][] maze) {
        this.N = N;
        this.M = M;
        this.maze = maze;
    }

    int solve() {
        class Pair {
            int x;
            int y;

            Pair(int x, int y) {
                this.x = x;
                this.y = y;
            }
        }

        Deque<Pair> q = new ArrayDeque<>();
        int[][] dist = new int[N][M];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                dist[i][j] = Integer.MAX_VALUE;

        q.addFirst(new Pair(0, 0));
        dist[0][0] = 0;

        while (!q.isEmpty() && dist[N - 1][M - 1] == Integer.MAX_VALUE) {
            Pair p = q.removeFirst();
            int curX = p.x;
            int curY = p.y;

            int[] dx = { 0, 0, 1, -1 };
            int[] dy = { 1, -1, 0, 0 };

            for (int i = 0; i < 4; ++i) {
                int nextX = curX + dx[i];
                int nextY = curY + dy[i];

                if (0 <= nextX && nextX < N && 0 <= nextY && nextY < M) {
                    if (maze[nextX][nextY] && dist[curX][curY] + 1 < dist[nextX][nextY]) {
                        dist[nextX][nextY] = dist[curX][curY] + 1;
                        q.addLast(new Pair(nextX, nextY));
                    } else if (!maze[nextX][nextY] && dist[curX][curY] < dist[nextX][nextY]) {
                        dist[nextX][nextY] = dist[curX][curY];
                        q.addFirst(new Pair(nextX, nextY));
                    }
                }
            }
        }

        return dist[N - 1][M - 1];
    }
}
