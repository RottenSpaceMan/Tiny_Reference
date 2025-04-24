#include <stdio.h>

struct Node{
    int dist[20];
    int from[20];
}route[10];

void main(){
    int dm[10][10], no;
    
    printf("Enter number of nodes: ");
    scanf("%d", &no);

    printf("Enter distance matrix\n");
    for(int i = 0; i < no; i++){
        for(int j = 0; j < no; j++){
            scanf("%d",dm[i][j]);
            if(i == j){
                dm[i][j] = 0;
            }

            route[i].dist[j] = dm[i][j];
            route[i].from[j] = j;
        }
    }

    int flag;

    do{
        flag = 0;
        for(int i = 0; i < no; i++){
            for(int j = 0; j < no; j++){
                for(int k = 0; k < no; k++){
                    if(route[i].dist[j] > (route[i].dist[k] + route[k].dist[j])){
                        route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
                        route[i].from[j] = route[i].from[k]; 
                        flag = 1;
                    }
                }
            }
        }
    }while(flag);

    for(int i = 0; i < no; i++){
        printf("Router info for router: %c\n", i+65);
        printf("To router\tNext Hop\tDistance\n");
        for(int j = 0; j < no; j++){
            printf("%c\t\t%c\t\t%d\n", j+65, route[i].from[j] + 65, route[i].dist[j]);
        }
    }
    return 0;
}