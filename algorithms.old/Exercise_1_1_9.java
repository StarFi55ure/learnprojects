import java.io.IOException;

/**
 * Created by julian on 2015/01/27.
 */


public class Exercise_1_1_9 {

    public static void main(String[] args) {
        System.out.println("Exercise 1.1.9");

        try {
            Process exec = Runtime.getRuntime().exec("/bin/ls -l");
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
