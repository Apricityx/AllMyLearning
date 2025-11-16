package learning.object;

import java.util.function.Function;

public class TrianglePlus extends Shape {
    /// Please do not use the default constructor
    TrianglePlus() {
        throw new IllegalArgumentException("Please do not use the default constructor");
    }

    public TrianglePlus(double a, double b, double c,TestFunctionalInterface fun) {
        // 使用海伦-秦九韶公式计算三角形面积
        fun.test();
        this.area = Math.sqrt((a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c) / 16);
        this.perimeter = a + b + c;
    }

    @Override
    public double getArea() {
        return this.area;
    }

    @Override
    double getPerimeter() {
        return this.perimeter;
    }
}
