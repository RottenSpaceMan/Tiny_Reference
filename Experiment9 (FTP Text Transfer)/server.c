#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void receive_file(int client_socket){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen("Received file", "w");
    int bytes_received;
    while(bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)){
        fwrite(buffer, sizeof(char), bytes_received, fp);
    }
    fclose(fp);
    printf("File written successfully\n");
}

void main(){
    int serv_fd, cli_fd;
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in cli_addr, serv_addr;
    socklen_t addr_len = sizeof(cli_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(serv_fd, 3);

    cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &addr_len);
    receive_file(cli_fd);
    close(cli_fd);
    close(serv_fd);
}