package top.apricityx.microService.controller;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import top.apricityx.microService.dto.ApiResponse;
import top.apricityx.microService.dto.LoginRequest;
import top.apricityx.microService.dto.LoginResponse;
import top.apricityx.microService.dto.RegisterRequest;
import top.apricityx.microService.model.User;
import top.apricityx.microService.rateLimit.LoginRateLimiter;
import top.apricityx.microService.util.JwtUtil;
import top.apricityx.microService.service.UserService;

@RestController
public class AuthController {

    private final UserService userService;
    private final JwtUtil jwtUtil;
    private final LoginRateLimiter loginRateLimiter;

    public AuthController(UserService userService,
                          JwtUtil jwtUtil,
                          LoginRateLimiter loginRateLimiter
    ) {
        this.userService = userService;
        this.jwtUtil = jwtUtil;
        this.loginRateLimiter = loginRateLimiter;
    }

    /**
     * POST /register
     * 用户注册
     */
    @PostMapping("/register")
    public ResponseEntity<ApiResponse> register(@Valid @RequestBody RegisterRequest request) {
        userService.register(request);
        ApiResponse response = new ApiResponse(true, "注册成功");
        return ResponseEntity.status(HttpStatus.CREATED).body(response);
    }

    /**
     * POST /login
     * 用户登录，返回 JWT Token
     */
    @PostMapping("/login")
    public ResponseEntity<LoginResponse> login(HttpServletRequest httpRequest, @Valid @RequestBody LoginRequest request) {
// 1. 取客户端 IP（最简单方式）
        String ip = httpRequest.getRemoteAddr();
        // 如果你有反向代理，可以优先取 X-Forwarded-For：
        // String ip = Optional.ofNullable(httpRequest.getHeader("X-Forwarded-For"))
        //         .map(s -> s.split(",")[0].trim())
        //         .orElse(httpRequest.getRemoteAddr());

        // 2. 限流判断：每个 IP 每分钟最多 5 次
        boolean allowed = loginRateLimiter.tryAcquire(ip);
        if (!allowed) {
            // 超过限制，返回 429 Too Many Requests
            LoginResponse tooMany = new LoginResponse(
                    false,
                    null,
                    null,
                    "该 IP 登录请求过于频繁，请稍后再试"
            );
            return ResponseEntity.status(HttpStatus.TOO_MANY_REQUESTS).body(tooMany);
        }
        User user = userService.login(request);

        String token = jwtUtil.generateToken(String.valueOf(user.getId()), user.getRole());
        String expireAt = (String) jwtUtil.parseToken(token).get("expiration_str");

        LoginResponse response = new LoginResponse(
                true,
                token,
                expireAt,
                "登录成功"
        );
        return ResponseEntity.ok(response);
    }
}