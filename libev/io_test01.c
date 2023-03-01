#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void stdin_cb(EV_P_ ev_io *w, int revents) {
    if (EV_ERROR & revents) {
        perror("got invalid event");
        return;
    }

    char buf[1024];
    ssize_t len = read(w->fd, buf, sizeof(buf));
    if (len == -1) {
        perror("read error");
        ev_io_stop(EV_A_ w);
        return;
    }

    if (len == 1) {
        printf("stdin closed\n");
        ev_io_stop(EV_A_ w);
        return;

    }

    printf("read %zd bytes: %.*s", len, (int)len, buf);
}

int main(int argc, char **argv) {
    // 初始化libev上下文
    struct ev_loop *loop = EV_DEFAULT;

    // 创建ev_io事件观察器
    ev_io stdin_watcher;
    ev_io_init(&stdin_watcher, stdin_cb, STDIN_FILENO, EV_READ);

    // 启动事件观察器
    ev_io_start(loop, &stdin_watcher);

    // 进入事件循环
    ev_run(loop, 0);

    // 释放事件观察器和libev上下文
    ev_io_stop(loop, &stdin_watcher);
    ev_loop_destroy(loop);


    return 0;
}
