public class Logger {
    public void log(String message) {
        System.out.println(message);
    }

    public void warn(String message) {
        //输出黄色文字
        System.out.println("\033[33m" + message + "\033[0m");
    }

    public void error(String message) {
        //输出红色文字
        System.out.println("\033[31m" + message + "\033[0m");
    }
}
