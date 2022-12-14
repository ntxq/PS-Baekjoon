package introduction_to_java_programming;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            var N = sc.nextInt();
            var K = sc.nextInt();
            var words = new String[N];
            for (var i = 0; i < N; ++i)
                words[i] = sc.next();
            var solver = new MaxLearnChar(words, K);
            System.out.println(solver.solve());
        }
    }
}

class MaxLearnChar {
    private final String[] words;
    private final int K;
    private boolean[][] bitWords;

    public MaxLearnChar(String[] words, int K) {
        this.words = words;
        this.K = K;
    }

    private void sanitize() {
        bitWords = Arrays.stream(words).map(word -> {
            var bitWord = new boolean[26];
            word.chars().forEach(c -> bitWord[c - 'a'] = true);
            return bitWord;
        }).filter(bitWord -> {
            var count = 0;
            for (var b : bitWord)
                if (b)
                    ++count;
            return count <= K;
        }).toArray(boolean[][]::new);
    }

    private int count(boolean[] selection) {
        var count = 0;
        for (var bitWord : bitWords) {
            var canRead = true;
            for (var i = 0; i < 26 && canRead; ++i)
                if (bitWord[i] && !selection[i])
                    canRead = false;
            if (canRead)
                ++count;
        }
        return count;
    }

    private int backtrack(int idx, int depth, boolean[] bag) {
        if (depth == K)
            return count(bag);
        else if (idx == 26)
            return 0;

        var max = backtrack(idx + 1, depth, bag);

        if (!bag[idx]) {
            bag[idx] = true;
            max = Math.max(max, backtrack(idx + 1, depth + 1, bag));
            bag[idx] = false;
        }

        return max;
    }

    public int solve() {
        if (K < 5)
            return 0;
        else if (K == 26)
            return words.length;
        sanitize();

        var bag = new boolean[26];
        bag['a' - 'a'] = true;
        bag['n' - 'a'] = true;
        bag['t' - 'a'] = true;
        bag['i' - 'a'] = true;
        bag['c' - 'a'] = true;
        return backtrack(0, 5, bag);
    }
}