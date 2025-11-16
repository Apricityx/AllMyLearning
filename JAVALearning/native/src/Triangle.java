public class Triangle {
    private double a, b, c; // 三边

    public Triangle() {
        a = 0;
        b = 0;
        c = 0;
    }

    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public double perimeter() {
        return a + b + c;
    }

    // Getter和Setter方法
    public double getA() {
        return a;
    }

    public static void checkSides(double a, double b, double c) {
        // 当边长存在小于等于0的情况，则抛出异常，消息必须为：存在边长小于零
        // 当边长存在两边之和小于第三边的情况，则抛出异常，消息必须为：两边之和小于等于第三边
        if (a <= 0 || b <= 0 || c <= 0) {
            throw new IllegalArgumentException("存在边长小于零");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            throw new IllegalArgumentException("两边之和小于等于第三边");
        }
    }

    public static Triangle[] fromArray(double[][] a) {
        // 待完成
        Triangle[] tri = new Triangle[a.length];
        for (int i = 0; i < a.length; i++) {
            // 使用构造器来创建三角形：a[i][0],a[i][1],a[i][2]表示第i个三角形的三边
            // 使用try-catch来捕获创建三角形可能抛出的异常
            // 异常捕获之后使用System.out.println打印消息：e.getMessage()
            try {
                checkSides(a[i][0], a[i][1], a[i][2]);
                tri[i] = new Triangle(a[i][0], a[i][1], a[i][2]);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
        return tri;
    }

    public void setA(double a) {
        this.a = a;
    }

    public double getB() {
        return b;
    }

    public void setB(double b) {
        this.b = b;
    }

    public double getC() {
        return c;
    }

    public void setC(double c) {
        this.c = c;
    }
}
