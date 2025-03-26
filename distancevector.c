#include <stdio.h>
#define INFINITY 9999
#define MAX 10

int cost[MAX][MAX],distance[MAX][MAX],nexthop[MAX][MAX],nodes;

void initialise()
{
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            distance[i][j]=cost[i][j];
            nexthop[i][j]=j;
        }
    }
}

void update()
{
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                for(int k=0;k<nodes;k++)
                {
                    if(distance[i][k]!=INFINITY && distance[k][j]!=INFINITY && distance[i][j]>distance[i][k]+distance[k][j])
                    {
                        distance[i][j]=distance[i][k]+distance[k][j];
                        nexthop[i][j]=nexthop[i][k];
                        updated=1;
                    }
                }
            }
        }
        
    }while(updated);
    
}

void display()
{
    for(int i=0;i<nodes;i++)
    {
        printf("Router %d's routing table:\n",i+1);
        printf("Destination\tCost\tNexthop\n");
        for(int j=0;j<nodes;j++)
        {
            printf("%d\t%d\t%d\n",j+1,distance[i][j],nexthop[i][j]+1);
        }
        
    }
}

int main()
{
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter the cost matrix: ");
    for(int i=0;i<nodes;i++)
    {
        for(int j=0;j<nodes;j++)
        {
            scanf("%d",&cost[i][j]);
            if(i==j)
            {
                cost[i][j]=0;
            }
            else if(cost[i][j]==0)
            {
                cost[i][j]=INFINITY;
            }
                
        }
    }
    initialise();
    update();
    display();
    return 0;
}
