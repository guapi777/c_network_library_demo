#include <ev.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define NFDS 2

void io_cb(EV_P_ ev_io *w, int revents) {
    char buf[3];
    int fd = w->fd;
    int nread = read(fd, buf, sizeof(buf));
    if (nread == 0) {
        printf("fd %d stop \n", fd);
        ev_io_stop(EV_A_ w);
    } else {
        buf[nread] = '\0';
        printf("fd %d read %d bytes: %s\n", fd, nread, buf);
    }
}

int main() {
    struct ev_loop *loop = EV_DEFAULT;
    ev_io io_w[NFDS];
    int fds[NFDS] = {0};
    fds[0] = open("file1.txt", O_RDONLY);
    fds[1] = open("file2.txt", O_RDONLY);
    if (fds[0] < 0 || fds[1] < 0) {
        perror("open");
        return 1;
    }
    for (int i = 0; i < NFDS; i++) {
        ev_io_init(&io_w[i], io_cb, fds[i], EV_READ);
        ev_io_start(loop, &io_w[i]);
    }
    ev_run(loop, 0);

    // 释放事件观察器和libev上下文
    ev_io_stop(loop, &io_w[0]);
    ev_io_stop(loop, &io_w[1]);


    ev_loop_destroy(loop);

    return 0;
}
