#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SOCKFILENAME "/tmp/msock.1"

char readbuf[1000];

int main() {

    struct sockaddr_un sock_address = {
            AF_UNIX,
            SOCKFILENAME
    };

    struct sockaddr_un cl_addr;
    socklen_t addrlen;

    int sock = socket(PF_UNIX, SOCK_STREAM, 0);
    int bind_result = bind(sock, (struct sockaddr*)&sock_address, sizeof (sock_address));
    int listen_result = listen(sock, 10);
    int connected_socket = accept(sock, (struct sockaddr*)&cl_addr, &addrlen);

//    while (recv(connected_socket, readbuf, 1000, 0) > 0) {
        ssize_t count1 = recv(connected_socket, readbuf, 1000, 0);
        for (ssize_t i = 0; i < count1 ; i++) {
            putchar(readbuf[i]);
        }
        putchar('\n');

        ssize_t count2 = recv(connected_socket, readbuf, 1000, 0);
        for (ssize_t i = count1; i < count2 ; i++) {
            putchar(readbuf[i]);
        }
        putchar('\n');
//    }

    printf("socket descriptor = %d\n", sock);
    printf("bind result = %d\n", bind_result);
    printf("listen result = %d\n", listen_result);
    printf("connected_socket = %d\n", connected_socket);
    printf("count1 = %d\n", count1);
    printf("count2 = %d\n", count2);
    remove(SOCKFILENAME);
    printf("Work finished!\n");
    return 0;
}
