import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.Charset;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class SocketTest {
    private final ExecutorService es = Executors.newFixedThreadPool(3);
    private final CountDownLatch latch = new CountDownLatch(1);

    public void startServer() {
        // 提交服务端运行任务
        es.submit(() -> {
            // 服务器任务
            try {
                ServerSocket server = new ServerSocket(4567);
//                System.out.println("服务器启动成功，端口为：" + server.getLocalPort());
                latch.countDown(); // 倒计数器减1
                Socket s = server.accept(); // 阻塞，监听到客户端请求后返回Socket对象
//                System.out.println("接收到请求");
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(s.getInputStream(), Charset.forName("utf-8")));) {
                    System.out.println("接收数据:" + reader.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
    }

    public void startClient() {
        try {
            latch.await();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("start client");
        es.submit(() -> {
//            System.out.println("客户端启动成功");
            try (Socket skt = new Socket("localhost", 4567); // 创建Socket对象，并尝试连接服务器端
                 PrintWriter pw = new PrintWriter(skt.getOutputStream());) {
//                System.out.println("连接服务器成功");
                pw.println("你好"); // 发送文本数据
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("客户端任务结束");
        }); // 提交客户端运行任务
    }
}
