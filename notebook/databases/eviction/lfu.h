#pragma once
#include "eviction_cache.h"

class LFUCache : public EvictionCache {
private:
    int capacity;

    Page evict() {
        return {};
    }

public:
    LFUCache(int cap) : capacity(cap) {}

    string name() const override { return "LFU"; }

    Page get(int key) override {
        return {};
    }

    Page put(int key, int value) override {
        return {};
    }
};
