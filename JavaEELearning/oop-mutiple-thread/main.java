public class main {
    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            new NumberedThread(i).start();
        }
    }
}

class NumberedThread extends Thread {
    private int id;

    NumberedThread(int i) {
        id = i;
    }

    public long getMyId() {
        return id;
    }

    public void run() {
        System.out.println("Thread ID: " + getMyId());
    }
}