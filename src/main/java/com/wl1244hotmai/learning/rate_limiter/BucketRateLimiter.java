package com.wl1244hotmai.learning;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

public class BucketRateLimiter implements RateLimiter {

    private final AtomicInteger counter;

    private final ScheduledExecutorService scheduledExecutorService = Executors.newScheduledThreadPool(1);

    public void shutdown() {
        scheduledExecutorService.shutdownNow();
    }

    public BucketRateLimiter(int refillRate, int limit) {
        this.counter = new AtomicInteger(limit);

        scheduledExecutorService.scheduleAtFixedRate(() -> {
            System.out.println("bucket " + counter.get());
            if (counter.get() < limit) {
                counter.incrementAndGet();
            }
        }, 1, refillRate, TimeUnit.MILLISECONDS);
    }

    @Override
    public boolean acquire() {
        while (true) {
            int current = counter.get();
            if (current <= 0) {
                return false;
            }
            if (counter.compareAndSet(current, current - 1)) {
                return true;
            }
        }
    }
}
