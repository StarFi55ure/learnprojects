package org.dyndns.ratel;

import edu.princeton.cs.introcs.In;
import edu.princeton.cs.introcs.StdOut;

import java.time.LocalDateTime;
import java.util.Arrays;

public class TwoSumFast {

    public static int count2(int[] a) {
        Arrays.sort(a);
        int N = a.length;
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            if (BinarySearch.rank(-a[i], a) > i) {
                cnt++;
            }
        }
        return cnt;
    }

    public static void main(String[] args) {
        LocalDateTime now = LocalDateTime.now();
        int start = now.getSecond();

        int[] a = In.readInts(args[0]);
        StdOut.println(count2(a));

        int end = now.getSecond();
        System.out.println("process time: " + (end - start) + " s");
    }
}
