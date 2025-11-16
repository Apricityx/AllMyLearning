package top.apricityx.servletlearning;

import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
@MultipartConfig // 允许解析 multipart/form-data
@WebServlet(name = "submit", value = "/submit") // 访问/get-time时调用
public class FormSubmit extends HttpServlet {
    private String message;

    public void init() {

    }

    /// 对于IP/get-time的GET请求，返回当前时间
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setHeader("Access-Control-Allow-Origin", "http://localhost:63342");
        response.setHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        response.setHeader("Access-Control-Allow-Headers", "Content-Type");
        // 打印请求信息

        String name = request.getParameter("name");
        String age = request.getParameter("age");
        response.setContentType("text/json");
        response.setCharacterEncoding("utf-8");
        // 设置响应类型和编码
        response.setContentType("application/json");
        response.setCharacterEncoding("utf-8");

        // 发送响应
        PrintWriter out = response.getWriter();
        out.print("{\"name\": \"" + name + "\", \"age\": " + age + "}");
        out.flush();
    }

    public void destroy() {
    }

    public String getMessage() {
        return message;
    }
}