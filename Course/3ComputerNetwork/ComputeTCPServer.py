# -*- coding: utf-8 -*-

import threading
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # SOCK_STREAM为TCP方式
s.bind(('127.0.0.1', 9999))  # 绑定端口
s.listen(5)
print("服务器端口号：%s:%s" % s.getsockname())
print("服务器已经启动...")


def tcplink(sock, addr):
    print("已建立连接 %s:%s" % addr)
    receivedData = sock.recv(1000).decode('utf-8')
    print("收到：%s" % receivedData)
    reply = 'received：%s' % receivedData
    sock.send(reply.encode('utf-8'))
    sock.close()
    print('已断开连接 %s:%s' % addr)


while True:
    sock, addr = s.accept()  # 接受一个新连接
    # print("已经建立连接")
    # receivedData = sock.recv(1000).decode('utf-8')
    # print("从客户端接收到信息为：%s" % receivedData)
    # sock.send(receivedData.encode('utf-8'))
    # sock.close()
    t = threading.Thread(target=tcplink, args=(sock, addr))  # 创建新线程来处理TCP连接
    t.start()
