package com.wl1244hotmai.learning;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.stereotype.Component;

@Component
@Aspect
public class RateLimiterAspect {
    private BucketRateLimiter rateLimiter = new BucketRateLimiter(100, 100);

    @Around("@annotation(acquire)")
    public void advice(ProceedingJoinPoint joinPoint, Acquire acquire) {
        rateLimiter.acquire();
        joinPoint.proceed();
    }

}
