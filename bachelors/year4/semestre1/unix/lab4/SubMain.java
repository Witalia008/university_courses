import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;

/**
 * Created by witalia on 05.11.15.
 */
public class SubMain {
    public static void main(String[] args) throws IOException, InterruptedException {
        DataInputStream reader = new DataInputStream(new BufferedInputStream(System.in));
        while (reader.available() > 0) {
            float x = reader.readFloat();
            float f_my = reader.readFloat();
            float f_std = reader.readFloat();
            float diff = reader.readFloat();

            System.out.println(String.format("Math.pow(1+%f, 1/4) = %f", x, f_std));
            System.out.println(String.format("My estimate (1+%f)^(1/4) = %f", x, f_my));
            System.out.println(String.format("Error: %f\n", diff));

            Thread.sleep(100);
        }
    }
}
