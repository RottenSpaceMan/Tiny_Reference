#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORT 8080

void main(){
    srand(time(NULL));
    int serv_fd, cli_fd;
    struct sockaddr_in cli_addr, serv_addr;
    socklen_t addr_len = sizeof(cli_addr);
    int frame = 0;

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(serv_fd, 3);

    cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &addr_len);

    while(frame < 9){
        if(recv(cli_fd, &frame, sizeof(frame), 0) > 0){
            if(rand() % 10 < 2){
                printf("Frame %d dropped\n", frame);
            }
            else{
                printf("Frame %d received sending ACK\n", frame);
                send(cli_fd, "ACK", strlen("ACK"), 0);
            }
        }
    }
    close(serv_fd);
    close(cli_fd);
}