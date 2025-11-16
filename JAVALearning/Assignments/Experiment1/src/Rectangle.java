package tech.mctown.javafx;

public class Rectangle {
    private double centerX;
    private double centerY;
    final private double width;
    final private double height;
    private double angle;

    /**
     * 矩形类构造方法
     * 该类需要传入的参数为中心点x坐标，中心点y坐标，宽度，高度
     *
     * @param centerX 中心点x坐标
     * @param centerY 中心点y坐标
     * @param width   宽度
     * @param height  高度
     */
    public Rectangle(double centerX, double centerY, double width, double height) {
        this.centerX = centerX;
        this.centerY = centerY;
        this.width = width;
        this.height = height;
    }

    /**
     * @param angle 旋转角度，单位为度
     */
    public void rotate(double angle) {
        this.angle += angle;
    }

    public void moveTo(double x, double y) {
        this.centerX = x;
        this.centerY = y;
    }

    public void move(double dx, double dy) {
        this.centerX += dx;
        this.centerY += dy;
    }

    public double getCenterX() {
        return centerX;
    }

    public double getCenterY() {
        return centerY;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

    public double getAngle() {
        return angle;
    }

    final private static int VERTEX0 = 0;
    final private static int VERTEX1 = 1;
    final private static int VERTEX2 = 2;
    final private static int VERTEX3 = 3;
}
