import edu.princeton.cs.introcs.StdOut;

public class Exercise_1_1_26 {

    public static void main(String[] args) {
        System.out.println("Exercise 1.1.26");

        int a = (int) (Math.random() * 1000);
        int b = (int) (Math.random() * 1000);
        int c = (int) (Math.random() * 1000);
        int t = 0;

        if (a > b) { t = a; a = b; b = t; }
        if (a > c) { t = a; a = c; c = t; }
        if (b > c) { t = b; b = c; c = t; }

        StdOut.println(a);
        StdOut.println(b);
        StdOut.println(c);
    }
}
