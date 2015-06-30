package sample;

import java.io.*;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Witalia on 29.11.14.
 */
public class FileUtils {
    public static Set<String> getWords(File file) {
        if (file.isDirectory() || !file.canRead()) {
            return null;
        }
        try {
            Set<String> res = new HashSet<>();
            Files.lines(file.toPath()).forEach(e->{
//                System.out.println(Arrays.toString(e.split("[^\\w+]")));
                for (String cur : e.split("[^\\w+]")) {
                    if (!cur.isEmpty() && Character.isAlphabetic(cur.charAt(0))) {
                        res.add(cur);
                    }
                }
            });
            return res;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Set<String> getWords(File[] files) {
        if (files == null) {
            return null;
        }
        Set<String> res = new HashSet<>();
        for (File cur : files) {
            Set s = getWords(cur);
            if (s != null) {
                res.addAll(s);
            }
        }
        return res;
    }

    public static int getWordsCount(File[] files) {
        Set<String> set = getWords(files);
        return (set == null ? 0 : set.size());
    }
}
