package univ.c3.II.oop.server;

import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Created by Witalia on 04.02.2015.
 */
public class PointData {
    private final Point[] moves = {
            new Point(1, 0),
            new Point(-1, 0),
            new Point(0, 1),
            new Point(0, -1),
            new Point(1, 1),
            new Point(-1, -1)
    };
    private final float sonicSpeed;
    private float[] res;
    private float[] data;
    private boolean[][] used;
    private int pos;
    private Rectangle rect;

    PointData(float sonicSpeed) {
        this.sonicSpeed = sonicSpeed;
    }

    public float[] getRes() {
        return res;
    }

    public PointData initialize(String filePath) {
        try {
            Scanner sc = new Scanner(new File(filePath));
            int n = sc.nextInt();
            int m = sc.nextInt();
            data = new float[n * m];
            for (int i = 0; i < n * m; i++) {
                sc.nextFloat(); // skip x
                sc.nextFloat(); // skip y
                data[i] = sc.nextFloat();
            }
            res = new float[(
                    (n - 1) * (2 * m - 1)   // number of lines 'almost vertical'
                    + n * (m - 1)           // number of horizontal
                    + 1) * 3];              // staring point (and 3 positions per point)
            pos = 0;
            used = new boolean[n * m][moves.length];
            rect = new Rectangle(n, m);
            System.out.println(res.length);
            fillOut(new Point(0, 0));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return this;
    }

    private int relativePos(Point v) {
        return v.x * rect.height + v.y;
    }

    private void fillOut(Point v) {
        int numV = relativePos(v);
        for (int i = 0; i < moves.length; ++i) {
            Point to = (Point) v.clone();
            to.translate(moves[i].x, moves[i].y);
            if (!used[numV][i] && rect.contains(to)) {
                int numTo = relativePos(to);
                used[numV][i] = true;
                used[numTo][i ^ 1] = true;
                fillOut(to);
            }
        }
        System.out.println(v);
        addPoint(v);
    }

    private void addPoint(Point v) {
        res[pos++] = (float) v.x / (rect.width - 1) * 2 - 1;
        res[pos++] = -data[relativePos(v)] * sonicSpeed / 2;
        res[pos++] = (float) v.y / (rect.height - 1) * 2 - 3;
    }
}