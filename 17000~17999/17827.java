package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            int v = sc.nextInt();
            int[] list = new int[n];
            for (int i = 0; i < n; ++i)
                list[i] = sc.nextInt();

            var snail = new SnailList(list, v);

            final var sb = new StringBuilder();
            for (int i = 0; i < m; ++i)
                sb.append(snail.query(sc.nextInt())).append('\n');
            System.out.println(sb);
        }
    }
}

class SnailList {
    private final int[] list;
    private final int snailIdx;

    public SnailList(int[] list, int snailIdx) {
        this.list = list;
        this.snailIdx = snailIdx;
    }

    public int query(int k) {
        if (k < snailIdx)
            return list[k];

        final int cycleLength = list.length - snailIdx + 1;
        final int afterSnailIdx = k - snailIdx + 1;

        final int idx = (snailIdx + (afterSnailIdx % cycleLength) - 1) % list.length;

        return list[idx];
    }
}
