import edu.princeton.cs.introcs.StdOut;
import edu.princeton.cs.introcs.StdRandom;
import edu.princeton.cs.introcs.Stopwatch;

public class SortCompare {

    public static double time(String alg, Double[] a) {
        Stopwatch timer = new Stopwatch();
        if (alg.equals("Insertion")) InsertionSort.sort(a);
        if (alg.equals("Selection")) SelectionSort.sort(a);
        if (alg.equals("Shell")) ShellSort.sort(a);
        
        return timer.elapsedTime();
    }
    
    public static double timeRandomInput(String alg, int N, int T) {
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++) {
            for (int i = 0; i < N; i++) {
                a[i] = StdRandom.uniform();
            }
            total += time(alg, a);
        }
        return total;
    }
    
    public static void main(String[] args) {
        String alg1 = args[0];
        String alg2 = args[1];
        
        int N = Integer.parseInt(args[2]);
        int T = Integer.parseInt(args[3]);
        
        // run
        double T1 = timeRandomInput(alg1, N, T);
        double T2 = timeRandomInput(alg2, N, T);
        StdOut.println(T1);
        StdOut.println(T2);
        
        StdOut.printf("For %d random Doubles\n    %s is", N, alg1);
        StdOut.printf(" %.1f time faster than %s\n", T2/T1, alg2);
    }
}
