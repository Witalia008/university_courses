import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.WritableRaster;

/**
 * Created by Witalia on 29.11.14.
 */
public class ImageUtils {
    public static Color[][] readPiece(int x, int y, BufferedImage image) {
        Color[][] res = new Color[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; ++j) {
                res[i][j] = new Color(
                        (i + x < image.getWidth() && j + y < image.getHeight())
                                ? image.getRGB(i + x, j + y) : 0
                );
            }
        }
        return res;
    }

    public static void writePiece(int x, int y, BufferedImage image, Color[][] piece) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; ++j) {
                if (i + x < image.getWidth() && j + y < image.getHeight()) {
                    image.setRGB(i + x, j + y, piece[i][j].getRGB());
                }
            }
        }
    }

    public static BufferedImage deepCopy(BufferedImage source) {
        ColorModel colorModel = source.getColorModel();
        boolean isAlphaPremultiplied = colorModel.isAlphaPremultiplied();
        WritableRaster raster = source.copyData(null);
        return new BufferedImage(
                colorModel,
                raster,
                isAlphaPremultiplied,
                null
        );
    }
}
