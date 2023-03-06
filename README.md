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



### 1. structs

#### SSL

SSL是一个具体的SSL/TLS连接对象，代表了一个客户端与服务端之间的安全通道。SSL_CTX对象是创建SSL对象的模板，一个SSL对象必须要与一个SSL_CTX对象关联，才能进行握手和数据传输等操作。在握手过程中，SSL对象会从SSL_CTX对象中获取相关配置信息，例如加密算法、证书、私钥等等，然后通过握手协议和服务端建立安全通道。

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

#### SSL_METHOD

```c
typedef struct ssl_method_st {
    int version; // SSL/TLS 版本号
    int (*ssl_new)(SSL *s); // 创建 SSL 对象的函数指针
    void (*ssl_clear)(SSL *s); // 清除 SSL 对象的函数指针
    void (*ssl_free)(SSL *s); // 释放 SSL 对象的函数指针
    int (*ssl_accept)(SSL *s); // SSL/TLS 握手过程中服务端接收客户端请求的函数指针
    int (*ssl_connect)(SSL *s); // SSL/TLS 握手过程中客户端发起请求的函数指针
    int (*ssl_read)(SSL *s, void *buf, int len); // SSL/TLS 加密数据读取的函数指针
    int (*ssl_peek)(SSL *s, void *buf, int len); // SSL/TLS 加密数据读取（但不删除）的函数指针
    int (*ssl_write)(SSL *s, const void *buf, int len); // SSL/TLS 加密数据写入的函数指针
    int (*ssl_shutdown)(SSL *s); // SSL/TLS 关闭连接的函数指针
    int (*ssl_renegotiate)(SSL *s); // SSL/TLS 重新协商连接的函数指针
    long (*ssl_ctrl)(SSL *s, int cmd, long larg, void *parg); // SSL/TLS 控制命令的函数指针
    long (*ssl_ctx_ctrl)(SSL_CTX *ctx, int cmd, long larg, void *parg); // SSL/TLS 上下文控制命令的函数指针
    const SSL_CIPHER *(*get_cipher_by_char)(const unsigned char *ptr); // 根据字符串表示获取 SSL_CIPHER 的函数指针
    int (*put_cipher_by_char)(const SSL_CIPHER *cipher, unsigned char *ptr); // 将 SSL_CIPHER 转换为字符串表示的函数指针
    int (*ssl_pending)(const SSL *s); // SSL/TLS 还未读取的已解密数据长度的函数指针
    int (*num_ciphers)(void); // SSL/TLS 支持的加密算法数目的函数指针
    const SSL_CIPHER *(*get_cipher)(unsigned ncipher); // 根据索引获取 SSL_CIPHER 的函数指针
    const struct ssl3_enc_method *ssl3_enc; // SSL3 加密方法的结构体指针
    int (*ssl_version)(void); // SSL/TLS 版本的函数指针
    long (*ssl_callback_ctrl)(SSL *s, int cb_id, void (*fp)(void)); // SSL/TLS 回调控制命令的函数指针
} SSL_METHOD;

```



SSL_METHOD 结构体包含了一系列函数指针和数据成员，用于描述 SSL/TLS 协议的方法和版本。常用的成员变量如下：

- version：SSL/TLS 协议的版本号，可以是 SSL2_VERSION、SSL3_VERSION、TLS1_VERSION、TLS1_1_VERSION、TLS1_2_VERSION 等。
- ssl_new：创建 SSL 对象的函数指针。

- ssl_clear：清除 SSL 对象的函数指针，用于释放 SSL 对象的内存。
- ssl_free：释放 SSL 对象的函数指针，用于释放 SSL 对象的内存。
- ssl_accept：SSL/TLS 握手过程中服务端接收客户端请求的函数指针，用于实现服务端的 SSL/TLS 握手逻辑。
- ssl_connect：SSL/TLS 握手过程中客户端发起请求的函数指针，用于实现客户端的 SSL/TLS 握手逻辑。
- ssl_read：SSL/TLS 加密数据读取的函数指针，用于从 SSL/TLS 连接中读取加密数据。
- ssl_peek：SSL/TLS 加密数据读取（但不删除）的函数指针，用于从 SSL/TLS 连接中读取加密数据，但不删除已读取的数据。
- ssl_write：SSL/TLS 加密数据写入的函数指针，用于向 SSL/TLS 连接中写入加密数据。
- ssl_shutdown：SSL/TLS 关闭连接的函数指针，用于实现 SSL/TLS 连接的关闭逻辑。
- ssl_renegotiate：SSL/TLS 重新协商连接的函数指针，用于重新协商 SSL/TLS 连接。
- ssl_ctrl：SSL/TLS 控制命令的函数指针，用于实现 SSL/TLS 的控制命令。
- ssl_ctx_ctrl：SSL/TLS 上下文控制命令的函数指针，用于实现 SSL/TLS 上下文的控制命令。
- get_cipher_by_char：根据字符串表示获取 SSL_CIPHER 的函数指针，用于从字符串中解析出 SSL_CIPHER。
- put_cipher_by_char：将 SSL_CIPHER 转换为字符串表示的函数指针，用于将 SSL_CIPHER 转换为字符串。
- ssl_pending：SSL/TLS 还未读取的已解密数据长度的函数指针，用于获取 SSL/TLS 还未读取的已解密数据长度。
- num_ciphers：SSL/TLS 支持的加密算法数目的函数指针，用于获取 SSL/TLS 支持的加密算法数目。
- get_cipher：根据索引获取 SSL_CIPHER 的函数指针，用于获取 SSL/TLS 支持的加密算法。
- ssl3_enc：SSL3 加密方法的结构体指针，用于实现 SSL3 加密方法。
- ssl_version：SSL/TLS 版本的函数指针，用于获取 SSL/TLS 版本。
- ssl_callback_ctrl：SSL/TLS 回调控制命令的函数指针，用于实现 SSL/TLS 回调控制命令。

### 2. methods

#### SSL_library_init()

SSL_library_init() 是 OpenSSL 库中的一个函数，它用于初始化 OpenSSL 库的 SSL/TLS 实现。它的作用是确保 OpenSSL 库已经正确地初始化，以便其他 SSL/TLS 相关的操作可以正常进行。

在使用 OpenSSL 库进行 SSL/TLS 通信时，通常需要先调用 SSL_library_init() 函数，以确保 OpenSSL 库已经正确地初始化。这通常在程序的初始化阶段完成。如果未正确初始化 OpenSSL 库，则可能会导致程序崩溃、内存泄漏或其他错误。

需要注意的是，如果程序中已经有 SSL 上下文（SSL context）对象被创建，那么在调用 SSL_library_init() 函数之前必须先调用 SSL_CTX_set_default_verify_paths() 函数，以确保 OpenSSL 库能够找到默认的证书验证路径。

总之，SSL_library_init() 函数是 OpenSSL 库中非常重要的一个函数，它的作用是确保 OpenSSL 库已经正确地初始化，为 SSL/TLS 通信做好准备。

#### OpenSSL_add_all_algorithms()

OpenSSL_add_all_algorithms() 是 OpenSSL 库中的一个函数，它用于加载所有支持的加密算法，包括对称加密算法、哈希算法、公钥加密算法和签名算法等。它的作用是确保 OpenSSL 库已经加载了所有支持的加密算法，以便其他加密相关的操作可以正常进行。

在使用 OpenSSL 库进行加密操作时，通常需要先调用 OpenSSL_add_all_algorithms() 函数，以确保 OpenSSL 库已经加载了所有支持的加密算法。这通常在程序的初始化阶段完成。如果未正确加载所有支持的加密算法，则可能会导致程序无法正常进行加密操作。

需要注意的是，如果程序只需要使用特定的加密算法，可以只加载特定的算法库，而不是加载所有支持的算法库。这可以通过调用特定的加载算法库函数（例如 EVP_add_cipher() 和 EVP_add_digest()）来实现。

总之，OpenSSL_add_all_algorithms() 函数是 OpenSSL 库中非常重要的一个函数，它的作用是确保 OpenSSL 库已经加载了所有支持的加密算法，为加密相关的操作做好准备。

#### SSL_load_error_strings()

SSL_load_error_strings() 是 OpenSSL 库中的一个函数，它用于加载 SSL/TLS 错误消息字符串。它的作用是将 OpenSSL 库中的错误消息字符串加载到错误消息缓冲区中，以便可以使用 OpenSSL 库中的错误处理函数（例如 ERR_error_string()）输出相应的错误消息。

在使用 OpenSSL 库进行 SSL/TLS 通信时，如果出现了错误，需要使用 OpenSSL 库中的错误处理函数来获取错误消息。如果在调用错误处理函数之前未调用 SSL_load_error_strings() 函数，可能无法获取正确的错误消息。

需要注意的是，SSL_load_error_strings() 函数只需要在程序的初始化阶段调用一次即可，它会将错误消息字符串加载到一个全局缓冲区中。如果在程序的其他地方需要使用错误处理函数获取错误消息，不需要再次调用 SSL_load_error_strings() 函数。

总之，SSL_load_error_strings() 函数是 OpenSSL 库中非常重要的一个函数，它的作用是将 SSL/TLS 错误消息字符串加载到错误消息缓冲区中，为获取错误消息做好准备。

#### TLS_client_method()

TLS_client_method() 是 OpenSSL 库中的一个函数，它用于创建一个 SSL_METHOD 对象，表示客户端使用 TLS/SSL 进行通信的加密方法。具体来说，TLS_client_method() 创建的 SSL_METHOD 对象是用于客户端与服务器进行 SSL/TLS 通信的方法。在创建 SSL_CTX 对象时，通常需要使用类似于 TLS_client_method() 这样的函数指定使用的加密方法。

TLS_client_method() 的作用是创建一个 SSL_METHOD 对象，该对象包含了客户端使用 TLS/SSL 加密进行通信时所需要的方法。具体来说，SSL_METHOD 对象包含了 SSL/TLS 协议版本、加密算法、握手过程、加密处理等方法的实现。在创建 SSL_CTX 对象时，需要指定使用的 SSL_METHOD，以便后续使用 SSL_connect() 或 SSL_accept() 函数建立 SSL/TLS 连接。

#### SSL_CTX_new()

SSL_CTX_new() 函数的输入参数是 SSL_METHOD对象，用于创建特定的 SSL 方法和选项。

SSL_METHOD 对象表示 SSL/TLS 连接所使用的加密协议和方法，例如 SSLv3、TLSv1.2 等。如果需要使用特定的 SSL/TLS 协议或方法，可以通过创建相应的 SSL_METHOD 对象来实现。常用的 SSL_METHOD 对象有 SSLv23_method()、TLSv1_2_method() 等。

SSL_CTX_new() 函数的输出是一个指向 SSL_CTX 结构体的指针，该结构体表示创建的 SSL 上下文对象。该对象包含了 SSL/TLS 通信所需的所有信息，可以通过 SSL/TLS 连接进行访问和配置。

需要注意的是，SSL_CTX_new() 函数只需要在程序的初始化阶段调用一次即可，可以在程序中使用多个 SSL/TLS 连接共享同一个 SSL 上下文对象。如果需要为不同的 SSL/TLS 连接使用不同的 SSL 上下文对象，可以多次调用 SSL_CTX_new() 函数，每次创建一个新的 SSL 上下文对象。

#### ERR_print_errors_fp()

ERR_print_errors_fp() 是 OpenSSL 库中的一个函数，它用于将 OpenSSL 中产生的错误信息输出到指定的文件流中，通常用于调试和错误处理。

ERR_print_errors_fp() 的输入是一个文件流指针，可以是标准输出、标准错误、日志文件等任意文件流指针。它的输出是将 OpenSSL 中产生的错误信息输出到指定的文件流中。输出的信息包括错误码、错误原因、错误文件名和行号等详细信息，有助于进行错误诊断和调试。

该函数还有一个类似的函数 ERR_print_errors()，不同的是它的输出不是写入文件流，而是返回一个字符串。两个函数的使用方式类似，通常需要在代码中添加错误处理逻辑，以便在程序发生错误时及时发现和解决问题。

#### BIO_new_connect()

```c
BIO *BIO_new_connect(const char *host_port);
```

BIO_new_connect() 是 OpenSSL 中的一个函数，用于创建一个连接到指定主机和端口的 BIO 对象，BIO 对象可以用于进行加密通信。BIO 对象是 OpenSSL 中的一种抽象数据类型，用于提供一种统一的接口，使得加密通信可以透明地进行，而不需要关心底层协议的细节。BIO_new_connect() 的输入是主机名和端口号，输出是一个指向 BIO 对象的指针。

其中，host_port 参数是一个字符串，表示主机名和端口号。它的格式为 "host:port"，比如 "[www.example.com:443](http://www.example.com:443/)" 表示连接到 [www.example.com](http://www.example.com/) 的 443 端口。BIO_new_connect() 函数会根据指定的主机名和端口号创建一个 TCP 连接，并返回一个指向新创建的 BIO 对象的指针。如果连接失败，则返回 NULL。需要注意的是，在使用 BIO_new_connect() 函数之前，必须先调用 SSL_library_init()、OpenSSL_add_all_algorithms() 和 SSL_load_error_strings() 等函数进行初始化，以确保 OpenSSL 库能够正常工作。

#### SSL_new()

```c
SSL *SSL_new(SSL_CTX *ctx);
```

SSL_new() 是 OpenSSL 中的一个函数，用于创建一个 SSL 对象，SSL 对象用于进行加密通信。SSL 对象是 OpenSSL 中的一种抽象数据类型，封装了底层的加密协议（如 TLS/SSL）以及加密算法，可以方便地进行加密通信。SSL_new() 的输入是一个 SSL_CTX 对象，用于指定 SSL 上下文，输出是一个指向 SSL 对象的指针。

其中，ctx 参数是一个指向 SSL 上下文的指针，它包含了 SSL 对象所需的一些配置信息，如加密算法、证书、私钥等。SSL_new() 函数会根据指定的 SSL 上下文创建一个新的 SSL 对象，并返回一个指向该对象的指针。如果创建失败，则返回 NULL。需要注意的是，在使用 SSL_new() 函数之前，必须先调用 SSL_library_init()、OpenSSL_add_all_algorithms() 和 SSL_load_error_strings() 等函数进行初始化，以确保 OpenSSL 库能够正常工作。同时，还需要使用 SSL_set_fd() 函数将 SSL 对象与 TCP 连接关联起来，以便进行加密通信。

#### SSL_set_tlsext_host_name()

SSL_set_tlsext_host_name() 是 OpenSSL 中的一个函数，用于设置 TLS 扩展中的主机名（Server Name Indication，SNI）。SNI 是 TLS 协议的一个扩展，用于在建立 TLS 连接时指定要连接的服务器的主机名，以支持一个 IP 地址下的多个虚拟主机。SSL_set_tlsext_host_name() 的输入是一个 SSL 对象和一个主机名，输出为空。

具体而言，SSL_set_tlsext_host_name() 函数的语法如下：

```c
int SSL_set_tlsext_host_name(SSL *ssl, const char *name);
```

其中，ssl 参数是一个指向 SSL 对象的指针，name 参数是一个字符串，表示要连接的服务器的主机名。SSL_set_tlsext_host_name() 函数会将指定的主机名设置为 SSL 对象的 TLS 扩展中的主机名，以便在建立 TLS 连接时使用。如果设置成功，则返回 1；否则返回 0。需要注意的是，SSL_set_tlsext_host_name() 函数必须在 SSL_connect() 函数之前调用，以确保在建立 TLS 连接时正确地使用 SNI 扩展。同时，还需要确保 OpenSSL 库的版本号不低于 1.0.2，以支持 SNI 扩展。

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

#### wslay_event_on_msg_recv_arg

- `wslay_event_on_msg_recv_arg`，用于表示WebSocket事件处理器在接收到WebSocket消息时的回调函数参数。该结构体包含了以下成员变量：

  1. `rsv`：WebSocket协议规定的保留位。该位占用3个比特位，其中最高位为RSV1，其次为RSV2，最低位为RSV3。WebSocket协议中规定这些位必须为0，如果不为0，则应该抛出一个异常或关闭WebSocket连接。
  2. `opcode`：WebSocket消息的操作码。WebSocket协议定义了几种不同的操作码，用于表示不同类型的WebSocket消息，如文本消息、二进制消息、PING消息、PONG消息等等。
  3. `msg`：指向接收到的WebSocket消息数据的指针。
  4. `msg_length`：接收到的WebSocket消息数据的长度。
  5. `status_code`：如果接收到的WebSocket消息的操作码为`WSLAY_CONNECTION_CLOSE`，则表示该消息包含了关闭WebSocket连接的状态码。如果该消息没有包含状态码，则该字段的值为0。

  通过该结构体中的成员变量，WebSocket事件处理器可以获得接收到的消息数据、消息类型、消息的状态等信息，从而执行相应的操作。例如，可以根据消息类型判断接收到的是文本消息还是二进制数据，然后对其进行相应的解析和处理；如果接收到的是关闭连接的消息，则可以根据状态码判断关闭连接的原因，然后执行相应的处理。

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

#### opcode

```c++
enum wslay_opcode {
  WSLAY_CONTINUATION_FRAME = 0x0u,
  WSLAY_TEXT_FRAME = 0x1u,
  WSLAY_BINARY_FRAME = 0x2u,
  WSLAY_CONNECTION_CLOSE = 0x8u,
  WSLAY_PING = 0x9u,
  WSLAY_PONG = 0xau
};
```

opcode用于表示WebSocket消息的操作码。WebSocket协议定义了6种不同的操作码，分别如下：

1. `WSLAY_CONTINUATION_FRAME`：表示一个消息分片的继续帧。在WebSocket协议中，一个大的消息可以分成多个小的消息分片发送，每个分片对应一个消息帧，其中第一个分片的帧的操作码为`WSLAY_TEXT_FRAME`或`WSLAY_BINARY_FRAME`，后续分片的帧的操作码为`WSLAY_CONTINUATION_FRAME`。
2. `WSLAY_TEXT_FRAME`：表示一个文本消息帧。该帧包含了一段文本数据，用于在客户端和服务器之间传输文本信息。
3. `WSLAY_BINARY_FRAME`：表示一个二进制数据消息帧。该帧包含了一段二进制数据，用于在客户端和服务器之间传输任意类型的数据。
4. `WSLAY_CONNECTION_CLOSE`：表示一个关闭连接的控制帧。该帧用于关闭WebSocket连接，可以包含一个状态码和一个关闭原因。
5. `WSLAY_PING`：表示一个PING控制帧。该帧用于检测WebSocket连接是否正常，服务器接收到该帧后应该立即回复一个PONG控制帧。
6. `WSLAY_PONG`：表示一个PONG控制帧。该帧用于回复服务器发来的PING控制帧，以表明WebSocket连接正常。

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
int wslay_event_context_client_init(wslay_event_context_ptr* ctx_ptr, const struct wslay_event_callbacks* callbacks, void* user_data);
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

函数的输出是一个整数，表示消息是否成功发送。如果返回值为零，表示消息已经成功发送。

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

#### wslay_event_queue_msg()

该函数用于将指定的WebSocket协议消息加入发送队列中。此函数支持控制和非控制消息，给定的消息会被不分片地发送。如果需要进行分片传输，应使用wslay_event_queue_fragmented_msg()函数。

此函数只是将消息加入队列中，而不是立即发送它。调用wslay_event_send()函数可以将这些队列中的消息发送出去。

wslay_event_queue_msg()函数返回0表示成功，否则返回以下负错误代码之一：

- WSLAY_ERR_NO_MORE_MSG：无法将给定消息加入队列中。可能的原因之一是已经排队/发送了关闭控制帧，不允许进一步排队消息。
- WSLAY_ERR_INVALID_ARGUMENT：给定的消息无效。
- WSLAY_ERR_NOMEM：内存不足。

总之，该函数是wslay库中的一个重要功能，用于将WebSocket协议消息加入到发送队列中，确保消息能够正确地发送和接收。在使用wslay库的过程中，需要适时地调用该函数，以确保消息能够被成功发送。

#### wslay_event_recv_callback()

这段代码定义了一个名为wslay_event_recv_callback的函数指针类型。该函数指针接受五个参数：

1. wslay_event_context_ptr ctx：指向wslay事件上下文结构的指针。
2. uint8_t *buf：指向包含接收数据的缓冲区的指针。
3. size_t len：缓冲区的长度。
4. int flags：接收数据的标志位。
5. void *user_data：指向用户数据的指针。

该函数指针的返回值为ssize_t类型，表示已成功接收的字节数。该函数指针用于在wslay事件上下文中指定接收数据时的回调函数。

当使用wslay库处理WebSocket消息时，用户需要定义一个用于接收WebSocket消息的回调函数。回调函数将被传递到wslay_event_context中，以便在接收到WebSocket消息时调用。此处的回调函数类型即为wslay_event_recv_callback。回调函数将接收指向包含WebSocket消息的缓冲区的指针以及缓冲区的长度，并返回已成功接收的字节数。

使用这种回调函数的方式可以在接收数据时提供更多的灵活性和可定制性。它允许用户定义自己的接收数据逻辑，并可以处理任何类型的数据，而不仅仅是WebSocket消息。

#### wslay_genmask_callback()

`genmask_callback` 是 Wslay 库中的一个回调函数类型，用于生成 WebSocket 数据帧的掩码，只有在初始化 WebSocket 客户端使用的事件驱动 API 时才需要使用。

在 WebSocket 协议中，客户端发送的所有数据帧都必须进行掩码操作，而服务器发送的数据帧则不能进行掩码操作。因此，当 WebSocket 客户端发送数据帧时，需要生成掩码，这个回调函数就是用来完成这个任务的。

此回调函数的输入参数包括：

- `wslay_event_context_ptr ctx`：指向 Wslay WebSocket 事件上下文结构体的指针。
- `uint8_t *buf`：指向掩码数据的指针。
- `size_t len`：掩码数据的长度。
- `void *user_data`：用户数据指针，用于传递用户自定义数据。

此回调函数的返回值为整型，表示生成掩码的结果。如果生成掩码成功，返回值为 0；如果出现错误，返回值为 -1。如果出现错误，还需要使用 `wslay_event_set_error()` 函数设置错误代码为 `WSLAY_ERR_CALLBACK_FAILURE`。

当 WebSocket 客户端需要发送数据帧时，会调用 `wslay_event_send()` 函数，并在需要时调用 `genmask_callback` 函数生成掩码。在 `genmask_callback` 函数中，需要将生成的掩码数据填充到 `buf` 中，并确保填充的字节数为 `len`。如果返回值为 0，表示成功生成掩码；如果返回值为 -1，表示生成掩码失败。

#### wslay_event_send_callback()

回调函数在wslay_event_send()需要向远程端点发送更多数据时被调用。函数需要将最多len字节的数据发送给远程端点，并返回实际发送的字节数。flags参数是以下标志位的按位或：

- WSLAY_MSG_MORE：表示还有更多数据需要发送。

这些标志位提供了一些提示，用于优化性能和行为。

如果发生错误，函数需要返回-1并设置错误代码WSLAY_ERR_CALLBACK_FAILURE。wslay的事件驱动API假定使用的是非阻塞I/O。如果错误原因是EAGAIN或EWOULDBLOCK，则应设置WSLAY_ERR_WOULDBLOCK。这很重要，因为它告诉wslay_event_send()停止发送数据并返回。

总之，该回调函数用于发送WebSocket协议消息的数据，是实现WebSocket通信的关键部分之一。在使用wslay库的过程中，需要编写合适的回调函数，以确保数据能够正确地发送和接收。

#### 执行顺序

- `wslay_event_recv_callback recv_callback`：当有数据可读时，将调用此回调函数。它用于接收数据并将其存储在应用程序的缓冲区中。
- `wslay_event_send_callback send_callback`：当应用程序有数据要发送时，将调用此回调函数。它将应用程序中的数据发送到对端。
- `wslay_event_genmask_callback genmask_callback`：此回调函数用于生成掩码。它将生成一个用于掩码的值并将其返回。
- `wslay_event_on_frame_recv_start_callback on_frame_recv_start_callback`：当开始接收一个新的 WebSocket 帧时，将调用此回调函数。它用于处理帧的开始。
- `wslay_event_on_frame_recv_chunk_callback on_frame_recv_chunk_callback`：当 WebSocket 帧的数据到达时，将调用此回调函数。它用于处理 WebSocket 帧中的数据块。
- `wslay_event_on_frame_recv_end_callback on_frame_recv_end_callback`：当 WebSocket 帧接收完毕时，将调用此回调函数。它用于处理 WebSocket 帧的结束。
- `wslay_event_on_msg_recv_callback on_msg_recv_callback`：当接收到完整的消息时，将调用此回调函数。它用于处理接收到的 WebSocket 消息。

执行顺序通常是 `recv_callback` -> `on_frame_recv_start_callback` -> `on_frame_recv_chunk_callback` -> `on_frame_recv_end_callback` -> `on_msg_recv_callback` -> `send_callback`。其中 `genmask_callback` 可能在任何时候调用，因为在发送和接收 WebSocket 帧时都需要使用掩码。

### 3. binance webscoket

参考于 https://binance-docs.github.io/apidocs/websocket_api/cn/ 



### 4. Webscoket

 #### body (payload)

WebSocket的body，也称为payload，是指在WebSocket数据帧中传输的有效载荷数据。在WebSocket协议中，数据传输被分割成多个帧，每个帧包含一个标头和一个数据体，其中数据体就是指body或payload。

WebSocket中的数据帧由两部分组成：帧头和帧体。帧头包含了一些控制信息，如FIN、RSV、Opcode、MASK等。而帧体就是指实际传输的数据，也就是payload或body。

在WebSocket数据传输中，body可以是二进制数据或文本数据。对于文本数据，body通常是一个UTF-8编码的字符串；对于二进制数据，可以是任何字节序列。在WebSocket数据帧中，payload的长度是有限制的，最大长度由WebSocket协议中的最大帧大小（Maximum Frame Size）定义，通常为2^63-1个字节。



## epoll

### 1. structs

#### epool_data

```c
typedef union epoll_data {
    void    *ptr;
    int      fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

```



#### epool_event

```c
struct epoll_event {
    uint32_t     events;    /* Epoll events */
    epoll_data_t data;      /* User data variable */
};
```

`epoll_event`是用于`epoll`系统调用的事件结构体，定义在`sys/epoll.h`头文件中。

该结构体有以下成员变量：

- `uint32_t events`：用于描述`epoll`事件的类型，可以是以下类型之一或者它们的组合：
  - `EPOLLIN`：表示对应的文件描述符可以读取数据（即读事件）；
  - `EPOLLOUT`：表示对应的文件描述符可以写入数据（即写事件）；
  - `EPOLLRDHUP`：表示对端已经关闭连接（即TCP连接的读半部分关闭）；
  - `EPOLLPRI`：表示对应的文件描述符有紧急数据可读（即带外数据）；
  - `EPOLLERR`：表示对应的文件描述符发生错误（即错误事件）；
  - `EPOLLHUP`：表示对应的文件描述符发生挂起（即挂起事件）；
  - `EPOLLET`：表示采用边缘触发模式（edge-triggered）；
  - `EPOLLONESHOT`：表示采用一次性事件模式（one-shot）。
- `epoll_data_t data`：用于存储用户数据的联合体

可以使用`epoll_ctl`系统调用来向`epoll`实例中添加、修改或删除事件，使用`epoll_wait`系统调用来等待事件发生并返回事件列表。例如，以下代码创建了一个`epoll`实例，并将标准输入（`stdin`）的读事件添加到该实例中

### 2. methods

#### epoll_ctrl()

`epoll_ctl` 是 Linux 系统下的一个系统调用函数，用于控制一个 epoll 实例（通过文件描述符 `epfd` 标识）上的文件描述符（通过参数 `fd` 标识）的事件监听状态。`epoll_ctl` 的作用是向 epoll 实例中添加、修改或删除一个待监听的文件描述符。

`epoll_ctl` 的输入参数包括：

- `int epfd`：epoll 实例的文件描述符。
- `int op`：操作类型，可以是 `EPOLL_CTL_ADD`（添加监听事件）、`EPOLL_CTL_MOD`（修改监听事件）或 `EPOLL_CTL_DEL`（删除监听事件）。
  - `EPOLL_CTL_ADD`：将一个文件描述符添加到 epoll 监听列表中；
  - `EPOLL_CTL_DEL`：将一个文件描述符从 epoll 监听列表中删除；
  - `EPOLL_CTL_MOD`：修改一个文件描述符在 epoll 监听列表中的事件类型或者 `epoll_event` 结构体中的数据。
- `int fd`：待监听的文件描述符。
- `struct epoll_event *event`：事件结构体指针，用于设置待监听的事件类型和其他参数。

`epoll_ctl` 的输出为整型，返回值表示操作是否成功。返回值为 0 表示成功，返回值为 -1 表示失败，具体错误信息可以通过 `errno` 全局变量获取。

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

#### sockaddr

```c
struct sockaddr {
    unsigned short sa_family;    // 地址族，如AF_INET、AF_INET6等
    char sa_data[14];           // 地址信息，如IP地址、端口号等
};
```

`sockaddr` 是一个通用的套接字地址结构，用于表示不同协议族的套接字地址。它定义在 `<sys/socket.h>` 头文件中，并且被其他特定协议族的地址结构（如 `sockaddr_in`、`sockaddr_in6` 等）所使用。

其中，`sa_family` 表示地址族，可以为 `AF_INET`（IPv4）、`AF_INET6`（IPv6）等等，`sa_data` 表示具体的地址信息。对于 `sockaddr` 结构体而言，`sa_data` 的长度是固定的，为14个字节，其中具体的地址信息是与地址族相关的。

由于 `sockaddr` 结构体的 `sa_data` 是一个数组，无法确定其具体的含义，因此在实际使用时，需要根据不同的协议族使用对应的地址结构体（如 `sockaddr_in`、`sockaddr_in6` 等），这些结构体都包含了 `sockaddr` 结构体，并且定义了更具体的成员变量来表示具体的地址信息。

#### sigaction

`sigaction` 是一个结构体，用于描述和处理信号的行为。它定义在头文件 `<signal.h>` 中。

它的成员变量如下：

- `void (*sa_handler)(int)`: 信号处理函数的地址或者是 `SIG_DFL`，表示采用默认的信号处理方式；或者是 `SIG_IGN`，表示忽略该信号。这个函数的参数是信号值 `int`。
- `void (*sa_sigaction)(int, siginfo_t *, void *)`: 用于处理信号的更高级的函数，如果设置了这个函数，那么 `sa_handler` 将被忽略。这个函数的参数是信号值 `int`、`siginfo_t *` 类型的指针和 `void *` 类型的指针，分别表示信号值、有关信号的附加信息和上下文。
- `sigset_t sa_mask`: 当前处理信号时，需要屏蔽的信号集。即，当处理一个信号时，如果在处理期间收到了 sa_mask 中的任何一个信号，那么它们都会被挂起，等到该信号处理完毕之后才会被处理。
- `int sa_flags`: 标志位，用于指定在处理该信号时的一些行为。可能的取值如下：
  - `SA_RESTART`: 如果信号处理器被信号中断，那么自动重启系统调用（当进程调用阻塞系统调用时，如果该信号处理器不使用 SA_RESTART 标志，那么该系统调用就会被中断并返回 EINTR 错误码）。
  - `SA_NOCLDSTOP`: 如果子进程停止或继续，不产生 `SIGCHLD` 信号。
  - `SA_SIGINFO`: 说明在 sa_sigaction 成员中使用了更高级别的信号处理器。

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

#### snprintf()

```c
int snprintf(char *str, size_t size, const char *format, ...);
```

`snprintf()` 是 C 语言中的一个函数，用于将格式化的数据写入字符串缓冲区中。

其中 `str` 是一个指向要写入的字符串缓冲区的指针，`size` 是缓冲区的大小，`format` 是一个字符串格式化参数，后面的 `...` 是可变参数列表。

`snprintf()` 的作用是将格式化的数据按照指定的格式写入到缓冲区中，它的输出结果可以用作日志输出、调试信息输出、错误信息输出等。与 `printf()` 不同的是，`snprintf()` 不会把输出结果直接写到标准输出或文件中，而是将其写入到指定的字符串缓冲区中。此外，由于 `snprintf()` 会检查缓冲区的大小，因此可以避免缓冲区溢出的问题。

需要注意的是，`snprintf()` 函数返回值为写入到缓冲区中的字符数，如果发生截断，则返回实际需要的字符数（不包括字符串结尾的 '\0'）。如果写入的字符数大于等于缓冲区的大小，则返回负数，表示缓冲区溢出的错误。

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

#### write()

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

write()函数是C语言中的一个系统调用，用于向已打开的文件描述符（file descriptor）中写入数据。

其中，`fd`是文件描述符，`buf`是要写入的数据的指针，`count`是要写入的数据字节数。

函数返回值是成功写入的字节数，如果返回值小于`count`，则表示写入操作未完全成功，可能是由于磁盘已满或者管道写入端被关闭等原因。

如果函数执行失败，返回值为-1，此时需要根据`errno`变量来获取错误信息。

一般地，使用write()函数的步骤为：

1. 打开文件，获取文件描述符；
2. 调用write()函数，向文件中写入数据；
3. 关闭文件。

该函数通常用于在C语言中进行文件写入操作，也可用于网络编程中，向套接字（socket）写入数据。

#### sigaction()

```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

它的参数意义如下：

- `signum`：表示要操作的信号编号。
- `act`：表示要设置的新信号处理方式，是一个指向 `struct sigaction` 结构体的指针。如果为 `NULL`，表示不改变原有信号处理方式。
- `oldact`：是一个指向 `struct sigaction` 结构体的指针，用于存储原有的信号处理方式，可以为 `NULL`。

函数返回值为 0 表示成功，否则表示失败。

#### fcntl()

在UNIX和类UNIX系统中，fcntl()是一个系统调用函数，用于对文件描述符（file descriptor）进行控制操作。fcntl()函数提供了一些功能，包括：

1. 获取和设置文件描述符的属性，如文件状态标志（file status flags）、文件读写位置（file offset）、文件锁（file locks）等；
2. 控制文件描述符的非阻塞模式，使得在读写文件时不会阻塞等待；
3. 复制文件描述符；
4. 改变文件描述符的属性，如关闭文件描述符、设置文件描述符为执行时关闭等。

`fcntl()`函数的输入参数有：

1. 文件描述符fd：需要进行控制操作的文件描述符；
2. cmd：控制操作的命令，如获取/设置文件描述符属性、获取/设置文件锁等；
3. arg：cmd命令的参数，如设置文件描述符属性时的文件状态标志、文件读写位置等；

返回值：执行成功返回0，否则返回-1，并设置errno来表示错误信息。

#### strtol()

`strtol()`是C语言标准库中的一个函数，用于将一个字符串转换为长整型数值（`long int`）。该函数的声明在头文件 `<stdlib.h>` 中，其函数原型如下：

```c
long int strtol(const char *str, char **endptr, int base);
```

`str` 参数是要被转换的字符串，`endptr` 是一个指向字符指针的指针，它会被设置为指向字符串中第一个无法被转换的字符的位置（如果整个字符串都能被转换，则指向字符串的末尾）。`base` 参数表示转换时使用的进制，可以是 2、8、10 或 16。

`strtol()` 函数返回被转换后的长整型数值。

以下是一个使用 `strtol()` 函数的示例：

```c
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char str[] = "12345";
    char *endptr;
    long int num;

    num = strtol(str, &endptr, 10);
    printf("The number is: %ld\n", num);
    printf("The first non-numeric character is: %c\n", *endptr);

    return 0;
}
```

该程序的输出为：

```c
//sqlCopy codeThe number is: 12345
//The first non-numeric character is: 
```

在上面的示例中，`strtol()` 函数将字符串 "12345" 转换为长整型数值 12345，并将 `endptr` 指向字符串末尾的空字符。

#### setsockopt()

`setsockopt()` 是一个在 Berkeley sockets 接口中定义的函数，用于设置套接字（socket）的选项。该函数在 `<sys/socket.h>` 头文件中声明，其函数原型如下：

```c++
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

各个参数的含义如下：

- `sockfd`：指定需要设置选项的套接字描述符；
- `level`：指定需要设置的选项的协议层。常见的协议层包括 `SOL_SOCKET`、`IPPROTO_TCP`、`IPPROTO_IP` 等；
- `optname`：指定需要设置的选项名；
- `optval`：指向存放选项值的缓冲区；
- `optlen`：指定选项值的长度。

`setsockopt()` 函数的作用是设置套接字的某些选项，如超时时间、发送和接收缓冲区大小、是否启用 TCP_NODELAY 等。这些选项可以影响套接字的行为和性能，允许程序对套接字进行更加细粒度的控制。

以下是一个使用 `setsockopt()` 函数设置套接字选项的示例：

```c++
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("setsockopt");
        close(sockfd);
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
        perror("inet_pton");
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    close(sockfd);
    return 0;
}
```

该程序创建了一个 TCP 套接字，并将其连接到本地 IP 地址为 127.0.0.1、端口号为 80 的服务器上。在连接之前，通过 `setsockopt()` 函数设置了 SO_RCVTIMEO 选项，该选项指定套接字接收数据时的超时时间为 5 秒。如果在 5 秒内没有接收到数据，则接收操作会返回一个错误。

### 3.class

#### string

在 C++ 中，`string` 是标准库提供的一个字符串类型。`string` 类的定义在头文件 `<string>` 中，其常用的成员函数有：

- `string::string()`：构造一个空字符串。
- `string::string(const char*)`：将 C 风格字符串转化为 `string` 类型。
- `string::string(const string&)`：拷贝构造函数，将一个 `string` 对象拷贝到另一个 `string` 对象中。
- `string::operator=()`：重载赋值运算符，用于将一个 `string` 对象的值赋给另一个 `string` 对象。
- `string::operator+()`：重载加法运算符，用于将两个 `string` 对象连接起来。
- `string::size()`：返回字符串的长度。
- `string::empty()`：判断字符串是否为空。
- `string::clear()`：清空字符串。
- `string::c_str()`：返回一个指向字符串首字符的指针。
- `string::data()`：返回一个指向字符串首字符的指针。
- `string::find()`：查找字符串中第一次出现某个字符或子字符串的位置。
- `string::substr()`：返回一个子字符串。

`string` 类的常用成员变量有：

- `char* data`：指向存储字符串的字符数组的指针。
- `size_t length`：表示字符串的长度，不包括结尾的空字符。
- `size_t capacity`：表示当前字符数组的容量。

需要注意的是，`string` 类的成员变量和实现细节在不同的编译器和操作系统下可能有所不同，上述只是其中的一些常见成员变量和函数。

##### assign()

```c
std::string s = "hello";
std::string str = "world";
s.assign(str.begin(), str.end());
// 等价于 s = str;
// 执行完上述代码后，s的值将变为"world"
```

这是C++标准库`std::basic_string`模板类中的成员函数`assign`的实现，其中`basic_string`可能是`std::string`或者`std::wstring`等类型的基类模板。

该函数的作用是将当前字符串对象中的所有字符替换成从迭代器`__first`到`__last`范围内的字符序列。具体来说，该函数会调用`replace`成员函数，将当前字符串对象中的所有字符替换成从迭代器`__first`到`__last`范围内的字符序列，并返回替换后的字符串对象的引用。

##### append()

```c++
std::string s = "hello";
std::string str = "world";
s.append(str.begin(), str.end());
// 等价于 s += str;
// 执行完上述代码后，s的值将变为"helloworld"
```

这是C++标准库`std::basic_string`模板类中的成员函数`append`的实现，其中`basic_string`可能是`std::string`或者`std::wstring`等类型的基类模板。

该函数的作用是将从迭代器`__first`到`__last`范围内的字符序列添加到当前字符串对象的末尾。具体来说，该函数会调用`replace`成员函数，将从当前字符串对象的末尾位置开始的一个空字符序列替换成从迭代器`__first`到`__last`范围内的字符序列，并返回替换后的字符串对象的引用。



#### ostringstream

ostringstream 是 C++ 标准库中的一个类，定义在头文件 <sstream> 中，它是一个流类，用于将各种数据类型转换成字符串。ostringstream 通常用于将各种类型的数据格式化成字符串，比如将数字转换成字符串，将变量和字符串拼接成一个完整的字符串等。

ostringstream 类继承自 ostream 类，支持 ostream 类的所有输出操作符，例如 << 操作符。与 ostream 类不同的是，ostringstream 类还提供了一个成员函数 str()，可以获取当前字符串流中的字符串值。可以将该值赋给一个 std::string 对象，从而实现将数据类型转换成字符串的功能。

ostringstream 类的常见用法是在 C++ 程序中将各种数据类型转换成字符串。例如，可以使用 ostringstream 类将整数、浮点数、字符串等数据类型转换成字符串，然后将它们拼接在一起，最终输出一个完整的字符串。也可以使用 ostringstream 类来格式化输出一些特定的信息，比如日志信息、调试信息等。

ostringstream 常见的成员函数包括：

- << 操作符：用于向字符串流中插入数据。
- str()：获取当前字符串流中的字符串值。
- str(const std::string&)：将字符串流的内容设置为指定的字符串。
- tellp()：获取当前插入位置的偏移量。
- seekp()：设置插入位置的偏移量。
- flush()：刷新输出流。
- good()：判断流是否处于可用状态。
- bad()：判断流是否处于错误状态。
- fail()：判断流是否处于失败状态。
- eof()：判断流是否已经到达文件末尾。

这些成员函数可以用于对字符串流进行操作，比如向字符串流中插入数据、获取字符串流的内容、设置插入位置、刷新输出流等。在实际使用过程中，常见的操作包括将各种数据类型转换成字符串、将多个字符串拼接成一个完整的字符串、格式化输出等。通过使用这些成员函数，可以方便地实现这些操作，从而使代码更加简洁、易读、易维护。

#### fstream

`fstream` 是 C++ 中用于读写文件的流类之一，继承自 `iostream` 类。它支持文件的读写、追加写入等操作，并且可以处理二进制数据和文本数据。

下面是 `fstream` 类的一些常用成员方法：

- `open()`：打开一个文件，并关联一个流；
- `close()`：关闭当前打开的文件；
- `is_open()`：判断文件是否已经打开；
- `eof()`：判断文件是否已经到达文件尾部；
- `fail()`：判断是否发生了错误；
- `tellg()`：获取当前读取位置；
- `seekg()`：设置当前读取位置；
- `tellp()`：获取当前写入位置；
- `seekp()`：设置当前写入位置；
- `write()`：将二进制数据写入文件；
- `read()`：从文件读取二进制数据；
- `operator<<()`：将数据以文本格式写入文件；
- `operator>>()：从文件读取文本格式的数据。

需要注意的是，`fstream` 类同时继承了 `istream` 和 `ostream` 类，因此可以直接使用 `<<` 和 `>>` 运算符来读写文本格式的数据。而且，`fstream` 类还支持文件的定位和截取等高级操作。

### 4. 其他概念

#### errno

`errno`是C/C++语言中的一个全局变量，它记录了最近一次发生错误的错误代码（通常是一个整数），由系统调用和某些库函数在发生错误时设置。通常情况下，当某个系统调用或库函数发生错误时，会将`errno`设置为一个非零值以表示出错原因的类型，程序员可以通过检查`errno`的值来确定错误的类型和发生的原因。`errno`的值是线程安全的，因为它是线程局部存储的。

要使用`errno`，需要包含头文件`<errno.h>`（或在C++中使用`<cerrno>`）。在使用之前，需要先将它初始化为0。在发生错误时，需要检查`errno`的值，根据不同的错误类型采取不同的处理方式。常见的错误类型有：

- `EACCES`：拒绝访问，通常发生在权限不足或文件不存在等情况下。
- `EINVAL`：无效参数，通常发生在参数不正确或不合法等情况下。
- `ENOENT`：未找到，通常发生在文件或目录不存在等情况下。
- `ENOMEM`：内存不足，通常发生在申请内存失败等情况下。
- `EINTR`：中断，通常发生在系统调用被中断时。

#### 服务名

服务名是一种可读性更好的网络端口号，用于标识网络上的服务。以下是一些常见的服务名：

- FTP：文件传输协议
- SSH：安全外壳协议
- Telnet：远程终端协议
- SMTP：简单邮件传输协议
- HTTP：超文本传输协议
- HTTPS：安全超文本传输协议
- DNS：域名系统
- SNMP：简单网络管理协议
- NTP：网络时间协议
- DHCP：动态主机配置协议
- NFS：网络文件系统
- SMB：服务器消息块协议（用于Windows文件共享）
- LDAP：轻型目录访问协议

这些服务名通常被映射到一些预定义的端口号，例如 HTTP 默认使用端口号 80，HTTPS 默认使用端口号 443。但是，服务名与端口号之间的映射并不是强制性的，也可以使用其他端口号来提供相应的服务。

#### HTTP

HTTP（超文本传输协议，Hypertext Transfer Protocol）是一种应用层协议，用于在Web应用程序之间传输数据。HTTP规定了浏览器和Web服务器之间的通信格式，包括请求和响应的格式、数据编码方式、错误处理等内容，是Web应用的基础协议。

HTTP协议是指HTTP所定义的具体协议规范，包括HTTP请求和响应格式、HTTP状态码、请求方法、响应头部字段等内容。HTTP协议定义了客户端和服务器之间的通信协议，并规定了如何交换数据、如何处理错误和异常情况等。

因此，HTTP是一个实际的应用协议，是Web应用程序中的一部分，而HTTP协议是一个抽象的协议定义，规范了HTTP协议中所需的各种元素和特性，是HTTP协议的正式文档。

#### HTTPS

HTTPS（全称：Hyper Text Transfer Protocol Secure）是一种安全的超文本传输协议，是在HTTP协议的基础上加入了SSL/TLS协议的加密和认证机制，用于保护网络通信安全。

HTTPS的工作原理是在数据传输过程中加入SSL/TLS协议，通过公开密钥加密技术和数字证书认证机制，确保客户端和服务器之间的通信安全可靠。HTTPS使用加密算法对数据进行加密，保证数据传输过程中的机密性和完整性，同时使用数字证书对通信双方进行认证，确保通信双方的身份真实可信。

HTTPS协议的主要优点是：

1. 数据传输安全性：HTTPS使用加密技术保护数据传输过程中的机密性和完整性，有效防止数据被篡改或窃取。
2. 通信双方身份认证：HTTPS使用数字证书认证机制对通信双方进行身份认证，确保通信双方的身份真实可信。
3. 可信度高：HTTPS使用数字证书认证机制确保通信双方的身份真实可信，保证数据传输过程中的安全可靠性。

因此，HTTPS广泛应用于涉及个人隐私和机密信息传输的场景，例如在线支付、网上购物、社交网络等。

---

HTTP和HTTPS之间的主要区别可以概括如下：

1. 数据传输安全性：HTTP数据传输是明文传输的，不提供任何加密保护，容易被窃听和篡改；而HTTPS使用SSL/TLS加密协议进行数据传输，数据传输过程中的数据都是经过加密的，安全性更高。
2. 通信方式：HTTP是无状态协议，每个请求都是独立的，服务器不会保留客户端的任何信息；而HTTPS支持会话状态保持，客户端与服务器之间可以保持一定的状态信息，从而提高通信效率。
3. 端口号：HTTP默认使用端口号80，而HTTPS默认使用端口号443。
