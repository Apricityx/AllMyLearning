package top.apricityx.microService.service;

import org.springframework.stereotype.Service;
import top.apricityx.microService.dto.RegisterRequest;

@Service
public class DeviceService
{
    /**
     * 查询设备
     */
    public void register(RegisterRequest request) {
        System.out.println("用户名字: " + request.getUsername());
        System.out.println("用户密码: " + request.getPassword());
        System.out.println("用户邮箱: " + request.getEmail());
        // 密码至少8个字符，包含字母和数字
        if (request.getPassword().length() < 8 ||
                !request.getPassword().matches(".*[a-zA-Z].*") ||
                !request.getPassword().matches(".*\\d.*")) {
            throw new IllegalArgumentException("密码必须至少8个字符，且包含字母和数字");
        }
    }
}
