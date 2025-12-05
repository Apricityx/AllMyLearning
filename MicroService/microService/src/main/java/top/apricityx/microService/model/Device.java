package top.apricityx.microService.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class Device {

    private Long id;

    private String name;

    private String description;

    // 当前状态，比如 "ONLINE", "OFFLINE", "FAULT"
    private String status;

    // 最后更新时间
    private LocalDateTime lastUpdatedTime;
}
