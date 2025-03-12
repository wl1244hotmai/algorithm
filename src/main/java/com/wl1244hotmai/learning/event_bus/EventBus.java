package com.wl1244hotmai.learning;

import com.wl1244hotmai.learning.Subscribe;

import java.lang.reflect.Method;
import java.util.*;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

public class EventBus {
    private final Map<Class<?>, List<Subscriber>> subscribers = new HashMap<>();
    private final Executor defaultExecutor;

    public EventBus() {
        this(Executors.newSingleThreadExecutor()); // 默认单线程异步执行
    }

    public EventBus(Executor executor) {
        this.defaultExecutor = executor;
    }

    // 注册订阅者
    public void register(Object listener) {
        for (Method method : listener.getClass().getDeclaredMethods()) {
            if (method.isAnnotationPresent(Subscribe.class)) {
                Subscribe annotation = method.getAnnotation(Subscribe.class);
                Class<?> eventType = method.getParameterTypes()[0]; // 获取事件类型
                subscribers.computeIfAbsent(eventType, k -> new ArrayList<>())
                        .add(new Subscriber(listener, method, annotation.priority(), annotation.async()));
            }
        }
        // 按优先级排序
        subscribers.values().forEach(subs -> subs.sort(Comparator.comparingInt(Subscriber::getPriority).reversed()));
    }

    // 取消注册
    public void unregister(Object listener) {
        subscribers.values().forEach(subs -> subs.removeIf(sub -> sub.listener == listener));
    }

    // 发布事件
    public void post(Object event) {
        Class<?> eventType = event.getClass();
        for (Class<?> key : subscribers.keySet()) {
            if (key.isAssignableFrom(eventType)) { // 父类也能接收子类事件
                List<Subscriber> eventSubscribers = subscribers.get(key);
                if (eventSubscribers != null) {
                    for (Subscriber sub : eventSubscribers) {
                        Executor executor = sub.isAsync() ? defaultExecutor : Runnable::run;
                        executor.execute(() -> sub.invoke(event)); // 异步或同步执行
                    }
                }
            }
        }
    }

    // 内部类：订阅者
    private static class Subscriber {
        private final Object listener;
        private final Method method;
        private final int priority;
        private final boolean async;

        public Subscriber(Object listener, Method method, int priority, boolean async) {
            this.listener = listener;
            this.method = method;
            this.priority = priority;
            this.async = async;
        }

        public int getPriority() {
            return priority;
        }

        public boolean isAsync() {
            return async;
        }

        public void invoke(Object event) {
            try {
                method.setAccessible(true);
                method.invoke(listener, event);
            } catch (Exception e) {
                System.err.println("Error while handling event: " + e.getMessage());
            }
        }
    }
}
