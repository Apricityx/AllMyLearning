package top.apricityx.servletlearning;

import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

import static java.lang.Thread.sleep;

@WebServlet(name = "echo", value = "/echo") // 访问/get-time时调用
public class Echo extends HttpServlet {
    private String message;

    public void init() {

    }

    /// 对于IP/get-time的GET请求，返回当前时间
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        message = request.getParameter("value");
        response.setContentType("text/json");
        if (message.isEmpty()) {
            message = "未提供值";
        }
        PrintWriter out = response.getWriter();
        out.println("{\"value\": \"" + message + "\"}");
    }

    public void destroy() {
    }

    public String getMessage() {
        return message;
    }
}