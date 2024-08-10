#include <stdio.h>
#include <unistd.h>

#include "libsocket/libunixsocket.h"

#define UNIX_PATH "/tmp/unix.sock"

int main(int argc ,char* argv[])
{
    int sfd = create_unix_stream_socket(UNIX_PATH ,0);
    if (sfd < 0){
        printf("create_unix_stream_socket failed\n");
        return -1;
    }    

    char buf[32] ="hello unix socket!";
    int ret =0;
    while(1){
        ret = write(sfd , buf ,sizeof(buf));
        if(ret ==-1){
            destroy_unix_socket(sfd);
            printf("write failed\n");
            return -2;
        }
        sleep(2);
    }

    destroy_unix_socket(sfd);
    return 0;
}