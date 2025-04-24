#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define TOTAL_PACKETS 12

void main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0), packet = -1, expected_packet_num = 0;
    struct sockaddr_in cli_addr, serv_addr;
    socklen_t addr_len = sizeof(cli_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(expected_packet_num < TOTAL_PACKETS){
        recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&cli_addr, &addr_len);
        printf("Received packet %d\n", packet);
        if(packet == expected_packet_num){
            int ack = packet;
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&cli_addr, addr_len);
            printf("Sent ack for packet %d\n", packet);
            expected_packet_num++;
        } else if (packet < expected_packet_num){
            int ack = packet;
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&cli_addr, addr_len);
            printf("Sent duplicate ACK for packet %d\n", ack);
        } else {
            int ack = expected_packet_num - 1;
            if(ack >= 0){
                sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr *)&cli_addr, addr_len);
                printf("Sent ACK for %d, expecting %d\n", ack, expected_packet_num);
            }
        }
    }
}