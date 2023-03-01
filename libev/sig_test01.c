#include <ev.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// 回调函数，当收到 SIGINT 信号时被调用
static void signal_cb(EV_P_ ev_signal *w, int revents) {
    printf("Got SIGINT\n");
    ev_break(EV_A_ EVBREAK_ALL);
}

int main(int argc, char **argv) {
    // 初始化libev上下文
    struct ev_loop *loop = EV_DEFAULT;

    // 创建ev_signal事件观察器
    ev_signal signal_watcher;
    ev_signal_init(&signal_watcher, signal_cb, SIGINT);

    // 启动事件观察器
    ev_signal_start(loop, &signal_watcher);

    // 进入事件循环
    ev_run(loop, 0);

    // 释放事件观察器和libev上下文
    ev_signal_stop(loop, &signal_watcher);
    ev_loop_destroy(loop);

    return 0;
}
