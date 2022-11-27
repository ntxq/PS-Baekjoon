import java.util.*;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int target = sc.nextInt();
            int[] costs = new int[target + 1];
            for (int i = 0; i < target; ++i)
                costs[i] = sc.nextInt();

            System.out.println(minCost(target, costs));
        }
    }

    private static int minCost(int target, int[] costs) {
        int[] dp = new int[target + 1];
        dp[0] = 0;

        for (int i = 1; i <= target; ++i) {
            dp[i] = Integer.MAX_VALUE;
            for (int j = 0; j < costs.length && j < i; ++j)
                if (dp[i - j - 1] + costs[j] < dp[i])
                    dp[i] = dp[i - j - 1] + costs[j];
        }

        return dp[target];
    }
}
