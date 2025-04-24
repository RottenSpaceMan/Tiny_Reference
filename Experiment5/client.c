#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define MAX_FRAME 1
#define TIMEOUT 2

void main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0), frame = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    //socket only waits for 2 second before it timesout
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(frame < 10){
        printf("Sending frame %d\n", frame);
        send(sock, &frame, sizeof(frame), 0);

        int bytes_received = read(sock, &buffer, sizeof(buffer));
        if(bytes_received > 0 && strcmp(buffer, "ACK") == 0){
            printf("ACK received for frame %d\n",frame);
            frame++;
        }
        else{
            printf("No ACK received for frame %d, resending \n", frame);
        }
        sleep(1);
    }
    close(sock);
}