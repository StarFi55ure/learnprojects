import edu.princeton.cs.introcs.StdOut;

public class Exercise_1_1_14 {

    public static int lg(int N) {
        int cap_int = 1000;

        int base = 2;
        int test_exp = 1;
        int test_N = 0;

        while( test_N <= N) {
            test_N = 0;
            for (int i=0; i< test_exp; i++) {
                if (test_N == 0) {
                    test_N = base;
                } else {
                    test_N = base * test_N;
                }
            }
            test_exp++;
        }

        return test_exp - 2;
    }

    public static void main(String[] args) {

        StdOut.println("Int: " + lg(1));
        StdOut.println("Int: " + lg(8));
        StdOut.println("Int: " + lg(100));
        StdOut.println("Int: " + lg(56));
    }
}
