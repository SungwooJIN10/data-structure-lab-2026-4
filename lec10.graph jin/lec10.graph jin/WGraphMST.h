#pragma once
#include "AdjMatGraph.h"
#include "MinHeap.h"
#include "VertexSets.h"

class WGraphMST : public WGraph {
public:
    void Kruskal() {
        MinHeap heap;

        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j);
            }
        }

        VertexSets set(size);
        int edgeAccepted = 0;

        while (edgeAccepted < size - 1) {
            HeapNode e = heap.remove();

            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());

            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()),
                    getVertex(e.getV2()),
                    e.getKey());

                set.unionSets(uset, vset);
                edgeAccepted++;
            }
        }
    }
};