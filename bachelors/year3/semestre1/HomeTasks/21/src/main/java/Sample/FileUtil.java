package Sample;

import java.io.File;

/**
 * Created by Witalia on 15.11.2014.
 */
public class FileUtil {
    public static boolean fileExists(String filePath){
        File f = new File(filePath);
        return f.exists();
    }
}
