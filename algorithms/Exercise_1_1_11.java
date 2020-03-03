import edu.princeton.cs.introcs.StdOut;
import edu.princeton.cs.introcs.StdRandom;

/**
 * Created by julian on 2015/01/27.
 */


public class Exercise_1_1_11 {

    public static void main(String[] args) {
        System.out.println("Exercise 1.1.11");

        Boolean[][] myarray = new Boolean[5][5];

        for (int i=0; i < 5; i++) {
            for (int j=0; j < 5; j++) {
                myarray[i][j] = StdRandom.bernoulli();
            }
        }

        StdOut.println("       1 2 3 4 5");
        for (int i=0; i < 5; i++) {
            StdOut.print("Row " + i + ": ");
            for (int j=0; j < 5; j++) {
                if (myarray[i][j]) {
                    StdOut.print('*');
                } else {
                    StdOut.print(' ');
                }

                StdOut.print(' ');
            }
            StdOut.print('\n');
        }

    }
}
