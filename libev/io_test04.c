#include <ev.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void io_cb(EV_P_ ev_io *w, int revents) {
    printf("File descriptor %d is ready for reading.\n", w->fd);
    ev_io_stop(EV_A_ w);
}

int main(int argc, char **argv) {
    struct ev_loop *loop = EV_DEFAULT; // 创建事件循环
    int fd = open("file1.txt", O_RDONLY | O_CREAT, 0644); // 打开或创建一个txt文件
    if (fd < 0) {
        perror("open");
        return 1;
    }

    fchmod(fd, 0); // 将文件设置为不可读取

    printf("File descriptor %d is not ready for reading.\n", fd);

    ev_io io_watcher; // 创建IO事件
    ev_io_init(&io_watcher, io_cb, fd, EV_READ); // 监听读取事件
    ev_io_start(loop, &io_watcher); // 将事件添加到事件循环

    fchmod(fd, 0644); // 将文件设置为可读取

    ev_run(loop, 0); // 运行事件循环

    ev_io_stop(loop, &io_watcher);

    ev_loop_destroy(loop);
    return 0;
}