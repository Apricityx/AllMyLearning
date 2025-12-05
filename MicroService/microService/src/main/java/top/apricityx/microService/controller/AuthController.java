package top.apricityx.microService.controller;

import top.apricityx.microService.dto.ApiResponse;
import top.apricityx.microService.dto.RegisterRequest;
import top.apricityx.microService.model.User;
import top.apricityx.microService.service.UserService;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping
public class AuthController {

    private final UserService userService;

    public AuthController(UserService userService) {
        this.userService = userService;
    }

    /**
     * POST /register
     * 用户注册：接收用户名、密码、邮箱
     */
    @PostMapping("/register")
    public ResponseEntity<ApiResponse> register(@RequestBody @Valid RegisterRequest request) {
        User user = userService.register(request);
        return ResponseEntity
                .status(HttpStatus.CREATED)
                .body(new ApiResponse(true, "注册成功，用户ID：" + user.getId()));
    }
}
