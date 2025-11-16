import learning.utils.MyLogger;

public class RunnableDemo implements Runnable {
    private final String threadName;
    private Thread t;

    RunnableDemo(String name) {
        MyLogger.debug("Creating " + name);
        threadName = name;
    }

    @Override
    public void run() {
        synchronized (this) { // 先进入的线程先执行
            try {
                // 0-1秒随机时间
                int randomTime = (int) (Math.random() * 1000);
                Thread.sleep(randomTime);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            MyLogger.debug("Exiting " + threadName);
        }
    }

    public void start() {
        System.out.println("Starting " + threadName);
        if (t == null) {
            t = new Thread(this, threadName);
            t.start();
        }
    }
}
