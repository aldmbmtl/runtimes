#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 8192

static const char *HTML_BODY =
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"  <meta charset=\"UTF-8\">\n"
"  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"  <title>Juno &mdash; C++ Runtime</title>\n"
"  <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">\n"
"  <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>\n"
"  <link href=\"https://fonts.googleapis.com/css2?family=Montserrat:wght@300;400;500;700&display=swap\" rel=\"stylesheet\">\n"
"  <style>\n"
"    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }\n"
"    body {\n"
"      background: #0e0e10;\n"
"      color: #f2f2f3;\n"
"      font-family: 'Montserrat', sans-serif;\n"
"      min-height: 100vh;\n"
"      display: flex;\n"
"      align-items: center;\n"
"      justify-content: center;\n"
"    }\n"
"    .card {\n"
"      background: #1b1b1e;\n"
"      border: 1px solid #2e2e33;\n"
"      border-radius: 16px;\n"
"      padding: 48px 56px;\n"
"      max-width: 520px;\n"
"      width: 100%;\n"
"    }\n"
"    .brand {\n"
"      display: flex;\n"
"      align-items: center;\n"
"      gap: 10px;\n"
"      margin-bottom: 40px;\n"
"    }\n"
"    .brand-dot {\n"
"      width: 10px;\n"
"      height: 10px;\n"
"      border-radius: 50%;\n"
"      background: #f4a61d;\n"
"    }\n"
"    .brand-name {\n"
"      font-size: 14px;\n"
"      font-weight: 500;\n"
"      color: #9a9aa3;\n"
"      letter-spacing: 0.08em;\n"
"      text-transform: uppercase;\n"
"    }\n"
"    h1 { font-size: 32px; font-weight: 700; color: #f2f2f3; line-height: 1.2; margin-bottom: 12px; }\n"
"    h1 span { color: #f4a61d; }\n"
"    h2 { font-size: 16px; font-weight: 400; color: #9a9aa3; margin-bottom: 32px; line-height: 1.5; }\n"
"    .divider { border: none; border-top: 1px solid #2e2e33; margin-bottom: 28px; }\n"
"    .status { display: flex; align-items: center; gap: 10px; font-size: 13px; color: #9a9aa3; }\n"
"    .status-dot { width: 8px; height: 8px; border-radius: 50%; background: #34d583; flex-shrink: 0; }\n"
"  </style>\n"
"</head>\n"
"<body>\n"
"  <div class=\"card\">\n"
"    <div class=\"brand\"><div class=\"brand-dot\"></div><span class=\"brand-name\">Juno</span></div>\n"
"    <h1>Hello from <span>Juno!</span></h1>\n"
"    <h2>This is the <strong>C++</strong> runtime.</h2>\n"
"    <hr class=\"divider\">\n"
"    <div class=\"status\"><div class=\"status-dot\"></div>Runtime is healthy and ready to serve your application.</div>\n"
"  </div>\n"
"</body>\n"
"</html>\n";

int main() {
    const char *prefix = getenv("PREFIX");
    if (!prefix) prefix = "/";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 10);

    int body_len = strlen(HTML_BODY);

    char not_found[] =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 9\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Not Found";

    while (1) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) continue;

        char buf[BUF_SIZE];
        memset(buf, 0, sizeof(buf));
        read(client, buf, BUF_SIZE - 1);

        /* Parse request path from first line e.g. "GET /polaris/foo/ HTTP/1.1" */
        char method[16], path[1024], proto[16];
        int matched = 0;
        if (sscanf(buf, "%15s %1023s %15s", method, path, proto) == 3) {
            matched = (strcmp(path, prefix) == 0);
        }

        if (matched) {
            char response[256];
            int hlen = snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=utf-8\r\n"
                "Content-Length: %d\r\n"
                "Connection: close\r\n"
                "\r\n",
                body_len);
            write(client, response, hlen);
            write(client, HTML_BODY, body_len);
        } else {
            write(client, not_found, strlen(not_found));
        }
        close(client);
    }
    return 0;
}
