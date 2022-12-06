package introduction_to_java_programming;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        try (var sc = new Scanner(System.in)) {
            final int T = sc.nextInt();
            Gear[] gears = new Gear[T];

            for (int i = 0; i < T; ++i) {
                boolean[] poles = new boolean[8];
                String line = sc.next();
                for (int j = 0; j < 8; ++j)
                    poles[j] = line.charAt(j) == '1';
                gears[i] = new Gear(poles);
            }

            final int K = sc.nextInt();
            for (int i = 0; i < K; ++i) {
                int gear = sc.nextInt();
                int direction = sc.nextInt();

                Gear.rotate(gears, gear - 1, direction == 1);
            }

            int score = 0;
            for (int i = 0; i < T; ++i)
                if (gears[i].getTop())
                    ++score;

            System.out.println(score);
        }
    }
}

class Gear {
    private boolean[] poles;
    private int top = 0;

    Gear(boolean[] poles) {
        this.poles = poles;
    }

    boolean getTop() {
        return poles[top];
    }

    boolean getLeft() {
        return poles[(top + 6) % 8];
    }

    boolean getRight() {
        return poles[(top + 2) % 8];
    }

    void rotate(boolean direction) {
        if (direction)
            top = (top + 7) % 8;
        else
            top = (top + 1) % 8;
    }

    static void rotate(Gear[] gears, int gearNum, boolean direction) {

        // rotate gears to the left
        boolean curDirection = direction;
        boolean curLeft = gears[gearNum].getLeft();
        for (int i = gearNum; i > 0; --i)
            if (curLeft != gears[i - 1].getRight()) {
                curLeft = gears[i - 1].getLeft();
                curDirection = !curDirection;
                gears[i - 1].rotate(curDirection);
            } else {
                break;
            }

        // rotate gears to the right
        curDirection = direction;
        boolean curRight = gears[gearNum].getRight();
        for (int i = gearNum; i < gears.length - 1; ++i)
            if (curRight != gears[i + 1].getLeft()) {
                curRight = gears[i + 1].getRight();
                curDirection = !curDirection;
                gears[i + 1].rotate(curDirection);
            } else {
                break;
            }

        // rotate the gear itself
        gears[gearNum].rotate(direction);
    }
}