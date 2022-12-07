package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int rows = sc.nextInt();
            int cols = sc.nextInt();

            int[][] heights = new int[rows][cols];
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < cols; ++j)
                    heights[i][j] = sc.nextInt();

            System.out.println(new Shapes(rows, cols, heights).getSurface());
        }
    }
}

class Shapes {
    private int rows;
    private int cols;
    private int[][] heights;

    public Shapes(int rows, int cols, int[][] heights) {
        this.rows = rows;
        this.cols = cols;
        this.heights = heights;
    }

    public int getSurface() {
        int leftView = 0;
        for (int i = 0; i < rows; ++i) {
            int curSum = heights[i][0];
            for (int j = 1; j < cols; ++j)
                if (heights[i][j] > heights[i][j - 1])
                    curSum += heights[i][j] - heights[i][j - 1];
            leftView += curSum;
        }

        int rightView = 0;
        for (int i = 0; i < rows; ++i) {
            int curSum = heights[i][cols - 1];
            for (int j = cols - 2; j >= 0; --j)
                if (heights[i][j] > heights[i][j + 1])
                    curSum += heights[i][j] - heights[i][j + 1];
            rightView += curSum;
        }

        int frontView = 0;
        for (int j = 0; j < cols; ++j) {
            int curSum = heights[0][j];
            for (int i = 1; i < rows; ++i)
                if (heights[i][j] > heights[i - 1][j])
                    curSum += heights[i][j] - heights[i - 1][j];
            frontView += curSum;
        }

        int backView = 0;
        for (int j = 0; j < cols; ++j) {
            int curSum = heights[rows - 1][j];
            for (int i = rows - 2; i >= 0; --i)
                if (heights[i][j] > heights[i + 1][j])
                    curSum += heights[i][j] - heights[i + 1][j];
            backView += curSum;
        }

        return leftView + rightView + frontView + backView + 2 * (rows * cols);
    }
}