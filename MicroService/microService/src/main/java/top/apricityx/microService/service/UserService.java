package top.apricityx.microService.service;

import top.apricityx.microService.dto.RegisterRequest;
import top.apricityx.microService.model.User;
import org.springframework.stereotype.Service;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

@Service
public class UserService {

    // 用 Map 模拟用户表：key = username
    private final Map<String, User> usersByUsername = new ConcurrentHashMap<>();

    // 自增 ID 模拟数据库主键
    private final AtomicLong idGenerator = new AtomicLong(1);

    public User register(RegisterRequest request) {
        String username = request.getUsername();
        String password = request.getPassword();
        String email = request.getEmail();

        // 1. 校验用户名是否已存在
        if (usersByUsername.containsKey(username)) {
            throw new IllegalArgumentException("用户名已存在");
        }

        // 2. 校验密码复杂度：至少 8 位，包含字母和数字
        validatePassword(password);

        // 3. 创建用户对象（默认角色给 USER）
        User user = User.builder()
                .id(idGenerator.getAndIncrement())
                .username(username)
                .password(password)
                .email(email)
                .role("USER")
                .build();

        // 4. 存入内存“数据库”
        usersByUsername.put(username, user);

        return user;
    }

    public User findByUsername(String username) {
        return usersByUsername.get(username);
    }

    /**
     * 简单密码复杂度验证：
     * - 长度 >= 8
     * - 至少包含一个字母
     * - 至少包含一个数字
     */
    private void validatePassword(String password) {
        if (password == null || password.length() < 8) {
            throw new IllegalArgumentException("密码长度至少 8 位，并且需包含字母和数字");
        }
        boolean hasLetter = false;
        boolean hasDigit = false;

        for (char c : password.toCharArray()) {
            if (Character.isLetter(c)) {
                hasLetter = true;
            } else if (Character.isDigit(c)) {
                hasDigit = true;
            }
            if (hasLetter && hasDigit) {
                break;
            }
        }

        if (!hasLetter || !hasDigit) {
            throw new IllegalArgumentException("密码必须同时包含字母和数字");
        }
    }
}
