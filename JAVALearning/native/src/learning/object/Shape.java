package learning.object;

abstract public class Shape {
    protected double area;
    protected double perimeter; // 周长

    Shape() {
    }

    abstract double getArea();

    abstract double getPerimeter();

}
