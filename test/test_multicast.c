#include <stdio.h>
#include <unistd.h>

#include "libsocket/libinetsocket.h"


int main(int argc ,char* argv[])
{
    int sfd = create_multicast_socket ("239.255.255.255" ,"8081" , NULL); /*加入组播*/
    if ( sfd < 0){
        printf("create_multicast_socket failed\n");
        return -1;
    }

    char buf[32];
    int ret =0;
    while(1){
        ret = recvfrom( sfd , buf ,sizeof(buf) ,0 ,NULL ,NULL);
        if ( ret < 0 ){
            printf("recvfrom failed\n");
            destroy_inet_socket (sfd);
            return -1;
        }
        printf("%s\n" ,buf);        
    }
    destroy_inet_socket(sfd);
    return 0;
}

/**
 * 向组播发送数据:
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "239.255.255.255"
#define PORT 8081

int main() {
    struct sockaddr_in addr;
    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    addr.sin_port = htons(PORT);
    
    while (1) {
        char message[100];
        fgets(message, 100, stdin);
        sendto(sockfd, message, strlen(message)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
    }
    
    close(sockfd);
    
    return 0;
}
*/