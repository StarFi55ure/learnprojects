

import edu.princeton.cs.introcs.StdOut;

import java.util.Formatter;

public class Util {

    public static void printMatrix(int[][] matrix) {

        int m_length = matrix.length;
        int n_length = matrix[0].length;

        StringBuilder headerrow = new StringBuilder();
        headerrow.append("      ");

        Formatter formatter = new Formatter(headerrow);

        for(int i=0; i<n_length; i++) {
            formatter.format(" %4d", i+1);
        }

        StdOut.println(headerrow.toString());

        StringBuilder rows = new StringBuilder();

        for (int i=0; i < m_length; i++) {
            Formatter row_formatter = new Formatter(rows);

            row_formatter.format("Rw: %2d", i);

            for (int j=0; j < n_length; j++) {
                row_formatter.format(" %4d", matrix[i][j]);
            }

            rows.append('\n');
        }

        StdOut.println(rows.toString());
    }

    public static int[][] transposeMatrix(int[][] in_matrix) {

        int out_cols = in_matrix.length;
        int out_rows = in_matrix[0].length;

        int[][] out_matrix = new int[out_rows][out_cols];

        for (int i=0; i<out_cols; i++) {
            for (int j=0; j<out_rows; j++) {
                out_matrix[j][i] = in_matrix[i][j];
            }
        }

        return out_matrix;
    }
}
