import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.*;

/**
 * Created by Witalia on 29.11.14.
 */
public class Koch {
    private static final int P = 25;
    private static final int C = 150;
    private static final Point fst = new Point(3, 4);
    private static final Point snd = new Point(4, 3);

    static private void simpleTransform(double[][] dct, Point a, Point b) {
        dct[a.x][a.y] = (C + dct[b.x][b.y])
                        * (dct[a.x][a.y] >= 0 ? 1 : -1);
    }

    static private BufferedImage insertMessage(BufferedImage img, BitSet msg) {
        BufferedImage res = ImageUtils.deepCopy(img);
        int pos = 0;

        mainLoop:
        for (int i = 0; i < img.getWidth(); i += 8) {
            for (int j = 0; j < img.getHeight(); j += 8) {
                if (pos >= msg.size()) {
                    break mainLoop;
                }
                Color[][] temp = ImageUtils.readPiece(j, i, img);
                double[][] dct = DCT.DCT(temp);

                double k = Math.abs(dct[fst.x][fst.y]) - Math.abs(dct[snd.x][snd.y]);
                if (msg.get(pos)) {
                    if (k <= P) {
                        simpleTransform(dct, fst, snd);
                    }
                } else {
                    if (k >= -P) {
                        simpleTransform(dct, snd, fst);
                    }
                }

                temp = DCT.inverseDCT(dct, temp);
                ImageUtils.writePiece(j, i, res, temp);
                ++pos;
            }
        }
        return res;
    }

    static public BufferedImage insertMessage(BufferedImage img, String msg) {
        return insertMessage(img, BitSet.valueOf(msg.getBytes()));
    }

    static public String readMessage(BufferedImage image) {
        StringBuffer res = new StringBuffer();

        int pos = 0;
        int b = 0;

        mainLoop:
        for (int i = 0; i < image.getWidth(); i += 8) {
            for (int j = 0; j < image.getHeight(); j += 8) {
                Color[][] temp = ImageUtils.readPiece(j, i, image);
                double[][] dct = DCT.DCT(temp);

                double k = Math.abs(dct[fst.x][fst.y]) - Math.abs(dct[snd.x][snd.y]);
                byte cur = 0;
                if (k >= P) {
                    cur = 1;
                } else if (k <= -P) {
                    cur = 0;
                } else {
                    break mainLoop;
                }

                b |= (cur << pos);        // probably another endianness
                ++pos;
                if (pos == 8) {
                    res.append((char) b);
                    pos = b = 0;
                }
            }
        }

        return res.toString();
    }
}
