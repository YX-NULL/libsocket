#include <stdio.h>
#include <unistd.h>

#include "libsocket/libinetsocket.h"

// int main(int argc ,char* argv[])
// {
//     int sfd = create_inet_stream_socket("127.0.0.1" ,"8080" ,LIBSOCKET_IPv4 ,0);

//     if (sfd < 0){
//         printf("create_inet_stream_socket failed\n");
//         return -1;
//     }

//     char buf[32];
//     int ret = read (sfd ,buf ,sizeof(buf));

//     printf("recv:%s\n" ,buf);

//     destroy_inet_socket(sfd);
//     return 0;
// }

int main(int argc ,char* argv[])
{
    int sfd = create_inet_dgram_socket (LIBSOCKET_IPv4 ,0);
    if ( sfd < 0){
        printf("create_inet_dgram_socket failed\n");
        return -1;
    }

    char buf[32] = "hello udp";
    int ret = 0;
    while(1){
        ret = sendto_inet_dgram_socket(sfd , buf ,sizeof(buf),"127.0.0.1" ,"8081" ,0);
        if(ret ==-1){
            printf("sendto_inet_dgram_socket failed\n");
            destroy_inet_socket(sfd);
            return -1;
        }
        sleep(2);
    }

    destroy_inet_socket(sfd);
    return 0;
}