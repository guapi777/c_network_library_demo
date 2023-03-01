#include <ev.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void io_cb(EV_P_ ev_io *w, int revents) {
    char buf[3];
    int fd = w->fd;
    int nread = read(fd, buf, sizeof(buf));
    if (nread == 0) {
        ev_io_stop(EV_A_ w);
        return;
    }
    printf("fd %d read %d bytes: %s\n", fd, nread, buf);
}

int main() {
    struct ev_loop *loop = EV_DEFAULT;
    ev_io io_w1, io_w2;
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    if (fd1 < 0 || fd2 < 0) {
        perror("open");
        return 1;
    }
    ev_io_init(&io_w1, io_cb, fd1, EV_READ);
    ev_io_init(&io_w2, io_cb, fd2, EV_READ);

    // 设置io_w1的优先级为1，io_w2的优先级为2
    ev_set_priority(&io_w1, 1);
    ev_set_priority(&io_w2, 2);

    // 将io_w1和io_w2添加到事件循环中
    ev_io_start(loop, &io_w1);
    ev_io_start(loop, &io_w2);

    ev_run(loop, 0);

    // 释放事件观察器和libev上下文
    ev_io_stop(loop, &io_w1);
    ev_io_stop(loop, &io_w2);


    ev_loop_destroy(loop);
    return 0;
}
