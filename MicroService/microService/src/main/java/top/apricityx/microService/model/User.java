package top.apricityx.microService.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class User {

    private Long id;

    private String username;

    // 暂时明文存储，后面可以改成加密（作业要求没强制的话可以先简单）
    private String password;

    private String email;

    // 角色，后面生成 JWT 要用（比如 "USER" / "ADMIN"）
    private String role;
}
