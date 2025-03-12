package com.wl1244hotmai.learning;

import org.junit.jupiter.api.Test;

public class SlidingWindowRateLimiterTest {
    @Test
    public void testSlidingWindowRateLimiterTest() throws InterruptedException {
        SlidingWindowRateLimiter rateLimiter = new SlidingWindowRateLimiter(
                5000L,
                10L
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
