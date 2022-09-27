package introduction_to_java_programming;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static class Pair {
        private final int x;
        private final int y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int x() {
            return x;
        }

        public int y() {
            return y;
        }
    }

    public static void main(String[] args) {
        try (final var sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            final var points = new ArrayList<Pair>(N);
            for (int i = 0; i < N; ++i)
                points.add(new Pair(sc.nextInt(), sc.nextInt()));

            int minDist = Integer.MAX_VALUE;
            var minPair = points.get(0);
            for (final var p1 : points) {
                int maxDist = 0;
                for (final var p2 : points)
                    if (getDistance(p1, p2) > maxDist)
                        maxDist = getDistance(p1, p2);

                if (maxDist <= minDist) {
                    minDist = maxDist;
                    minPair = p1;
                }
            }

            System.out.println(minPair.x() + " " + minPair.y());
        }
    }

    public static int getDistance(Pair p1, Pair p2) {
        int dx = p1.x() - p2.x();
        int dy = p1.y() - p2.y();
        return dx * dx + dy * dy;
    }
}
