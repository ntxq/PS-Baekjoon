package introduction_to_java_programming;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int[] A = new int[N];
            for (int i = 0; i < N; ++i)
                A[i] = sc.nextInt();
            System.out.println(maxIncSeq(A));
        }
    }

    public static int maxIncSeq(int[] A) {
        int[] dp = A.clone();

        for (int i = 1; i < A.length; ++i)
            for (int j = 0; j < i; ++j)
                if (A[j] < A[i] && dp[j] + A[i] > dp[i])
                    dp[i] = dp[j] + A[i];

        return Arrays.stream(dp).max().getAsInt();
    }
}