package com.wl1244hotmai.learning;

import org.junit.jupiter.api.Test;

public class BucketRateLimiterTest {
    @Test
    public void testSlidingWindowRateLimiterTest() throws InterruptedException {
        BucketRateLimiter rateLimiter = new BucketRateLimiter(
                1000,
                10
        );

        for (int i = 0; i < 12; i++) {
            System.out.println(rateLimiter.acquire());
        }
        System.out.println();

        Thread.sleep(6000L);

        for (int i = 0; i < 5; i++) {
            System.out.println(rateLimiter.acquire());
        }
        System.out.println();

        for (int i = 0; i < 12; i++) {
            System.out.println(rateLimiter.acquire());
            Thread.sleep(400L);
        }
    }
}
