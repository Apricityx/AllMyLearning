package top.apricityx.microService.config;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import top.apricityx.microService.interceptor.AuthInterceptor;

@Configuration
public class WebConfig implements WebMvcConfigurer {

    @Autowired
    private AuthInterceptor authInterceptor;

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        // 3. 注册拦截器并定义规则
        registry.addInterceptor(authInterceptor)
                .addPathPatterns("/devices/**")
                .excludePathPatterns("/login", "/register");
    }
}