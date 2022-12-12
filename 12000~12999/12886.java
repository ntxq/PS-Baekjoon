package introduction_to_java_programming;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int[] stones = new int[3];
            for (int i = 0; i < 3; i++)
                stones[i] = sc.nextInt();

            System.out.println(bfs(stones) ? 1 : 0);
        }
    }

    public static boolean bfs(final int[] stones) {
        class Triple {
            int a, b, c;

            public Triple(int a, int b, int c) {
                this.a = a;
                this.b = b;
                this.c = c;
            }
        }

        final Queue<Triple> q = new LinkedList<>();
        final boolean[][] visited = new boolean[1501][1501];

        Arrays.sort(stones);
        visited[stones[0]][stones[2]] = true;
        q.add(new Triple(stones[0], stones[1], stones[2]));

        while (!q.isEmpty()) {
            var t = q.remove();

            if (t.a == t.b && t.b == t.c)
                return true;

            if (t.a != t.b) {
                int a = Math.max(t.a, t.b);
                int b = Math.min(t.a, t.b);
                int c = t.c;

                a = a - b;
                b = b + b;

                int curMax = Math.max(a, Math.max(b, c));
                int curMin = Math.min(a, Math.min(b, c));

                if (!visited[curMin][curMax]) {
                    visited[curMin][curMax] = true;
                    q.add(new Triple(a, b, c));
                }
            }

            if (t.a != t.c) {
                int a = Math.max(t.a, t.c);
                int b = t.b;
                int c = Math.min(t.a, t.c);

                a = a - c;
                c = c + c;

                int curMax = Math.max(a, Math.max(b, c));
                int curMin = Math.min(a, Math.min(b, c));

                if (!visited[curMin][curMax]) {
                    visited[curMin][curMax] = true;
                    q.add(new Triple(a, b, c));
                }
            }

            if (t.b != t.c) {
                int a = t.a;
                int b = Math.max(t.b, t.c);
                int c = Math.min(t.b, t.c);

                b = b - c;
                c = c + c;

                int curMax = Math.max(a, Math.max(b, c));
                int curMin = Math.min(a, Math.min(b, c));

                if (!visited[curMin][curMax]) {
                    visited[curMin][curMax] = true;
                    q.add(new Triple(a, b, c));
                }
            }
        }

        return false;
    }
}