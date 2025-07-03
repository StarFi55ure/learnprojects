import edu.princeton.cs.introcs.StdOut;

/**
 * Created by julian on 2015/01/27.
 */


public class Exercise_1_1_13 {

    public static void main(String[] args) {

        int M = 6;
        int N = 8;

        int[][] matrix = new int[M][N];

        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                matrix[i][j] = (int) (Math.random() * 1000);
            }
        }

        StdOut.println("Original Matrix: ");
        StdOut.println("");
        Util.printMatrix(matrix);

        int[][] transMatrix = Util.transposeMatrix(matrix);
        StdOut.println("Transposed Matrix: ");
        StdOut.println("");

        Util.printMatrix(transMatrix);
    }
}
