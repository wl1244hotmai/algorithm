package com.wl1244hotmai.learning;

public class SnowflakeIdGenerator {

    // 起始纪元（可以设置为系统启动时间或一个固定值），如2023-01-01 00:00:00对应的时间戳（毫秒）
    private final static long EPOCH = 1672531200000L;

    // 各部分位数分配
    private final static long WORKER_ID_BITS = 5L;
    private final static long DATACENTER_ID_BITS = 5L;
    private final static long SEQUENCE_BITS = 12L;

    // 各部分最大值
    private final static long MAX_WORKER_ID = ~(-1L << WORKER_ID_BITS);           // 31
    private final static long MAX_DATACENTER_ID = ~(-1L << DATACENTER_ID_BITS);   // 31
    // 序列号最大值为 2^12 - 1 = 4095
    private final static long SEQUENCE_MASK = ~(-1L << SEQUENCE_BITS);

    // 各部分移位位数
    private final static long WORKER_ID_SHIFT = SEQUENCE_BITS;  // 12
    private final static long DATACENTER_ID_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS; // 12+5=17
    private final static long TIMESTAMP_LEFT_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS + DATACENTER_ID_BITS; // 12+5+5=22

    // 数据中心 ID 和 工作节点 ID（在分布式部署时必须保证唯一性）
    private final long workerId;
    private final long datacenterId;

    // 序列号和上次生成 ID 的时间戳
    private long sequence = 0L;
    private long lastTimestamp = -1L; // 上次生成 ID 的时间戳

    /**
     * 构造方法，指定工作节点和数据中心ID
     *
     * @param workerId 工作节点 ID，取值范围 [0, MAX_WORKER_ID]
     * @param datacenterId 数据中心 ID，取值范围 [0, MAX_DATACENTER_ID]
     */
    public SnowflakeIdGenerator(long workerId, long datacenterId) {
        if (workerId < 0 || workerId > MAX_WORKER_ID) {
            throw new IllegalArgumentException(String.format("workerId must be between 0 and %d", MAX_WORKER_ID));
        }
        if (datacenterId < 0 || datacenterId > MAX_DATACENTER_ID) {
            throw new IllegalArgumentException(String.format("datacenterId must be between 0 and %d", MAX_DATACENTER_ID));
        }
        this.workerId = workerId;
        this.datacenterId = datacenterId;
    }

    /**
     * 获取下一个唯一 ID，该方法需保证多线程环境下并发安全
     * 使用 synchronized 保证原子性
     *
     * @return 全局唯一 ID
     */
    public synchronized long nextId() {
        long timestamp = currentTime();

        if (timestamp < lastTimestamp) {
            throw new RuntimeException(
                    String.format("Clock moved backwards. Refusing to generate id for %d milliseconds", lastTimestamp - timestamp));
        }

        if (timestamp == lastTimestamp) {
            // 在当前毫秒内，递增序列
            sequence = (sequence + 1) & SEQUENCE_MASK;
            if (sequence == 0) {
                // 当前毫秒内序列已经用完，则等待下一个毫秒
                timestamp = tilNextMillis(lastTimestamp);
            }
        } else {
            // 不在同一毫秒内，重置序列为 0
            sequence = 0L;
        }

        lastTimestamp = timestamp;
        // 将各部分数据按位拼接成一个 long 值
        return ((timestamp - EPOCH) << TIMESTAMP_LEFT_SHIFT)
                | (datacenterId << DATACENTER_ID_SHIFT)
                | (workerId << WORKER_ID_SHIFT)
                | sequence;
    }

    /**
     * 等待到下一个毫秒
     *
     * @param lastTimestamp 上次记录的时间戳
     * @return 当前时间戳（必然大于 lastTimestamp）
     */
    private long tilNextMillis(long lastTimestamp) {
        long timestamp = currentTime();
        while (timestamp <= lastTimestamp) {
            timestamp = currentTime();
        }
        return timestamp;
    }

    /**
     * 返回当前时间戳（毫秒）
     *
     * @return 当前时间（毫秒）
     */
    private long currentTime() {
        return System.currentTimeMillis();
    }

    // 测试方法（可选）
    public static void main(String[] args) {
        final SnowflakeIdGenerator idGenerator = new SnowflakeIdGenerator(1, 1);

        // 模拟高并发环境生成 ID
        int threadCount = 10;
        int idsPerThread = 1000;

        Runnable task = () -> {
            for (int i = 0; i < idsPerThread; i++) {
                long id = idGenerator.nextId();
                System.out.println(Thread.currentThread().getName() + " generated id: " + id);
            }
        };

        Thread[] threads = new Thread[threadCount];

        for (int i = 0; i < threadCount; i++) {
            threads[i] = new Thread(task, "Thread-" + i);
            threads[i].start();
        }

        // 等待所有线程完成
        for (int i = 0; i < threadCount; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
