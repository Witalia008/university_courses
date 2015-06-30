import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.URL;

/**
 * Created by Witalia on 29.11.14.
 */
public class Main {
    public static void main(String[] args) {
        try {
            /*BufferedImage image = ImageIO.read(
                    new URL("http://www.technotrigger.com/" +
                            "wp-content/uploads/2014/01/" +
                            "house-in-green-field.jpg")
            );
            ImageIO.write(image, "jpeg", new File("saved.jpg"));*/
            BufferedImage image = ImageIO.read(
                    new File("saved.jpg")
            );
            BufferedImage temp = Koch.insertMessage(
                    image,
                    "Hello, World!"
            );
            ImageIO.write(temp, "jpeg", new File("temp.jpg"));
            System.out.println(
                    Koch.readMessage(temp)
            );
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
