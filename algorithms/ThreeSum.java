package org.dyndns.ratel;

import edu.princeton.cs.introcs.In;
import edu.princeton.cs.introcs.StdOut;

import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class ThreeSum {

    public static int count(int[] a) {
        int N = a.length;
        int cnt = 0;
        for (int i=0; i < N; i++) {
            for (int j=i+1; j < N; j++) {
                for (int k=j+1; k < N; k++) {
                    if (a[i] + a[j] + a[k] == 0) {
                        cnt++;
                    }
                }
            }
        }
        return cnt;
    }

    public static void main(String[] args) {
        LocalDateTime start = LocalDateTime.now();

        int[] a = In.readInts(args[0]);
        StdOut.println(count(a));

        LocalDateTime end = LocalDateTime.now();
        Duration dur = Duration.between(start, end);
        System.out.println("process time: " + dur.getSeconds() + " s");
    }

}
