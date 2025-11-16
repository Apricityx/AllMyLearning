package learning.utils;

public class MyLogger {
    static public <T> void log(T message) {
        System.out.println(message);
    }

    static public <T> void warn(T message) {
        //输出黄色文字
        System.out.println("\033[33m" + message + "\033[0m");
    }

    static public <T> void error(T message) {
        //输出红色文字
        System.out.println("\033[31m" + message + "\033[0m");
    }

    static public <T> void debug(T message) {
        //输出蓝色文字
        System.out.println("\033[34m" + message + "\033[0m");
    }
}
