package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            System.out.println(countZoo(sc.nextInt()));
        }
    }

    public static int countZoo(int height) {
        final int MOD = 9901;

        int[] prev = { 1, 1, 1 };
        int[] cur = new int[3];

        for (int i = 1; i < height; ++i) {
            cur[0] = (prev[0] + prev[1] + prev[2]) % MOD;
            cur[1] = (prev[0] + prev[2]) % MOD;
            cur[2] = (prev[0] + prev[1]) % MOD;

            prev[0] = cur[0];
            prev[1] = cur[1];
            prev[2] = cur[2];
        }

        return (prev[0] + prev[1] + prev[2]) % MOD;
    }
}