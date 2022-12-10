package introduction_to_java_programming;

import java.util.Scanner;
import java.util.function.IntBinaryOperator;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            int N = sc.nextInt();
            int[] operands = new int[N];
            for (int i = 0; i < N; ++i)
                operands[i] = sc.nextInt();
            int[] bags = new int[4];
            for (int i = 0; i < 4; ++i)
                bags[i] = sc.nextInt();

            var minMaxOperator = new MinMaxOperator(operands, bags);
            System.out.println(minMaxOperator.max);
            System.out.println(minMaxOperator.min);
        }
    }
}

class MinMaxOperator {
    private int[] operands;
    private int[] bags;

    public int min = Integer.MAX_VALUE;
    public int max = Integer.MIN_VALUE;

    private static final IntBinaryOperator[] operators = new IntBinaryOperator[] {
            (a, b) -> a + b,
            (a, b) -> a - b,
            (a, b) -> a * b,
            (a, b) -> a / b
    };

    public MinMaxOperator(int[] operands, int[] bags) {
        this.operands = operands;
        this.bags = bags;

        backtrack(0, operands[0]);
    }

    private void backtrack(int idx, int curVal) {
        if (idx == operands.length - 1) {
            if (curVal < min)
                min = curVal;
            if (curVal > max)
                max = curVal;

            return;
        }

        for (int i = 0; i < operators.length; ++i)
            if (bags[i] > 0) {
                --bags[i];
                backtrack(idx + 1, operators[i].applyAsInt(curVal, operands[idx + 1]));
                ++bags[i];
            }
    }
}