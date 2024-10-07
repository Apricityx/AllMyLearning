package experiment1;

public class Circle {
    public static void printMetadata() {
        System.out.println("Circle class loaded! This class is used to represent a circle.");
    }

    // 默认构造函数

    /**
     * Circle类的构造函数
     * 该构造函数没有参数的时候将会将半径初始化为1.0
     */
    public Circle() {
        this.radius = 1.0;
        System.out.println("Warning: Radius is not given! Circle created with default radius: " + this.radius);
    }

    /**
     * Circle类的构造函数
     * 该构造函数没有参数的时候将会将半径初始化为1.0
     *
     * @param radius 半径
     */
    public Circle(double radius) {
        this.radius = radius;
    }

    // 半径
    private double radius;

    // 面积计算
    public double getArea() {
        return Math.PI * radius * radius;
    }

    // 周长计算
    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    // 获取半径
    public double getRadius() {
        return radius;
    }

    // 初始化半径
    public void setRadius(double radiusBuffer) {
        this.radius = radiusBuffer;
    }
}
