#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <wslay/wslay.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096
#define PROXY_HOST "127.0.0.1"
#define PROXY_PORT 7890


ssize_t recv_callback(wslay_event_context_ptr ctx, uint8_t *buf, size_t len, int flags, void *user_data) {
    return 0;
}


int main(int argc, char *argv[]) {

    int sockfd;

    // get binance address info
    struct addrinfo hints = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
            .ai_protocol = IPPROTO_TCP,
    };
    struct addrinfo *result, *rp;

    int s = getaddrinfo("stream.binance.com", "9443", &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(s));
        return EXIT_FAILURE;
    }

    // 设置代理服务器
    struct sockaddr_in proxy_addr;
    memset(&proxy_addr, 0, sizeof(proxy_addr));
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_addr.s_addr = inet_addr(PROXY_HOST);
    proxy_addr.sin_port = htons(PROXY_PORT);



    fprintf(stderr, "02");

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, (struct sockaddr *) &proxy_addr, sizeof(proxy_addr)) < 0) {
            perror("connect error");
            exit(1);
        }


        if (sendto(sockfd, "CONNECT target.example.com:80 HTTP/1.0\r\n\r\n", 40, 0, rp->ai_addr, rp->ai_addrlen) < 0) {
            perror("sendto error");
            exit(1);
        }


    }

    if (rp == NULL) {
        /* No address succeeded */
        fprintf(stderr, "Could not connect to Binance API server\n");
        return EXIT_FAILURE;
    }

    freeaddrinfo(result);

    wslay_event_context_ptr ctx;
    struct wslay_event_callbacks callbacks = {
            .recv_callback= recv_callback, // 回调函数：接收数据帧
    };

    printf("01");

    if (wslay_event_context_client_init(&ctx, &callbacks, NULL) != 0) {
        fprintf(stderr, "Failed to initialize wslay_event_context.\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("02");

    // 发送 WebSocket 握手请求
    char *request = "GET /ws/btcusdt@trade HTTP/1.1\r\n"
                    "Host: stream.binance.com\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n"
                    "Sec-WebSocket-Protocol: chat\r\n"
                    "Sec-WebSocket-Version: 13\r\n"
                    "\r\n";

    struct wslay_event_msg event_msg = {
            .msg = (uint8_t *) request,
    };

    wslay_event_queue_msg(ctx, &event_msg);

    while (wslay_event_want_write(ctx)) {
        int ret = wslay_event_send(ctx);

        if (ret != 0) {
            fprintf(stderr, "Error sending data with wslay: %d\n", ret);
            return -1;
        }
    }
    wslay_event_recv(ctx);

    wslay_event_context_free(ctx);

    return 0;
}
