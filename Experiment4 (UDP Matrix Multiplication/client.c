#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr;
    int len = sizeof(serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int r1, c1, r2, c2, mat1[10][10], mat2[10][10], res[10][10];

    printf("Enter number of rows and columns of first matrix: ");
    scanf("%d%d",&r1,&c1);
    printf("Enter number of rows and columns of second matrix: ");
    scanf("%d%d",&r2,&c2);

    if(c1!=r2){
        printf("Matrix multiplication not possible with given dimesions");
        close(sock);
        return 0;
    }

    printf("Enter elements of first matrix:\n");
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c1; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");
    for(int i = 0; i < r2; i++){
        for(int j = 0; j < c2; j++){
            scanf("%d", &mat2[i][j]);
        }
    }

    sendto(sock, &r1, sizeof(r1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sock, &c1, sizeof(c1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sock, &r2, sizeof(r2), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sock, &c2, sizeof(c2), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sock, &mat1, sizeof(mat1), 0, (struct sockaddr *)&serv_addr, len);
    sendto(sock, &mat2, sizeof(mat2), 0, (struct sockaddr *)&serv_addr, len);

    recvfrom(sock, res, sizeof(res), MSG_WAITALL, (struct sockaddr *)&serv_addr, &len);

    printf("Resultant matrix\n");
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            printf("%d",res[i][j]);
        }
        printf("\n");
    }
    close(sock);
    return 0;
}
