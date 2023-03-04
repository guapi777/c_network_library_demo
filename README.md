# c_network_library_demo

[TOC]

## libev

libev是一个高性能事件驱动库，可以用于开发基于事件驱动的网络应用程序。它提供了一个事件循环和事件处理器，使得开发者可以通过注册回调函数来响应各种事件。

以下是libev的一些主要功能：

- 支持多种事件类型：libev支持多种事件类型，包括文件描述符、信号、定时器等，开发者可以通过注册回调函数来处理这些事件。

- 高性能：libev使用了多种优化技术，如epoll、kqueue等系统调用，以及缓存机制、事件合并等技术，提高了事件处理的效率。

- 可扩展性：libev可以很容易地与其他库和框架集成，如libevent、nginx等。

- 跨平台支持：libev支持多种操作系统，包括Linux、BSD、Solaris等。

- 线程安全：libev可以在多线程环境中使用，多个线程可以共享一个事件循环。

总之，libev是一个非常实用的事件驱动库，可以帮助开发者构建高性能的网络应用程序。

### methods

#### ev_io_init()

ev_io_init(struct ev_io *w, void (*cb)(struct ev_loop *loop, struct ev_io *w, int revents), int fd, int events)

初始化ev_io观察者，用于I/O事件的监听。该函数将ev_io结构体指针w与指定的文件描述符fd和事件类型events进行绑定，并设置回调函数cb用于处理I/O事件。

#### ev_io_start()

ev_io_start(struct ev_loop *loop, struct ev_io *w)

启动ev_io观察者，将其注册到事件循环loop中，开始监听I/O事件。

#### ev_io_stop()

ev_io_stop(struct ev_loop *loop, struct ev_io *w)

停止ev_io观察者，从事件循环loop中移除该观察者，停止监听I/O事件。

#### ev_io_set()

ev_io_set(struct ev_io *w, int fd, int events) 

设置ev_io观察者的文件描述符和事件类型，用于在运行时更改监听的I/O事件。


### structs

### examples

#### io_test01.c

示例程序中，首先初始化了一个libev上下文，并创建了一个ev_io事件观察器来监听标准输入的读取事件。

当标准输入上有数据可读时，stdin_cb回调函数将被调用。在回调函数中，使用read函数读取输入数据并输出到控制台。如果读取出错或读到了文件结束标志，程序将停止监听标准输入并退出事件循环。

在主函数中，启动事件观察器并进入事件循环。当标准输入被关闭或事件循环结束时，程序将释放事件观察器和libev上下文。

#### io_test02.c

示例代码使用了一个ev_io数组io_w和一个int数组fds，分别用于存储多个ev_io观察者和多个文件描述符。

在主函数中，先通过open函数打开两个文件，分别作为文件描述符0和1存入fds数组中。

然后，使用for循环对每个文件描述符都初始化一个ev_io观察者，并将它们都启动起来，开始监听EV_READ事件（即文件可读事件）。

最后，调用ev_run函数进入事件循环，等待I/O事件的到来。

需要注意的是，该示例代码中的ev_io观察者和文件描述符都是在主函数中定义的局部变量，因此在事件循环运行期间不能随意修改它们。如果需要在运行期间动态添加或删除观察者，需要使用动态内存分配等技术，确保能够在事件循环中动态管理I/O事件观察者。

#### io_test03.c

该示例代码中使用ev_set_priority()函数将io_w1的优先级设置为1，将io_w2的优先级设置为2，然后将它们添加到事件循环中。

由于io_w2的优先级高于io_w1，因此在同时有I/O事件到达的情况下，io_w2会被先处理。

#### io_test04.c

在这个示例中，首先打开或创建一个名为“file1.txt”的文件，并使用fchmod()将其设置为不可读取。

然后，创建一个ev_io对象，用于监听文件描述符的读取事件，并设置一个回调函数，当文件描述符可读时触发。

接着，将IO事件添加到事件循环中，并使用fchmod()将文件设置为可读取。

最后，运行事件循环，等待文件描述符可读事件的发生。

#### io_test05.c

在这个示例中，首先打开或创建一个名为“file1.txt”的文件，并使用fchmod()将其设置为不可写入。

然后，创建一个ev_io对象，用于监听文件描述符的写入事件，并设置一个回调函数，当文件描述符可写入时触发。

接着，将IO事件添加到事件循环中，并使用fchmod()将文件设置为可写入。

最后，运行事件循环，等待文件描述符可写入事件的发生。

#### sig_test01.c

用 SIGINT 信号触发 libev 回调的样例代码

## openssl

OpenSSL是一个开源的安全套接字层协议库，提供了很多加密算法和安全协议的实现，例如SSL、TLS、DTLS等。它可以用于构建安全的网络通信应用，比如HTTPS、FTPS等。OpenSSL支持多种操作系统和编程语言，包括C、C++、Java、Python等。

与libev配合使用，通常可以通过以下几个步骤来实现：

- 使用libev创建一个TCP客户端或服务器，连接到目标主机或监听指定端口；

- 在连接或监听成功后，使用OpenSSL创建一个SSL上下文对象（SSL_CTX），并进行SSL会话的初始化；

- 将创建的SSL上下文对象关联到TCP套接字上，以启用SSL安全通信；

- 在进行网络数据传输时，使用OpenSSL提供的加密和解密函数对数据进行加密和解密操作，以保证通信的安全性；

- 在通信结束后，使用OpenSSL释放相关资源。

需要注意的是，使用OpenSSL进行安全通信的过程中，还需要进行证书的验证和管理，以确保通信的安全性。证书的验证和管理涉及到多种复杂的加密算法和协议，需要具备一定的专业知识和技能。

---

要使用 OpenSSL 库连接网站，可以按照以下步骤进行操作：

1. 创建 SSL/TLS 会话上下文：首先需要创建一个 SSL/TLS 会话上下文对象，通过设置 SSL 协议版本、加密算法、证书等信息来配置该对象。可以使用 SSL_CTX_new() 函数创建一个新的 SSL/TLS 会话上下文对象，然后使用 SSL_CTX_set_*() 函数设置 SSL/TLS 会话上下文的相关参数。

2. 创建 TCP 套接字并连接：在连接网站之前，需要先创建一个 TCP 套接字并连接到网站的服务器。可以使用 socket() 函数创建一个新的 TCP 套接字，然后使用 connect() 函数将套接字连接到网站的服务器。

3. 将 SSL/TLS 会话与 TCP 套接字关联：创建 SSL/TLS 会话上下文和 TCP 套接字之后，需要将它们关联起来，以便在 SSL/TLS 握手过程中使用。可以使用 SSL_new() 函数创建一个新的 SSL/TLS 会话对象，然后使用 SSL_set_fd() 函数将该对象与 TCP 套接字关联。

4. 开始 SSL/TLS 握手：在将 SSL/TLS 会话对象与 TCP 套接字关联后，可以使用 SSL_connect() 函数开始 SSL/TLS 握手协议，建立安全通道。

5. 发送和接收数据：完成 SSL/TLS 握手之后，就可以通过 SSL/TLS 会话对象发送和接收数据了。可以使用 SSL_write() 函数发送数据，使用 SSL_read() 函数接收数据。



### structs

#### SSL_CTX

在 OpenSSL 中，SSL_CTX 对象是 SSL 上下文对象，它是一个包含 SSL 会话配置信息的数据结构。该对象被用于创建和管理 SSL 会话，包括 SSL 握手协议的相关参数，加密和解密算法，以及证书和密钥等信息。可以看作是一个全局的配置，一般在程序初始化时创建，可以被多个SSL连接对象共享。使用SSL_CTX可以提高SSL/TLS连接的效率和安全性。

使用 SSL_CTX 对象可以完成如下功能：

- 加载 SSL 证书和私钥

- 配置 SSL 协议版本和加密算法

- 设置 CA 证书验证等级

- 配置 SSL 会话缓存
SSL是一个具体的SSL/TLS连接对象，代表了一个客户端与服务端之间的安全通道。SSL_CTX对象是创建SSL对象的模板，一个SSL对象必须要与一个SSL_CTX对象关联，才能进行握手和数据传输等操作。在握手过程中，SSL对象会从SSL_CTX对象中获取相关配置信息，例如加密算法、证书、私钥等等，然后通过握手协议和服务端建立安全通道。
- 管理 SSL 会话上下文等

在使用 OpenSSL 进行 SSL 通信时，通常需要先创建一个 SSL_CTX 对象，然后使用该对象创建一个 SSL 会话上下文，最后通过该上下文对象创建 SSL 连接。

#### SSL

SSL是一个具体的SSL/TLS连接对象，代表了一个客户端与服务端之间的安全通道。SSL_CTX对象是创建SSL对象的模板，一个SSL对象必须要与一个SSL_CTX对象关联，才能进行握手和数据传输等操作。在握手过程中，SSL对象会从SSL_CTX对象中获取相关配置信息，例如加密算法、证书、私钥等等，然后通过握手协议和服务端建立安全通道。

## wslay

wslay是一个轻量级的WebSocket协议库，支持WebSocket协议的所有规范，包括WebSocket握手、帧格式、消息分片等。wslay的设计目标是高性能、易用性和可移植性，它提供了简单的API接口和灵活的事件处理机制，可以用于实现WebSocket客户端和服务器应用。

wslay可以与libev配合使用，以实现异步、非阻塞的WebSocket通信。一般来说，可以通过以下几个步骤来实现：

- 使用libev创建一个TCP客户端或服务器，连接到目标主机或监听指定端口；

- 在连接或监听成功后，使用wslay创建一个WebSocket会话对象（wslay_event_context），并进行WebSocket握手；

- 将创建的WebSocket会话对象关联到TCP套接字上，以启用WebSocket通信；

- 在进行网络数据传输时，使用wslay提供的事件处理函数对WebSocket消息进行处理，包括消息帧的解析、消息的分片、消息的组装等；

- 在WebSocket通信结束后，使用wslay释放相关资源。

需要注意的是，使用wslay进行WebSocket通信 的过程中，还需要遵循WebSocket协议的规范和标准，包括消息格式、状态码、错误处理等。在处理WebSocket消息时，需要特别注意消息分片、消息合并、控制帧的处理等问题，以确保通信的正确性和稳定性。

综上所述，使用wslay与libev配合使用可以实现高性能、异步、非阻塞的WebSocket通信，但需要遵循WebSocket协议的规范和标准，注意消息的分片和合并、控制帧的处理等问题。

其官方文档的网站为    https://tatsuhiro-t.github.io/wslay/index.html

### 1. structs

#### wslay_event_context

`wslay_event_context` 代表一个 WebSocket 事件上下文，用于管理一个 WebSocket 连接上的事件处理器。

这个结构体的成员变量包括：

- `callbacks`: 一个 `wslay_event_callbacks` 结构体，包含了用户定义的回调函数，用于处理 WebSocket 事件。
- `user_data`: 用户数据指针，可以存储一些额外的信息，由用户自己管理。
- `send_queue`: 发送队列，用于存储等待发送的 WebSocket 数据帧。
- `recv_queue`: 接收队列，用于存储已接收但尚未处理的 WebSocket 数据帧。
- `read_limit`: 读取限制，用于控制一次读取数据的最大字节数。
- `write_limit`: 写入限制，用于控制一次写入数据的最大字节数。
- `max_recv_msg_length`: 接收消息的最大长度限制，用于防止接收到超过限制长度的消息。
- `max_send_msg_length`: 发送消息的最大长度限制，用于防止发送超过限制长度的消息。
- `error_code`: 错误码，用于表示 WebSocket 连接的错误状态。
- `status_code`: 状态码，用于表示 WebSocket 连接的状态信息。
- `error_callback`: 错误回调函数，用于在发生错误时进行回调。
- `msg_recv_callback`: 消息接收回调函数，用于在接收到消息时进行回调。
- `frame_recv_callback`: 帧接收回调函数，用于在接收到帧时进行回调。
- `frame_send_callback`: 帧发送回调函数，用于在发送帧时进行回调。
- `frame_not_send_callback`: 帧未发送回调函数，用于在发送帧失败时进行回调。
- `send_callback`: 发送回调函数，用于在发送数据时进行回调。
- `on_msg_recv_callback`: 消息接收完成回调函数，用于在消息接收完成后进行回调。

#### wslay_frame

`wslay_frame` 结构体定义了 WebSocket 数据帧的各种属性，包括：

- `fin`：表示是否是最后一个分片。
- `rsv`：表示保留位，用于扩展协议。
- `opcode`：表示数据的类型，比如文本、二进制等。
- `mask`：表示是否使用掩码。
- `payload_length`：表示有效载荷的长度。
- `payload`：指向有效载荷的指针。

#### wslay_event_config 

`wslay_event_config` 结构体是 Wslay WebSocket 配置结构体，包含了一些与 WebSocket 连接相关的配置信息和回调函数等信息。以下是 `wslay_event_config` 结构体的成员变量和存储的信息：

- `max_recv_msg_length`：最大接收消息长度。
- `timeout_ms`：超时时间，以毫秒为单位。
- `callbacks`：回调函数结构体，包含用于处理各种 WebSocket 事件的回调函数的指针。
- `user_data`：用户自定义数据指针，可用于在回调函数中访问用户自定义数据。

通过对 `wslay_event_config` 结构体进行配置，我们可以自定义一些 WebSocket 相关的配置信息和回调函数，以实现更加灵活的 WebSocket 功能。这些配置信息和回调函数可以根据应用程序的需求进行自定义配置。

#### wslay_event_callbacks

```c
struct wslay_event_callbacks {
    wslay_event_recv_callback                recv_callback;
    wslay_event_send_callback                send_callback;
    wslay_event_genmask_callback             genmask_callback;
    wslay_event_on_frame_recv_start_callback on_frame_recv_start_callback;
    wslay_event_on_frame_recv_chunk_callback on_frame_recv_chunk_callback;
    wslay_event_on_frame_recv_end_callback   on_frame_recv_end_callback;
    wslay_event_on_msg_recv_callback         on_msg_recv_callback;
};
```

`wslay_event_callbacks` 是一个结构体，定义了一组回调函数，用于处理 WebSocket 连接的各种事件。

作用：

- `recv_callback`：当 WebSocket 连接接收到数据时，将调用此回调函数。
- `send_callback`：当 WebSocket 连接需要发送数据时，将调用此回调函数。
- `on_frame_recv_start_callback`：当 WebSocket 连接开始接收数据帧时，将调用此回调函数。
- `on_frame_recv_chunk_callback`：当 WebSocket 连接接收到数据帧数据时，将调用此回调函数。
- `on_frame_recv_end_callback`：当 WebSocket 连接接收到完整的数据帧时，将调用此回调函数。

通过设置这些回调函数，我们可以在 WebSocket 连接中处理各种事件。例如，在 `on_msg_recv_callback` 中，我们可以处理完整的消息，然后在 `send_callback` 中发送响应。在 `on_close_callback` 中，我们可以清理资源并关闭连接。

#### genmask_callback

`genmask_callback` 是 Wslay 库中的一个回调函数类型，用于生成 WebSocket 数据帧的掩码，只有在初始化 WebSocket 客户端使用的事件驱动 API 时才需要使用。

在 WebSocket 协议中，客户端发送的所有数据帧都必须进行掩码操作，而服务器发送的数据帧则不能进行掩码操作。因此，当 WebSocket 客户端发送数据帧时，需要生成掩码，这个回调函数就是用来完成这个任务的。

此回调函数的输入参数包括：

- `wslay_event_context_ptr ctx`：指向 Wslay WebSocket 事件上下文结构体的指针。
- `uint8_t *buf`：指向掩码数据的指针。
- `size_t len`：掩码数据的长度。
- `void *user_data`：用户数据指针，用于传递用户自定义数据。

此回调函数的返回值为整型，表示生成掩码的结果。如果生成掩码成功，返回值为 0；如果出现错误，返回值为 -1。如果出现错误，还需要使用 `wslay_event_set_error()` 函数设置错误代码为 `WSLAY_ERR_CALLBACK_FAILURE`。

当 WebSocket 客户端需要发送数据帧时，会调用 `wslay_event_send()` 函数，并在需要时调用 `genmask_callback` 函数生成掩码。在 `genmask_callback` 函数中，需要将生成的掩码数据填充到 `buf` 中，并确保填充的字节数为 `len`。如果返回值为 0，表示成功生成掩码；如果返回值为 -1，表示生成掩码失败。

### 2. methods

#### wslay_event_frame_recv_callback()

```c
typedef int (*wslay_event_frame_recv_callback)
    (wslay_event_context_ptr ctx, const struct wslay_frame *frame, void *user_data);
```

在 wslay 中，`wslay_event_frame_recv_callback` 是一个回调函数指针类型，用于处理接收到 WebSocket 数据帧的事件。

这个回调函数的输入参数包括：

- `ctx`：一个指向 `wslay_event_context` 结构体的指针，表示当前 WebSocket 事件上下文。
- `frame`：一个指向 `wslay_frame` 结构体的指针，表示接收到的 WebSocket 数据帧。
- `user_data`：一个指针，表示用户自定义数据。

回调函数的输出参数为 `int` 类型，表示处理结果，返回 0 表示成功，其他值表示失败。如果回调函数返回非 0 值，则表示出现了错误，WebSocket 连接将被关闭。

如果需要在回调函数中发送数据，可以将数据帧添加到 `send_queue` 队列中，由事件处理循环负责发送。

#### wslay_event_context_client_init()

```c
int wslay_event_context_client_init(wslay_event_context_ptr* ctx_ptr,
                                    const struct wslay_event_callbacks* callbacks,
                                    void* user_data);
```

`wslay_event_context_client_init()` 是一个函数，用于初始化一个 WebSocket 客户端的事件上下文。

这个函数的输入参数包括：

- `ctx_ptr`：一个指向 `wslay_event_context_ptr` 的指针，表示要初始化的事件上下文。
- `callbacks`：一个指向 `wslay_event_callbacks` 结构体的指针，表示要使用的回调函数集合。
- `user_data`：一个指针，表示用户自定义数据。

其中，`wslay_event_callbacks` 结构体定义了一组回调函数，用于处理 WebSocket 连接的各种事件。

这个函数的输出参数为 `int` 类型，表示处理结果，返回 0 表示成功，其他值表示失败。

调用这个函数可以初始化一个 WebSocket 客户端的事件上下文，包括设置默认的读取和写入限制，设置默认的最大消息长度和最大帧负载长度等参数。同时，它也可以将用户自定义的回调函数和数据存储到事件上下文中，以便在事件处理中使用。

在初始化完成后，可以调用其他 wslay 库函数来处理 WebSocket 事件，比如建立 WebSocket 连接、发送和接收数据等。处理完毕后，还需要调用 `wslay_event_context_free()` 函数来释放事件上下文的内存。

#### wslay_event_config_set_callbacks()

`wslay_event_config_set_callbacks()` 是一个用于设置 Wslay WebSocket 事件上下文结构体 (`wslay_event_context`) 的回调函数的函数。

函数的输入参数包括：

- `wslay_event_config *cfg`：一个指向 Wslay WebSocket 配置结构体的指针。
- `const struct wslay_event_callbacks *callbacks`：一个指向回调函数结构体的指针。回调函数结构体包含了一组指向回调函数的指针，用于处理各种 WebSocket 事件。

函数没有输出，只是将回调函数结构体指针保存到配置结构体中。

通过调用此函数，我们可以为 WebSocket 事件上下文结构体配置自定义的回调函数，用于处理各种 WebSocket 事件。我们可以通过回调函数处理收到的数据，发送响应，关闭连接等等。配置回调函数可以实现自定义的 WebSocket 逻辑。

#### wslay_event_want_write()

`wslay_event_want_write()` 是一个用于判断是否需要写入数据的函数。当返回值为非零时，表示需要写入数据；当返回值为零时，表示不需要写入数据。

函数的输入参数包括：

- `wslay_event_context *ctx`：一个指向 Wslay WebSocket 事件上下文结构体的指针。

函数的返回值是一个整数，表示是否需要写入数据。返回值为 0 表示不需要写入数据，非零值表示需要写入数据。

通过调用此函数，我们可以判断当前 WebSocket 连接是否需要写入数据。如果需要写入数据，则可以调用相应的发送函数将数据写入。这个函数通常在事件循环中被调用，用于确定是否需要进行数据写入。例如，如果返回值为非零，就可以使用 select() 等系统调用来等待文件描述符就绪，以确保在写入数据时不会发生阻塞。

#### wslay_event_send()

`wslay_event_send()` 函数是一个用于发送 WebSocket 消息的函数。

函数的输入参数包括：

- `wslay_event_context *ctx`：一个指向 Wslay WebSocket 事件上下文结构体的指针。
- `const struct wslay_event_msg *msg`：一个指向要发送的 WebSocket 消息结构体的指针。

函数的输出是一个整数，表示消息是否成功发送。如果返回值为零，表示消息未能成功发送。

通过调用此函数，我们可以直接发送 WebSocket 消息，而不是将消息压入事件队列中等待事件处理器发送。这种方法虽然可以简单地发送消息，但也有可能出现阻塞的情况，从而降低 WebSocket 连接的性能和稳定性。因此，建议使用 `wslay_event_queue_push()` 函数将要发送的消息压入事件队列中，等待事件处理器处理并发送消息。

#### wslay_event_recv()

`wslay_event_recv()` 是一个用于接收 WebSocket 数据并触发相关事件的函数。

函数的输入参数包括：

- `wslay_event_context *ctx`：一个指向 Wslay WebSocket 事件上下文结构体的指针。

函数的输出是一个整数，表示接收数据的字节数。如果返回值为负数，表示接收数据发生了错误。

通过调用此函数，我们可以接收 WebSocket 数据并触发相关事件。函数将会根据接收到的数据内容，触发相应的事件回调函数，如收到新消息、收到 Ping 消息、收到关闭连接等事件。可以通过设置回调函数来自定义处理这些事件。

#### wslay_event_want_read()

`wslay_event_want_read()` 是一个用于判断是否需要读取数据的函数。当返回值为非零时，表示需要读取数据；当返回值为零时，表示不需要读取数据。

函数的输入参数包括：

- `wslay_event_context *ctx`：一个指向 Wslay WebSocket 事件上下文结构体的指针。

函数的返回值是一个整数，表示是否需要读取数据。返回值为 0 表示不需要读取数据，非零值表示需要读取数据。

通过调用此函数，我们可以判断当前 WebSocket 连接是否需要读取数据。如果需要读取数据，则可以调用相应的接收函数将数据读入。这个函数通常在事件循环中被调用，用于确定是否需要进行数据读取。例如，如果返回值为非零，就可以使用 select() 等系统调用来等待文件描述符就绪，以确保在读取数据时不会发生阻塞。

#### wslay_event_context_free()

`wslay_event_context_free()` 是一个用于释放 Wslay WebSocket 事件上下文结构体 (`wslay_event_context`) 的函数。在释放上下文结构体之前，函数会先清理所有与该上下文相关的资源。

函数的输入参数是一个指向要释放的上下文结构体的指针（`wslay_event_context **ctx_ptr`）。在函数执行结束后，该指针将被设置为 `NULL`。

函数没有输出。释放操作在函数内部完成，而不是返回值。

### 3. binance webscoket

参考于 https://binance-docs.github.io/apidocs/websocket_api/cn/ 



## nghttp2

HTTP/2协议是一种二进制协议，相对于HTTP/1.x协议具有更高的性能和更好的压缩性能。nghttp2是一个开源的HTTP/2实现库，支持多种语言和操作系统。

下面介绍如何使用libev和nghttp2实现异步、非阻塞的HTTP/2协议通信：

- 使用libev创建一个TCP客户端或服务器，连接到目标主机或监听指定端口；

- 在连接或监听成功后，使用nghttp2创建一个会话对象（nghttp2_session），并进行HTTP/2握手；

- 将创建的会话对象关联到TCP套接字上，以启用HTTP/2协议通信；

- 在进行网络数据传输时，使用nghttp2提供的事件处理函数对HTTP/2消息进行处理，包括消息帧的解析、消息的分片、消息的组装等；

- 在HTTP/2通信结束后，使用nghttp2释放相关资源。

需要注意的是，使用nghttp2进行HTTP /2通信的过程中，还需要遵循HTTP/2协议的规范和标准，包括消息格式、状态码、错误处理等。在处理HTTP/2消息时，需要特别注意消息分片、消息合并、帧优先级、流控制等问题，以确保通信的正确性和稳定性。

## llhttp

## kernel bypass

Kernel bypass（内核旁路）是一种网络协议栈的设计方法，旨在绕过操作系统内核的网络协议处理，直接将数据传输到网卡上进行处理。这种方法可以极大地提高网络性能和吞吐量，特别是在高负载、高并发的网络环境中。

传统的网络协议栈通常是由操作系统内核负责管理和处理的，每个数据包都需要经过多个内核层进行处理和转发。这种方式的好处是方便管理和维护，但是在高负载和高并发的情况下，会对系统性能造成很大的影响。

通过Kernel bypass技术，网络数据包可以直接从网卡上读取和写入，避免了内核层的处理，提高了系统的性能和吞吐量。这种方法通常需要使用专门的硬件设备或驱动程序来实现，并且需要针对不同的硬件平台和网络协议进行优化和调整。常见的Kernel bypass实现方式包括DPDK、Netmap、XDP等。

## others

### 1. structs 

#### addrinfo

```c
struct addrinfo {
    int ai_flags;           // 标志，指定返回的地址信息类型
    int ai_family;          // 地址族，例如 AF_INET、AF_INET6 等
    int ai_socktype;        // 套接字类型，例如 SOCK_STREAM、SOCK_DGRAM 等
    int ai_protocol;        // 传输协议，例如 IPPROTO_TCP、IPPROTO_UDP 等
    socklen_t ai_addrlen;   // 地址长度
    struct sockaddr *ai_addr; // 地址结构体指针
    char *ai_canonname;     // 官方主机名（规范名）
    struct addrinfo *ai_next; // 链表指针，指向下一个地址结构体
};
```

`addrinfo` 结构体定义在头文件 `<netdb.h>` 中，是一个用于描述 socket 地址信息的结构体，它通常用于在网络编程中获取可用的网络地址列表，以便选择最适合的地址进行网络通信。

`addrinfo` 结构体包含以下成员变量：

- `ai_flags`标志，用于指定返回的地址信息类型，可以是以下值之一：
  - `AI_PASSIVE`：用于创建被动式套接字（通常在服务器端使用）。
  - `AI_CANONNAME`：返回官方主机名（规范名）。
  - `AI_NUMERICHOST`：如果节点名无法解析，则返回一个数字格式的地址。
  - `AI_NUMERICSERV`：如果服务名无法解析，则返回一个数字格式的端口号。
  - `AI_V4MAPPED`：如果没有 IPv6 地址，则返回 IPv4 地址。
  - `AI_ALL`：返回所有符合条件的地址。
  
- `ai_family`：地址族，例如 AF_INET（IPv4）、AF_INET6（IPv6）等。

- `ai_socktype`：套接字类型，例如 SOCK_STREAM（流式套接字）、SOCK_DGRAM（数据报套接字）等。

- `ai_protocol`：传输协议，例如 IPPROTO_TCP（TCP协议）、IPPROTO_UDP（UDP协议）等。

- `ai_addrlen`：地址长度，单位为字节。

- `ai_addr`：指向一个 sockaddr 结构体的指针，用于存储地址信息。

- `ai_canonname`：指向一个字符串，表示官方主机名（规范名）。

- `ai_next`：指向一个 addrinfo 结构体的指针，用于存储下一个地址信息。当使用 getaddrinfo 函数获取多个地址信息时，返回的地址信息会形成一个链表，ai_next 指向下一个地址信息结构体。

### 2. methods

#### getaddrinfo()

```c
int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints, struct addrinfo **res);
```

`getaddrinfo()` 方法是一个用于获取网络地址信息的函数，它可以根据给定的主机名、服务名或者地址信息结构体，返回一个或多个可用的地址信息列表。该函数定义在头文件 `<sys/socket.h>` 和 `<netdb.h>` 中

该函数的输入参数包括：

- `node` ：表示主机名或者地址字符串，可以是以下格式之一：

    - IP 地址字符串（例如："192.168.0.1"）；

    - 域名（例如："[www.example.com"）；](http://www.example.com")%3B/)

    - NULL（表示获取本地的地址信息）；


- `service`  ：表示服务名或者端口号字符串，可以是以下格式之一：

    - 端口号字符串（例如："80"）；

    - 服务名字符串（例如："http"）；

    - NULL（表示不指定服务名或端口号，用于获取套接字地址信息）；


- `hints`：表示一个 `addrinfo` 结构体指针，用于设置获取地址信息的条件；

- `res`：表示一个指向 `addrinfo` 结构体指针的指针，用于存储返回的地址信息列表。

该函数的返回值是一个整数，返回值为 0 表示函数调用成功，否则表示出现了错误，可以通过 errno 全局变量获取错误代码。

在函数调用成功后，`res` 指向一个 `addrinfo` 结构体指针，该指针指向一个或多个 `addrinfo` 结构体，每个结构体包含一个可用的套接字地址信息，可以通过遍历链表的方式获取所有的地址信息。每个地址信息结构体中包含了地址族、套接字类型、传输协议、IP 地址、端口号等信息。

总之，`getaddrinfo()` 函数可以根据输入的主机名、服务名或者地址信息结构体，返回一个或多个可用的套接字地址信息列表。它是网络编程中常用的函数之一，用于在客户端和服务器端获取可用的网络地址。

#### fprintf()

```c
int fprintf(FILE *stream, const char *format, ...);
```

`fprintf()` 是 C 语言标准库中的一个函数，它的作用是向指定的输出流中输出格式化的数据。

其中，`stream` 参数指定输出的流，可以是 `stdout`、`stderr` 或者其它用户自定义的流。`format` 参数是一个字符串，它包含了输出的格式信息，与 `printf()` 函数中的格式化字符串相同。`...` 表示可变参数列表，用于按照格式字符串中的格式将后续参数输出到指定的输出流中。

`fprintf()` 函数的输入参数是输出流、格式化字符串和可变参数列表，可以根据需要动态指定输出流和输出格式。相比于 `printf()` 函数，`fprintf()` 函数的优点在于它可以将输出重定向到指定的输出流，可以实现灵活的输出控制，比如将输出保存到文件中、将输出发送到远程服务器等。

#### socket()

```c
int socket(int domain, int type, int protocol);
```

`socket()` 是一个系统调用，用于创建一个新的套接字（socket），套接字是实现网络通信的基础。

其中，输入

- `domain` 参数指定协议族，常见的有 `AF_INET`（IPv4）、`AF_INET6`（IPv6）、`AF_UNIX`（Unix 域套接字）等；
- `type` 参数指定套接字类型，常见的有 `SOCK_STREAM`（面向连接的流套接字，如 TCP）、`SOCK_DGRAM`（无连接的数据报套接字，如 UDP）等；
- `protocol` 参数指定协议，通常为 0，表示使用默认协议。

`socket()` 函数的输出是一个整数类型的文件描述符，它用于标识套接字，可以像文件描述符一样使用 `read()`、`write()` 等系统调用进行读写操作。

`socket()` 函数创建的套接字可以用于在网络上建立连接、发送和接收数据等操作，是实现网络通信的基础。例如，通过创建一个面向连接的流套接字，可以使用 TCP 协议建立可靠的、面向连接的网络连接，可以保证数据的可靠传输和按序传输。而通过创建一个无连接的数据报套接字，可以使用 UDP 协议进行快速的、不可靠的数据传输，适合一些实时性要求不高、数据传输量较小的场景。

#### connect()

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

`connect()` 函数是一个系统调用，用于在客户端套接字上发起对服务端套接字的连接请求，其建立的是TCP连接。

其中，输入

- `sockfd` 参数指定客户端套接字的文件描述符；
- `addr` 参数指定服务端套接字的地址信息，通常使用 `struct sockaddr_in` 结构体表示；
- `addrlen` 参数指定地址信息的长度，通常使用 `sizeof(struct sockaddr_in)` 表示。

`connect()` 函数的输出是一个整数类型的返回值，如果连接成功则返回 0，否则返回 -1 并设置相应的错误码，可以使用 `errno` 变量获取错误信息。

`connect()` 函数在客户端套接字上发起连接请求，连接请求发出后将进入三次握手过程，即客户端向服务端发送 SYN 包，服务端回复 SYN-ACK 包，客户端再回复 ACK 包，完成连接建立。如果连接成功，则可以通过客户端套接字进行数据的发送和接收操作。

需要注意的是，`connect()` 函数是一个阻塞调用，如果服务端没有响应或者响应时间过长，函数将一直阻塞直到连接成功或者超时，因此在使用时需要注意设置合理的超时时间或者使用非阻塞模式进行连接。同时，如果客户端套接字使用非阻塞模式，`connect()` 函数将立即返回，并设置相应的错误码，此时可以使用 `select()` 或者 `poll()` 等函数进行异步等待，直到套接字变为可写状态后再进行后续的处理。

#### freeaddrinfo()

```c
void freeaddrinfo(struct addrinfo *res);
```

`freeaddrinfo()` 函数用于释放由 `getaddrinfo()` 函数获取到的地址信息结构体链表，以便释放内存并避免内存泄漏。

其中，`res` 参数是由 `getaddrinfo()` 函数返回的地址信息结构体链表的头指针。

在调用 `getaddrinfo()` 函数获取地址信息之后，程序需要使用获取到的地址信息来建立连接或者绑定端口等操作，完成操作之后需要释放这些地址信息，避免内存泄漏。可以通过调用 `freeaddrinfo()` 函数来释放这些地址信息。需要注意的是，`freeaddrinfo()` 函数只能用于释放由 `getaddrinfo()` 函数获取到的地址信息结构体链表，不能用于释放其他内存块，否则会引发内存错误。

#### send()

以下是send()函数的参数和作用：

send()函数通常在网络编程中用于向已连接的套接字（socket）发送数据。它的参数如下：

1. sockfd: 一个已连接的套接字的文件描述符，用于标识连接。
2. buf: 要发送的数据的指针。
3. len: 要发送的数据的长度。
4. flags: 可选参数，通常设置为0。

send()函数的作用是将指定长度的数据从指定指针缓冲区发送到已连接的套接字。它返回实际发送的字节数，如果出现错误，则返回-1。可以使用errno变量来查看发生了什么错误。
