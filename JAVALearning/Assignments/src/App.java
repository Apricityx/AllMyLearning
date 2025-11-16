import assignment2.SimpleCalculator;
import assignment2.PalindromeNumbers;
import utils.Logger;

public class App {
    public static void main(String[] args) {
        Logger.log(SimpleCalculator.calculate(1, 2, "+"));
        Logger.log(PalindromeNumbers.isPalindrome(12321));
        Logger.log(PalindromeNumbers.isPalindrome(121233321));
    }
}