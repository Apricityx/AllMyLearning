package top.apricityx.microService.controller;

import jakarta.servlet.http.HttpServletRequest;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import top.apricityx.microService.rateLimit.DeviceAccessRateLimiter;
import top.apricityx.microService.util.JwtUtil;

import java.util.HashMap;
import java.util.Map;

@RestController
public class DeviceController {
    private final JwtUtil jwtUtil;
    private final DeviceAccessRateLimiter deviceAccessRateLimiter;
    public DeviceController(JwtUtil jwtUtil,
                            DeviceAccessRateLimiter deviceAccessRateLimiter) {
        this.jwtUtil = jwtUtil;
        this.deviceAccessRateLimiter = deviceAccessRateLimiter;
    }

    @GetMapping("/devices/{id}")
    public ResponseEntity<?> getDevice(@PathVariable String id, HttpServletRequest request) {
        String authHeader = request.getHeader("Authorization");
        if (authHeader == null || !authHeader.startsWith("Bearer ")) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED)
                    .body(Map.of(
                            "success", false,
                            "message", "缺少或非法的 Authorization 头"
                    ));
        }
        String token = authHeader.substring(7); // 去掉 "Bearer "

        // 校验并解析 token，拿到 userId
        Long userId;
        try {
            userId = jwtUtil.getUserIdFromToken(token);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED)
                    .body(Map.of(
                            "success", false,
                            "message", "Token 无效或已过期"
                    ));
        }

        // 每个用户每小时最多 3 次
        if (!deviceAccessRateLimiter.tryAcquire(userId)) {
            return ResponseEntity.status(HttpStatus.TOO_MANY_REQUESTS)
                    .body(Map.of(
                            "success", false,
                            "message", "获取设备信息过于频繁，请稍后再试"
                    ));
        }

        Map<String, Object> deviceInfo = new HashMap<>();
        deviceInfo.put("deviceId", id);
        deviceInfo.put("deviceName", "高压压缩机 #" + id);
        deviceInfo.put("status", "RUNNING");
        deviceInfo.put("location", "二号厂房");
        deviceInfo.put("lastUpdate", "2023-12-12 14:30:00");

        return ResponseEntity.ok(deviceInfo);
    }
}
