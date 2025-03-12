package com.wl1244hotmai.learning.event_bus;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Retention(RetentionPolicy.RUNTIME) // 在运行时保留注解
@Target(ElementType.METHOD) // 用于方法
public @interface Subscribe {
    int priority() default 0; // 优先级（值越大优先级越高）
    boolean async() default false; // 是否异步执行
}
