#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int socket, const char *filename){
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(filename, "r");
    int bytes_read;
    while(bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)){
        send(socket, buffer, bytes_read, 0);
    }
    fclose(fp);
    printf("File sent successfully\n");
}

void main(){
    int cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Connected to server\n");
    send_file(cli_fd, "sample.txt");
    close(cli_fd);
}