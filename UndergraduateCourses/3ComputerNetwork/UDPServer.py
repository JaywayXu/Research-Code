# -*- coding: utf-8 -*-

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # SOCK_DGRAM为UDP方式
s.bind(('127.0.0.1', 9999))  # 绑定端口
print("服务器端口：%s:%s" % s.getsockname())
print("服务器已经启动...")

while True:
    receivedData, addr = s.recvfrom(1000)
    print('来自主机端口：%s:%s' % addr)
    receivedData = receivedData.decode('utf-8')
    print('收到：%s' % receivedData)
    reply = 'received：%s' % receivedData
    s.sendto(reply.encode('utf-8'), addr)
