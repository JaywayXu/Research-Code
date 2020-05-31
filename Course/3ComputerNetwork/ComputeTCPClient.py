# -*- coding: utf-8 -*-

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 9999))  # 建立连接

sendData = input("请输入待发送的数据：").encode('utf-8')

s.send(sendData)

receivedData = s.recv(1000).decode('utf-8')
print("从服务器接收到的结果为：%s" % receivedData)

s.close()
