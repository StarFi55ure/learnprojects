
import edu.princeton.cs.introcs.StdOut;

import java.io.IOException;


public class Exercise_1_1_19 {

    public static long[] cache = null;

    public static long F(int N) {

        if (cache != null && cache[N] > -1) {
            return cache[N];
        }

        if (N==0) return 0;
        if (N==1) return 1;
        StdOut.println(N + ": " + (N-1) + ", " + (N-2));
        long t = F(N-1) + F(N-2);
        if (cache != null) {
            StdOut.println("saving " + N + " into cache");
            cache[N] = t;
        }
        return t;
    }

    public static void main(String[] args) {

        int cnt = 100;

        cache = new long[cnt];

        if (cache != null) {
            for (int i = 0; i < cnt; i++) {
                cache[i] = -1;
            }
        }

        for (int N=0; N < cnt; N++) {
            StdOut.println(N + " --> " + F(N));
        }

    }
}
