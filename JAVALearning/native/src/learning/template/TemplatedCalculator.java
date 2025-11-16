package learning.template;

public class TemplatedCalculator {
    public static <T extends Number> T add(T a, T b) {
        return (T) Double.valueOf(a.doubleValue() + b.doubleValue());
    }
}