package top.apricityx.microService.rateLimit;

import org.springframework.stereotype.Component;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import com.google.common.cache.Cache;
import com.google.common.cache.CacheBuilder;
@Component
public class LoginRateLimiter {

    // key: ip, value: 这一分钟内的计数
    private final Cache<String, AtomicInteger> ipCounter = CacheBuilder.newBuilder()
            .expireAfterWrite(1, TimeUnit.MINUTES) // 1 分钟窗口
            .build();

    private static final int MAX_REQUESTS_PER_MINUTE = 5;

    /**
     * 返回 true 表示允许登录，false 表示超过次数
     */
    public boolean tryAcquire(String ip) {
        try {
            AtomicInteger counter = ipCounter.get(ip, () -> new AtomicInteger(0));
            int current = counter.incrementAndGet();
            return current <= MAX_REQUESTS_PER_MINUTE;
        } catch (ExecutionException e) {
            // 出现异常时保守一点，直接拒绝
            return false;
        }
    }
}