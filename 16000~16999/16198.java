package introduction_to_java_programming;

import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            final int N = sc.nextInt();
            LinkedList<Integer> marbles = new LinkedList<>();
            for (int i = 0; i < N; ++i)
                marbles.add(sc.nextInt());
            System.out.println(new EnergyMarbles(marbles).backtrack(N));
        }
    }
}

class EnergyMarbles {
    final LinkedList<Integer> marbles;

    EnergyMarbles(LinkedList<Integer> marbles) {
        this.marbles = marbles;
    }

    int backtrack(int curSize) {
        if (curSize == 2)
            return 0;

        var curMax = Integer.MIN_VALUE;
        for (int i = 1; i < curSize - 1; ++i) {
            var cur = marbles.get(i);
            marbles.remove(i);
            var curEnergy = backtrack(curSize - 1) + marbles.get(i - 1) * marbles.get(i);
            curMax = Math.max(curMax, curEnergy);
            marbles.add(i, cur);
        }

        return curMax;
    }
}