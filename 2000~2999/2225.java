package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            System.out.println(countSum(sc.nextInt(), sc.nextInt()));
        }
    }

    public static int countSum(int N, int K) {
        final var MOD = 1000000000;
        final var DP = new int[K][N + 1];
        for (int i = 0; i <= N; ++i)
            DP[0][i] = 1;

        for (int i = 1; i < K; ++i) {
            for (int j = 0; j <= N; ++j) {
                for (int k = 0; k <= j; ++k) {
                    DP[i][j] += DP[i - 1][j - k];
                    DP[i][j] %= MOD;
                }
            }
        }

        return DP[K - 1][N];
    }
}