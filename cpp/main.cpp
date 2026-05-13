#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 4096

int main() {
    char *prefix = getenv("PREFIX");
    if (!prefix) prefix = "/";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)
    };
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 10);

    char body[256];
    snprintf(body, sizeof(body), "{\"status\":\"ok\",\"runtime\":\"cpp\"}\n");
    int body_len = strlen(body);

    char response[512];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s", body_len, body);

    while (1) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) continue;
        char buf[BUF_SIZE];
        read(client, buf, BUF_SIZE);
        write(client, response, strlen(response));
        close(client);
    }
    return 0;
}
