package top.apricityx.microService.util;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import org.springframework.stereotype.Component;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * JWT 工具类
 * 负责生成和解析 Token
 */
@Component
public class JwtUtil {

    // 密钥（在实际生产中应放在 application.properties 或环境变量中）
    private static final String SECRET_KEY = "Industrial_Monitor_Secret_Key_For_Safety";

    // 过期时间：1小时 (毫秒)
    private static final long EXPIRATION_TIME = 3600_000;

    /**
     * 生成 JWT Token
     * 要求：存储用户ID、角色和过期具体时间（按照yyyy-MM-dd HH:mm:ss）
     */
    public String generateToken(String userId, String role) {
        Map<String, Object> claims = new HashMap<>();
        claims.put("id", userId);
        claims.put("role", role);

        // 计算过期时间对象
        Date expDate = new Date(System.currentTimeMillis() + EXPIRATION_TIME);

        // 格式化过期时间字符串并存入 Claims
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String formattedExp = sdf.format(expDate);
        claims.put("expiration_str", formattedExp);

        // 构建 Token
        return Jwts.builder()
                .setClaims(claims)
                .setSubject(userId)
                .setIssuedAt(new Date())
                .setExpiration(expDate)
                .signWith(SignatureAlgorithm.HS256, SECRET_KEY)
                .compact();
    }

    /**
     * 验证并解析 Token
     * @param token JWT 字符串
     * @return 解析后的 Claims 对象，如果验证失败或过期则返回 null
     */
    public Claims parseToken(String token) {
        try {
            return Jwts.parser()
                    .setSigningKey(SECRET_KEY)
                    .parseClaimsJws(token)
                    .getBody();
        } catch (Exception e) {
            // 解析失败（签名错误、Token过期、格式错误等）都会抛出异常
            // 这里返回 null 表示验证不通过
            return null;
        }
    }
    public Long getUserIdFromToken(String token) {
        Claims claims = parseToken(token);
        return Long.valueOf(claims.getSubject());
    }
}