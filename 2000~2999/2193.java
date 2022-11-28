package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    static final long[] dp = new long[91];
    static {
        dp[1] = 1;
        dp[2] = 1;

        for (int i = 3; i < 91; ++i)
            dp[i] = dp[i - 2] + dp[i - 1];
    }

    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            System.out.println(dp[sc.nextInt()]);
        }
    }
}