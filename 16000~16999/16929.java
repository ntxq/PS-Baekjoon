package introduction_to_java_programming;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int rows = sc.nextInt();
            int cols = sc.nextInt();

            char[][] dots = new char[rows][cols];
            for (int i = 0; i < rows; ++i)
                dots[i] = sc.next().toCharArray();

            var twoDots = new TwoDots(dots, rows, cols);
            if (twoDots.isCycle())
                System.out.println("Yes");
            else
                System.out.println("No");
        }
    }
}

class TwoDots {
    private final char[][] dots;
    private final int rows;
    private final int cols;

    public TwoDots(char[][] dots, int rows, int cols) {
        this.dots = dots;
        this.rows = rows;
        this.cols = cols;
    }

    private List<List<Integer>> getAdj() {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < rows * cols; ++i)
            adj.add(new ArrayList<>());

        final int[] dx = { 0, 0, 1, -1 };
        final int[] dy = { 1, -1, 0, 0 };
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                int curIdx = i * cols + j;

                for (int k = 0; k < 4; ++k) {
                    int nx = j + dx[k];
                    int ny = i + dy[k];

                    if (0 <= nx && nx < cols && 0 <= ny && ny < rows && dots[i][j] == dots[ny][nx]) {
                        int nextIdx = ny * cols + nx;
                        adj.get(curIdx).add(nextIdx);
                    }
                }
            }

        return adj;
    }

    private boolean dfs(int p, int u, List<List<Integer>> adj, boolean[] visited) {
        visited[u] = true;
        for (var v : adj.get(u))
            if (p != v && (visited[v] || dfs(u, v, adj, visited)))
                return true;

        return false;
    }

    public boolean isCycle() {
        var adj = getAdj();
        boolean[] visited = new boolean[rows * cols];

        for (int i = 0; i < rows * cols; ++i)
            if (!visited[i] && dfs(-1, i, adj, visited))
                return true;

        return false;
    }
}