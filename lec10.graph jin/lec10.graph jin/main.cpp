#include "SrchAMGraph.h"
#include "WGraphMST.h"

int main()
{
    /***********************
        기존 DFS 실습
    ************************/

    SrchAMGraph g;

    for (int i = 0; i < 8; i++)
        g.insertVertex('A' + i);

    g.insertEdge(0, 1);
    g.insertEdge(0, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(3, 5);
    g.insertEdge(4, 6);
    g.insertEdge(4, 7);
    g.insertEdge(6, 7);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n\n");


    /***********************
        MST 실습
    ************************/

    WGraphMST wg;

    wg.load("graph.txt");

    printf("가중치 그래프\n");
    wg.display();

    printf("\nMST By Kruskal's Algorithm\n");
    wg.Kruskal();

    return 0;
}