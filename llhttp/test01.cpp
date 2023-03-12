//
// Created by yuanz on 23-3-12.
//
#include <iostream>
#include <cstring>
#include <llhttp.h>

// 定义解析器回调函数
int on_url(llhttp_t* parser, const char* at, size_t length) {
    std::cout << "URL: " << std::string(at, length) << std::endl;
    return 0;
}

int on_header_field(llhttp_t* parser, const char* at, size_t length) {
    std::cout << "Header field: " << std::string(at, length) << std::endl;
    return 0;
}

int on_header_value(llhttp_t* parser, const char* at, size_t length) {
    std::cout << "Header value: " << std::string(at, length) << std::endl;
    return 0;
}

int on_headers_complete(llhttp_t* parser) {
    std::cout << "Headers complete" << std::endl;
    return 0;
}

int on_message_complete(llhttp_t* parser) {
    std::cout << "Message complete" << std::endl;
    return 0;
}

int main() {
    // 创建解析器实例
    llhttp_t parser;
    llhttp_settings_t settings;

    // 初始化解析器和设置
    llhttp_init(&parser, HTTP_REQUEST, &settings);
    settings.on_url = on_url;
    settings.on_header_field = on_header_field;
    settings.on_header_value = on_header_value;
    settings.on_headers_complete = on_headers_complete;
    settings.on_message_complete = on_message_complete;

    // 需要解析的HTTP请求
    const char* request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\n\r\n";

    // 开始解析HTTP请求
    size_t request_len = strlen(request);
    llhttp_execute(&parser, request, request_len);

    return 0;
}
