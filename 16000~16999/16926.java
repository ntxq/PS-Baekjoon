package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            int r = sc.nextInt();

            int[][] data = new int[n][m];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    data[i][j] = sc.nextInt();

            var result = new TurnArray(data, n, m);
            result.turnMany(r);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++)
                    System.out.print(result.data[i][j] + " ");
                System.out.println();
            }
        }
    }
}

class TurnArray {
    int[][] data;
    int rows;
    int cols;

    TurnArray(int[][] data, int rows, int cols) {
        this.data = data;
        this.rows = rows;
        this.cols = cols;
    }

    void turn() {
        if (rows < cols)
            for (int ring = 0; ring < rows / 2; ++ring)
                turnRing(ring);
        else
            for (int ring = 0; ring < cols / 2; ++ring)
                turnRing(ring);
    }

    void turnRing(int ring) {
        int start = data[ring][ring];

        for (int i = ring; i < cols - ring - 1; ++i)
            data[ring][i] = data[ring][i + 1];
        for (int i = ring; i < rows - ring - 1; ++i)
            data[i][cols - ring - 1] = data[i + 1][cols - ring - 1];
        for (int i = cols - ring - 1; i > ring; --i)
            data[rows - ring - 1][i] = data[rows - ring - 1][i - 1];
        for (int i = rows - ring - 1; i > ring; --i)
            data[i][ring] = data[i - 1][ring];

        data[ring + 1][ring] = start;
    }

    void turnMany(int times) {
        for (int i = 0; i < times; ++i)
            turn();
    }
}