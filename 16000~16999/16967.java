package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int rows, cols, xOffset, yOffset;
            rows = sc.nextInt();
            cols = sc.nextInt();
            yOffset = sc.nextInt();
            xOffset = sc.nextInt();

            int[][] transformed = new int[rows + yOffset][cols + xOffset];
            for (int i = 0; i < rows + yOffset; ++i)
                for (int j = 0; j < cols + xOffset; ++j)
                    transformed[i][j] = sc.nextInt();

            int[][] original = new Transformed(transformed, rows, cols, xOffset, yOffset).getOriginal();
            for (var row : original) {
                for (var col : row)
                    System.out.print(col + " ");
                System.out.println();
            }
        }
    }
}

class Transformed {
    int[][] transformed;
    int rows;
    int cols;
    int xOffset;
    int yOffset;

    Transformed(int[][] transformed, int rows, int cols, int xOffset, int yOffset) {
        this.transformed = transformed;
        this.rows = rows;
        this.cols = cols;
        this.xOffset = xOffset;
        this.yOffset = yOffset;
    }

    int[][] getOriginal() {
        int[][] original = new int[rows][cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (0 <= i - yOffset && 0 <= j - xOffset)
                    original[i][j] = transformed[i][j] - original[i - yOffset][j - xOffset];
                else
                    original[i][j] = transformed[i][j];

        return original;
    }
}