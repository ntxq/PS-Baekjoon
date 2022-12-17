package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            final int N = sc.nextInt();
            final int M = sc.nextInt();

            final int[][] dist = new int[N][N];
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    dist[i][j] = sc.nextInt();
            final FloydWarshall floydWarshall = new FloydWarshall(N, dist);

            var sb = new StringBuilder();
            for (int i = 0; i < M; ++i) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                int w = sc.nextInt();
                if (floydWarshall.query(u - 1, v - 1, w))
                    sb.append("Enjoy other party\n");
                else
                    sb.append("Stay here\n");
            }
            System.out.print(sb);
        }
    }
}

class FloydWarshall {
    private final int V;
    private final int[][] dist;

    FloydWarshall(int V, int[][] dist) {
        this.V = V;
        this.dist = dist;

        floydWarshall();
    }

    void floydWarshall() {
        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
    }

    boolean query(int u, int v, int w) {
        return dist[u][v] <= w;
    }
}