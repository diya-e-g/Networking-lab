#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define INF 9999

typedef struct {
    int distance[MAX_NODES];
    int next_hop[MAX_NODES];
} RoutingTable;

RoutingTable rt[MAX_NODES];

void initializeRoutingTable(int nodes, int cost[MAX_NODES][MAX_NODES]) {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            rt[i].distance[j] = cost[i][j];
            rt[i].next_hop[j] = (cost[i][j] != INF && i != j) ? j : -1;
        }
    }
}

void updateRoutingTables(int nodes) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < nodes; i++) {  
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (rt[i].distance[k] > rt[i].distance[j] + rt[j].distance[k]) {
                        rt[i].distance[k] = rt[i].distance[j] + rt[j].distance[k];
                        rt[i].next_hop[k] = j;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

void displayRoutingTables(int nodes) {
    for (int i = 0; i < nodes; i++) {
        printf("\nRouting Table for Node %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < nodes; j++) {
            if (rt[i].distance[j] == INF)
                printf("%d\t\t-\t\tINF\n", j);
            else
                printf("%d\t\t%d\t\t%d\n", j, rt[i].next_hop[j], rt[i].distance[j]);
        }
    }
}

int main() {
    int nodes;
    int cost[MAX_NODES][MAX_NODES];

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the cost matrix (Enter %d for no direct link):\n", INF);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);
            if (i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    initializeRoutingTable(nodes, cost);
    updateRoutingTables(nodes);
    displayRoutingTables(nodes);

    return 0;
}
