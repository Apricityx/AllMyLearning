package top.apricityx.microService.interceptor;

import io.jsonwebtoken.Claims;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;
import top.apricityx.microService.util.JwtUtil;

@Component
public class AuthInterceptor implements HandlerInterceptor {

    @Autowired
    private JwtUtil jwtUtil;

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        // 1. 从 HTTP 头中获取 Token
        // 前端通常发送格式：Authorization: Bearer <token_string>
        String header = request.getHeader("Authorization");

        // 2. 判断 Token 是否存在且格式正确
        if (header != null && header.startsWith("Bearer ")) {
            String token = header.substring(7); // 去掉 "Bearer " 前缀

            // 3. 调用工具类解析 Token
            Claims claims = jwtUtil.parseToken(token);

            // 4. 如果解析成功（没过期、签名对），则放行
            if (claims != null) {
                return true; // 【放行】：请求继续传给 Controller
            }
        }

        // 5. 验证失败，设置 401 状态码，并拦截
        response.setStatus(401);
        response.setContentType("text/plain;charset=UTF-8");
        response.getWriter().write("Unauthorized: 请先登录获取有效Token");
        return false; // 【拦截】：请求到此结束，不会进入 Controller
    }
}