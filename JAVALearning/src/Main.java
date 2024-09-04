import java.util.Arrays;

public class Main {
    public static void main(String[] args) { // 主函数
        Logger logger = new Logger();
        logger.log("Hello world");
        if (args == null || args.length == 0) {
            logger.warn("No arguments provided!");
            return;
        } else {
            logger.warn("Arguments: " + Arrays.toString(args));
        }
        logger.warn("Java compilation completed!");
        System.out.print("Hello and welcome!");
        Puppy cat = new Puppy("Tom", 3);
        logger.log("Created " + cat.getName());
    }
}
// 在一个JAVA程序中只能有一个public类，并且类名必须与文件名相同。
