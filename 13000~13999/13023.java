package introduction_to_java_programming;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.IntStream;

public class Main {
    static List<List<Integer>> adj = new ArrayList<>();
    static boolean[] visited;

    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int M = sc.nextInt();

            for (int i = 0; i < N; ++i)
                adj.add(new ArrayList<>());
            visited = new boolean[adj.size()];

            for (int i = 0; i < M; ++i) {
                int u = sc.nextInt();
                int v = sc.nextInt();

                adj.get(u).add(v);
                adj.get(v).add(u);
            }

            if (IntStream.range(0, N).anyMatch(i -> DFS(i, 1)))
                System.out.println(1);
            else
                System.out.println(0);
        }
    }

    public static boolean DFS(int u, int curLength) {
        if (curLength > 4)
            return true;

        visited[u] = true;
        for (int v : adj.get(u))
            if (!visited[v] && DFS(v, curLength + 1))
                return true;
        visited[u] = false;

        return false;
    }
}