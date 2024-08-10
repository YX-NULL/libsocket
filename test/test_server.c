#include <stdio.h>
#include <unistd.h>

#include "libsocket/libinetsocket.h"

// tcp server
// int main(int argc ,char* argv[])
// {
//     /*setsockopt 设置ip地址 port可以服用*/
//     int sfd = create_inet_server_socket ("127.0.0.1" ,"8080" , LIBSOCKET_TCP ,LIBSOCKET_IPv4 ,0);

//     if (sfd < 0) {
//         printf("create_inet_server_socket failed\n");
//         return -1;
//     }

//     char client_addr[32];
//     char client_port[16];
//     int connect_fd = accept_inet_stream_socket (sfd , client_addr ,sizeof(client_addr) ,client_port ,sizeof(client_port), 0 ,0);
    
//     if (connect_fd < 0){
//         printf("accept_inet_stream_socket failed\n");
//         close(sfd);
//         return -2;
//     }
//     printf("addr:%s prot:%s\n" ,client_addr ,client_port);

//     int ret = write (connect_fd ,"hello libsocket.so" ,20);
//     if (ret < 0){
//         printf("write failed\n");
//         close(sfd);
//         close(connect_fd);
//         return -3;
//     }

//     pause();
//     close(sfd);
//     close(connect_fd);
//     return 0;
// }


int main(int argc ,char* argv[])
{
    int sfd = create_inet_server_socket ("127.0.0.1" ,
                            "8081" ,LIBSOCKET_UDP , LIBSOCKET_IPv4 ,0);
    if (sfd < 0){
        printf("create_inet_server_socket failed\n");
        return -1;
    }

    char buf[32];
    char src_add[32];
    char port[16];
    int ret =0 ;
    while(1){
        ret = recvfrom_inet_dgram_socket(sfd ,buf ,sizeof(buf), src_add ,
                                    sizeof(src_add), port ,sizeof(port) , 0 ,0);
        if (ret < 0){
            printf("recvfrom_inet_dgram_socket failed\n");
            destroy_inet_socket(sfd);
            return -2;
        }
        printf("%s:%s -->%s\n" ,src_add,port, buf);
    }
    destroy_inet_socket(sfd);
    return 0;
}