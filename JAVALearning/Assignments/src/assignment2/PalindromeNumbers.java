package assignment2;

public class PalindromeNumbers {
    // 检查一个数是否为回文数的方法
    public static boolean isPalindrome(int number) {
        //todo
        final int numberReversed = reverse(number);
        return number == numberReversed;
    }
    // 反转数字
    public static int reverse(int number) {
        //todo
        int reversed = 0;
        while (number != 0) {
            reversed = reversed * 10 + number % 10;
            number /= 10;
        }
        return reversed;
    }
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.printf("从1到%-3d的回文数如下:\n", n);
        for (int i = 1; i < n; i++) {
            if (isPalindrome(i)) {
                System.out.print(i + " ");
            }
        }
    }
}