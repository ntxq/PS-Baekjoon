package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            int[] xs = new int[n];
            for (int i = 0; i < n; ++i)
                xs[i] = sc.nextInt();

            System.out.println(maxSubseqSum(xs));
        }
    }

    public static int maxSubseqSum(int[] xs) {
        int[][] maxSum = new int[xs.length][2];
        int curMax = xs[0];

        maxSum[0][0] = xs[0];
        maxSum[0][1] = xs[0];

        for (int i = 1; i < xs.length; ++i) {
            maxSum[i][0] = Math.max(maxSum[i - 1][0] + xs[i], xs[i]);
            maxSum[i][1] = Math.max(maxSum[i - 1][0], maxSum[i - 1][1] + xs[i]);
            curMax = Math.max(curMax, Math.max(maxSum[i][0], maxSum[i][1]));
        }

        return curMax;
    }
}