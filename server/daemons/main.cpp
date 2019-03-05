#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
 
const char* response =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<doctype !html>\n"
"    <html>\n"
"        <head>\n"
"            <title>Bye-bye baby bye-bye</title>\n"
"            <style>body { background-color: #111 }\n"
"                   h1 { font-size:4cm; text-align: center; color: black;\n"
"                        text-shadow: 0 0 2mm red}\n"
"            </style>\n"
"        </head>\n"
"<body>\n"
"        <h1>Goodbye, world!</h1>\n"
"</body>\n"
"</html>\r\n";
 
int main(int argc, char* argv[])
{
        int one = 1;
        int client_fd;
        struct sockaddr_in svr_addr;
        struct sockaddr_in cli_addr;
        socklen_t sin_len = sizeof(cli_addr);
 
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            err(1, "can't open socket");
        }
 
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
 
        int port = 8080;
        svr_addr.sin_family = AF_INET;
        svr_addr.sin_addr.s_addr = INADDR_ANY;
        svr_addr.sin_port = htons(port);
 
        if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
            close(sock);
            err(1, "Can't bind");
        }
 
        listen(sock, 5);
        while (true) {
            client_fd = accept(sock,
                    (struct sockaddr *) &cli_addr,
                            &sin_len);
            printf("got connection\n");

            if (client_fd == -1) {
                    perror("Can't accept");
                    continue;
            }

            ssize_t total_cnt = 0, now_cnt;
            while (total_cnt != strlen(response)) {
                now_cnt = write(client_fd, response + total_cnt, strlen(response) - total_cnt);
                total_cnt += now_cnt;
            }
            close(client_fd);
        }
};
