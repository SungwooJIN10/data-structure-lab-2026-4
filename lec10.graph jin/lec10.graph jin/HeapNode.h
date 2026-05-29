#pragma once

class HeapNode {
    int key;
    int v1;
    int v2;

public:
    HeapNode(int k = 0, int u = 0, int v = 0)
        : key(k), v1(u), v2(v) {
    }

    void setKey(int k) {
        key = k;
    }

    int getKey() {
        return key;
    }

    int getV1() {
        return v1;
    }

    int getV2() {
        return v2;
    }
};