package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int N = 1 << sc.nextInt();
            int R = sc.nextInt();

            int[][] data = new int[N][N];
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    data[i][j] = sc.nextInt();

            SpinMatrix matrix = new SpinMatrix(data, N);
            for (int i = 0; i < R; ++i) {
                int op = sc.nextInt();
                int partition = 1 << sc.nextInt();

                switch (op) {
                    case 1 -> matrix.verticalFlip(partition);
                    case 2 -> matrix.horizontalFlip(partition);
                    case 3 -> matrix.rightRotate(partition);
                    case 4 -> matrix.leftRotate(partition);
                    case 5 -> matrix.subVerticalFlip(partition);
                    case 6 -> matrix.subHorizontalFlip(partition);
                    case 7 -> matrix.subRightRotate(partition);
                    case 8 -> matrix.subLeftRotate(partition);
                }
            }

            System.out.println(matrix);
        }
    }
}

class SpinMatrix {
    private int[][] data;
    private int size;

    public SpinMatrix(int[][] data, int size) {
        this.data = data;
        this.size = size;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (var row : data) {
            for (var col : row)
                sb.append(col).append(" ");
            sb.append("\n");
        }
        return sb.toString();
    }

    public void verticalFlip(int partition) {
        for (int row = 0; row < size; row += partition)
            for (int col = 0; col < size; col += partition) {
                for (int i = 0; i < partition / 2; ++i)
                    for (int j = 0; j < partition; ++j) {
                        int temp = data[row + i][col + j];
                        data[row + i][col + j] = data[row + partition - i - 1][col + j];
                        data[row + partition - i - 1][col + j] = temp;
                    }
            }
    }

    public void horizontalFlip(int partition) {
        for (int row = 0; row < size; row += partition)
            for (int col = 0; col < size; col += partition) {
                for (int i = 0; i < partition; ++i)
                    for (int j = 0; j < partition / 2; ++j) {
                        int temp = data[row + i][col + j];
                        data[row + i][col + j] = data[row + i][col + partition - j - 1];
                        data[row + i][col + partition - j - 1] = temp;
                    }
            }
    }

    public void rightRotate(int partition) {
        for (int row = 0; row < size; row += partition)
            for (int col = 0; col < size; col += partition)
                for (int ring = 0; ring < partition / 2; ++ring) {
                    int[] temp = new int[partition - 1 - 2 * ring];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        temp[i] = data[row + ring][col + ring + i];

                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + ring][col + ring + i] = data[row + partition - ring - 1 - i][col + ring];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + partition - ring - 1 - i][col + ring] = data[row + partition - ring - 1][col
                                + partition - ring - 1 - i];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + partition - ring - 1][col + partition - ring - 1 - i] = data[row + ring + i][col
                                + partition - ring - 1];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + ring + i][col + partition - ring - 1] = temp[i];
                }
    }

    public void leftRotate(int partition) {
        for (int row = 0; row < size; row += partition)
            for (int col = 0; col < size; col += partition)
                for (int ring = 0; ring < partition / 2; ++ring) {
                    int[] temp = new int[partition - 1 - 2 * ring];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        temp[i] = data[row + ring][col + ring + i];

                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + ring][col + ring + i] = data[row + ring + i][col + partition - ring - 1];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + ring + i][col + partition - ring - 1] = data[row + partition - ring - 1][col
                                + partition - ring - 1 - i];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + partition - ring - 1][col + partition - ring - 1 - i] = data[row + partition - ring
                                - 1 - i][col + ring];
                    for (int i = 0; i < partition - 1 - 2 * ring; ++i)
                        data[row + partition - ring - 1 - i][col + ring] = temp[i];
                }
    }

    public void subVerticalFlip(int partition) {
        verticalFlip(size);
        verticalFlip(partition);
    }

    public void subHorizontalFlip(int partition) {
        horizontalFlip(size);
        horizontalFlip(partition);
    }

    public void subRightRotate(int partition) {
        rightRotate(size);
        leftRotate(partition);
    }

    public void subLeftRotate(int partition) {
        leftRotate(size);
        rightRotate(partition);
    }
}