#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PACKET_COUNT 10

void main(){
    srand(time(NULL));
    int packets[PACKET_COUNT], i = 0, rate, bucketSize, remainingSize = 0, timeToTransmit, clk, op;
    
    for(i = 0; i < PACKET_COUNT; i++){
        packets[i] = (rand()%6+1)*10;
    }

    printf("Enter output rate: ");
    scanf("%d", &rate);
    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);
    i = 0;
    
    while(i < PACKET_COUNT || remainingSize > 0){
        if(i < PACKET_COUNT){
            if(packets[i] + remainingSize > bucketSize){
                printf("Packet %d dropped (size %d)\n", i , packets[i]);
            } else {
                remainingSize += packets[i];
                printf("Packet %d of size %d added to the bucket(remaining size %d)\n", i, packets[i], bucketSize-remainingSize);
            }
            i++;
        }
        timeToTransmit = (rand()%4+1)*10;
        printf("Time to transmit: %d\n", timeToTransmit);
        for(clk = 10; clk <= timeToTransmit; clk+=10){
            sleep(1);
            if(remainingSize > 0){
                if(remainingSize <= rate){
                    op = remainingSize;
                    remainingSize = 0;
                } else {
                    op = rate;
                    remainingSize -= rate;
                }
                printf("Packet transmitted: %d, remaining size %d\n", op, bucketSize - remainingSize);
            } else {
                printf("Time left: %d\n", timeToTransmit - clk);
                printf("Bucket empy\n");
            }
        }
    }
}