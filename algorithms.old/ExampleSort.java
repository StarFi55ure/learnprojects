package org.dyndns.ratel;

import edu.princeton.cs.introcs.In;
import edu.princeton.cs.introcs.StdOut;

import java.util.concurrent.ConcurrentMap;

public class ExampleSort {
    
    private static void sort(Comparable[] a) {
    
    }
    
    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }
    
    private static void exch(Comparable[] a, int i, int j) {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    
    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }
    
    private static boolean isSorted(Comparable[] a) {
        for(int i = 0; i < a.length; i++) {
            if (less(a[i], a[i-1]))
                return false;
        }
        return true;
    }
    
    public static void main(String[] args) {
        System.out.println("Algorithms");
        String[] a = In.readStrings();
        sort(a);
        assert isSorted(a);
        show(a);
    }
}

