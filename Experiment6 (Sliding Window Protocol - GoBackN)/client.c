#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#define PORT 8080
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 12

void main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0), base = 0, next_pack_num = 0, ack;
    srand(time(NULL));
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    while(base < TOTAL_PACKETS){
        while(next_pack_num < base + WINDOW_SIZE && next_pack_num < TOTAL_PACKETS){
            printf("Sending packet %d\n", next_pack_num);
            if(rand()%5 != 0){
                sendto(sock, &next_pack_num, sizeof(next_pack_num), 0, (struct sockaddr *)&serv_addr, addr_len);
            }else{
                printf("Simulated packet loss for %d\n", next_pack_num);
            }
            next_pack_num++;
        }

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(sock, &fds);
        int retval = select(sock + 1, &fds, NULL, NULL, &tv);
        if(retval == 0){
            printf("Timeout! Sending from %d\n", base);
            next_pack_num = base;
        } else {
            recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&serv_addr, &addr_len);
            printf("ACK received for packet %d\n", ack);
            if(ack >= base){
                base = ack + 1;
            }

        }
    }
    close(sock);
}