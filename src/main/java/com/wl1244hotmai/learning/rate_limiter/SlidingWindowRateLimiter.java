package com.wl1244hotmai.learning;

import java.time.Instant;
import java.util.concurrent.*;

import static java.time.temporal.ChronoUnit.MILLIS;

public class SlidingWindowRateLimiter implements RateLimiter {
    private final Long window;
    private final Long limit; // milliseconds

    ScheduledExecutorService scheduledExecutorService = Executors.newScheduledThreadPool(1);
    private final ConcurrentLinkedDeque<Instant> deque =
            new ConcurrentLinkedDeque();

    /**
     *
     * @param window milli seconds
     * @param limit long
     */
    public SlidingWindowRateLimiter(Long window, Long limit) {
        this.window = window;
        this.limit = limit;

        scheduledExecutorService.scheduleAtFixedRate(() -> {
            Instant now = Instant.now();
            while (!deque.isEmpty() && (deque.peek().until(now, MILLIS) > window)) {
                deque.pop();
            }
        }, 0, 5000L, TimeUnit.MILLISECONDS);
    }

    public boolean acquire() {
        if(deque.size() >= limit) {
            return false;
        } else {
            deque.addLast(Instant.now());
            return true;
        }
    }
}
