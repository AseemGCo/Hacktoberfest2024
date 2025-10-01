class ExpiringCache<K,V> {
    private final ConcurrentHashMap<K, CacheEntry<V>> store = new ConcurrentHashMap<>();
    private final DelayQueue<DelayedCacheItem<K>> queue = new DelayQueue<>();

    public void put(K key, V value, long ttlMillis) {
        long expireAt = System.currentTimeMillis() + ttlMillis;
        store.put(key, new CacheEntry<>(value, expireAt));
        queue.put(new DelayedCacheItem<>(key, expireAt));
    }

    public V get(K key) {
        CacheEntry<V> entry = store.get(key);
        if (entry == null || entry.isExpired()) {
            store.remove(key);
            return null;
        }
        return entry.value;
    }

    // cleaner thread
    private void startCleaner() {
        Thread t = new Thread(() -> {
            while (true) {
                try {
                    DelayedCacheItem<K> expired = queue.take();
                    store.remove(expired.getKey(), store.get(expired.getKey()));
                } catch (InterruptedException ignored) {}
            }
        });
        t.setDaemon(true);
        t.start();
    }
}
