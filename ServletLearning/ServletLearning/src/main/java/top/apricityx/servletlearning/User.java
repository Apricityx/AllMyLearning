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

@WebServlet(name = "user", value = "/user")
public class User extends HttpServlet {
    private String message;

    public void init() {
        message = "12:00";
    }

    /// 对于IP/get-time的GET请求，返回当前时间
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {

    }

    public void destroy() {
    }
}