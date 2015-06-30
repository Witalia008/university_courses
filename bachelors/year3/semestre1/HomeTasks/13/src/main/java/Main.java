import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.annotation.Annotation;
import java.lang.reflect.*;
/**
 * Created by Witalia on 13.10.2014.
 */
public class Main {
    public static void main(String[] args) {
        try {
            Loader loader = new Loader(ClassLoader.getSystemClassLoader(),
                    "target\\classes\\");
            String className = "";
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            className = br.readLine();
            Class targetClass = loader.findClass(className);
            Printer.printClass(targetClass, 0);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
