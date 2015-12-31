import org.json.JSONArray;
import org.json.JSONObject;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by Vitalii on 24-Oct-15
 * Project phw2.client
 */

public class Main {
    private static final double in_min_x = 0;
    private static final double in_max_x = 25;
    private static final double in_step = 2.5;

    private static ArrayList<Double> drange(double start, double stop, double step) {
        ArrayList<Double> res = new ArrayList<>();
        for (;start < stop; start += step) {
            res.add(start);
        }
        return res;
    }

    public static void main(String[] args) throws IOException {

        ArrayList<Double> xx = drange(in_min_x, in_max_x+1, in_step);
        ArrayList<Double> yy = new ArrayList<>(xx.size());
        for (double i : xx) {
            yy.add(Math.sin(i));
        }

        String url = "http://localhost:8000/remote/";
        String charset = "UTF-8";
        String p1 = Arrays.toString(xx.toArray()).replaceAll("\\[|\\]", "");
        String p2 = Arrays.toString(yy.toArray()).replaceAll("\\[|\\]", "");

        String query = String.format("x=%s&y=%s",
                URLEncoder.encode(p1, charset),
                URLEncoder.encode(p2, charset));

        URLConnection connection = new URL(url).openConnection();
        connection.setDoOutput(true); // make it POST
        connection.setRequestProperty("Accept-Charset", charset);
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded;charset=" + charset);

        try (OutputStream outputStream = connection.getOutputStream()) {
            outputStream.write(query.getBytes(charset));
        }

        InputStream response = connection.getInputStream();
        BufferedReader rd = new BufferedReader(new InputStreamReader(response));
        String resp = rd.readLine();

        JSONObject root = new JSONObject(resp);
        JSONArray arr = root.getJSONArray("arr");
        JSONArray res = root.getJSONArray("res");
        JSONObject splines = root.getJSONObject("splines");

        System.out.println("\nInput:");
        for (Object i : arr) {
            System.out.println(String.format("Dot(%.3f, %.3f)",
                    ((JSONObject) i).getDouble("x"), ((JSONObject)i).getDouble("y")));
        }

        System.out.println(splines);
        System.out.println("\nOutput:");
        for (Object j : splines.keySet()) {
            JSONObject i = (JSONObject) splines.get(j.toString());
            System.out.println(String.format("S(x) = %.3f + %.3f*x + %.3f*x^2/2 + %.3f*x^3/6 (x = %.3f)",
                    i.getDouble("a"), i.getDouble("b"), i.getDouble("c"), i.getDouble("d"), i.getDouble("x")));
        }

        System.out.println("\nOutput data:");
        for (Object i : res) {
            System.out.println(String.format("Dot(%.3f, %.3f)",
                    ((JSONObject)i).getDouble("x"), ((JSONObject)i).getDouble("y")));
        }
    }
}
