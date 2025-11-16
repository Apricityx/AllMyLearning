package top.apricityx.servletlearning;

import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import static java.lang.Thread.sleep;

@WebServlet(name = "get-time", value = "/get-time") // 访问/get-time时调用
public class GetTime extends HttpServlet {
    private String message;

    public void init() {
        message = "12:00";
    }

    /// 对于IP/get-time的GET请求，返回当前时间
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        /// 获取当前时间
        SimpleDateFormat sdf = new SimpleDateFormat();
        sdf.applyPattern("yyyy-MM-dd HH:mm:ss a");
        Date date = new Date();
        message = sdf.format(date);
        response.setContentType("text/json");
        PrintWriter out = response.getWriter(); /// 获取输出流
        out.println("{\"time\": \"" + message + "\"}"); /// 输出当前时间
    }

    public void destroy() {
    }
}