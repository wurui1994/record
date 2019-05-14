import java.lang.reflect.*;
import java.util.regex.*;

public class listMethod {
    private static Pattern p = Pattern.compile("\\w+\\.");
    public static void main(String[] args) throws ClassNotFoundException {
        int lines = 0;
        Class<?> c = Class.forName("java.lang.Byte");
        Method[] methods = c.getMethods();
        Constructor[] ctors = c.getConstructors();
        for (Method method : methods)
            System.out.println(p.matcher(method.toString()).replaceAll(""));
        for (Constructor ctor : ctors)
            System.out.println(p.matcher(ctor.toString()).replaceAll(""));
        lines = methods.length + ctors.length;
        System.out.println(lines);
    }
}