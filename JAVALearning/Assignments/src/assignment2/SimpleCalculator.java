package assignment2;

public class SimpleCalculator {
    // 计算方法，根据操作符进行相应的计算
    public static double calculate(double num1, double num2, String operator) {
// 逻辑实现：运算符解析与计算过程
        return switch (operator) {
            case "+" -> num1 + num2;
            case "-" -> num1 - num2;
            case "*" -> num1 * num2;
            case "/" -> num1 / num2;
            default -> throw new IllegalArgumentException("Invalid operator: " + operator);
        };
    }
}