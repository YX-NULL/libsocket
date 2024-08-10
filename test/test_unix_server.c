#include <stdio.h>
#include <unistd.h>

#include "libsocket/libunixsocket.h"

#define UNIX_PATH "/tmp/unix.sock"

int main(int argc ,char* argv[])
{
    int sfd = create_unix_server_socket(UNIX_PATH ,LIBSOCKET_STREAM ,0);
    if (sfd < 0){
        printf("create_unix_server_socket failed\n");
        return -1;
    }

    int cfd = accept_unix_stream_socket(sfd ,0);
    if (cfd < 0){
        destroy_unix_socket(sfd);
        printf("accept_unix_stream_socket failed\n");
        return -2;    
    }

    char buf[32];
    int ret =0;
    while(1){
        ret = read (cfd , buf ,sizeof(buf));
        if (ret < 0){
            printf("read failed\n");
            destroy_unix_socket(sfd);
            destroy_unix_socket(cfd);
            return -3;
        }
        printf("recv:%s\n" ,buf);
    }

    destroy_unix_socket(sfd);
    destroy_unix_socket(cfd);
    return 0;
}