package top.apricityx.microService.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class LoginResponse {

    private boolean success;
    private String token;
    private String expireAt;  // yyyy-MM-dd HH:mm:ss
    private String message;
}