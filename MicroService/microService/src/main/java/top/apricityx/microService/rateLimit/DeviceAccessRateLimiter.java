package top.apricityx.microService.rateLimit;

import com.google.common.cache.Cache;
import com.google.common.cache.CacheBuilder;
import org.springframework.stereotype.Component;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

@Component
public class DeviceAccessRateLimiter {

    // key: userId, value: 这一小时内访问次数
    private final Cache<Long, AtomicInteger> userCounter = CacheBuilder.newBuilder()
            .expireAfterWrite(1, TimeUnit.HOURS) // 1 小时窗口
            .build();

    private static final int MAX_REQUESTS_PER_HOUR = 3;

    public boolean tryAcquire(Long userId) {
        try {
            AtomicInteger counter = userCounter.get(userId, () -> new AtomicInteger(0));
            int current = counter.incrementAndGet();
            return current <= MAX_REQUESTS_PER_HOUR;
        } catch (ExecutionException e) {
            return false;
        }
    }
}