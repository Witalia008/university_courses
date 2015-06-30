import java.lang.annotation.Annotation;
import java.lang.reflect.*;

/**
 * Created by Witalia on 13.10.2014.
 */
public class Printer {

    public static void printClass(Class targetClass, int level) {
        if (level == 0 && targetClass.getPackage() != null) {
            System.out.println("package " + targetClass.getPackage().getName() + ";\n");
        }

        System.out.print(
                getTabs(level)
                        + Modifier.toString(targetClass.getModifiers())
                        + " class "
                        + targetClass.getCanonicalName()
        );

        TypeVariable[] tv = targetClass.getTypeParameters();
        if (tv.length != 0) {
            System.out.print("<");
            for (int i = 0; i < tv.length; ++i) {
                System.out.print((i == 0 ? "" : ", ") + tv[i].getName());
            }
            System.out.print(">");
        }

        if (targetClass.getGenericSuperclass() != null)
            System.out.print("\n" + getTabs(level + 2) + "extends "
                    + targetClass.getGenericSuperclass().getTypeName());

        Type[] interfaces = targetClass.getGenericInterfaces();
        if (interfaces.length != 0) {
            System.out.print("\n" + getTabs(level + 2) + "implements");
            for (int i = 0; i < interfaces.length; ++i) {
                System.out.print((i == 0 ? "" : ",") + " " + interfaces[i].getTypeName());
            }
        }
        System.out.println(" {");

        Annotation[] annotations = targetClass.getAnnotations();
        if (annotations.length != 0) {
            for (Annotation cur : annotations) {
                System.out.println(getTabs(level + 1) + cur);
            }
        }
        System.out.println();

        Class[] declaredClasses = targetClass.getDeclaredClasses();
        for (Class cur : declaredClasses) {
            printClass(cur, level + 1);
        }

        System.out.println("\n" + getTabs(level + 1)
                + "// ---------- Fields ---------");
        printMember(targetClass.getDeclaredFields(), level + 1);

        System.out.println("\n" + getTabs(level + 1)
                + "// ---------- Constructors ---------");
        printMember(targetClass.getDeclaredConstructors(), level + 1);

        System.out.println("\n" + getTabs(level + 1)
                + "// ---------- Methods ---------");
        printMember(targetClass.getDeclaredMethods(), level + 1);

        System.out.println(getTabs(level) + "}\n");
    }

    private static void printMember(Member[] members, int level) {
        for (Member cur : members) {
            System.out.print(getTabs(level));

            if (cur instanceof Field)
                System.out.print(((Field) cur).toGenericString());
            if (cur instanceof Method)
                System.out.print(((Method) cur).toGenericString());
            if (cur instanceof Constructor)
                System.out.print(((Constructor) cur).toGenericString());

            System.out.println(";");
        }
    }

    private static String getTabs(int level) {
        String s = "";
        for (int i = 0; i < level; ++i)
            s += "    ";
        return s;
    }

    public String toString() {
        printClass(Integer.class, 0);
        return "Hello, world!";
    }
}
