# -*- coding: utf-8 -*-

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # SOCK_DGRAM为UDP方式

sendData = b'This is an Example for C/S Communication by UDP!'
s.sendto(sendData, ('127.0.0.1', 9999))  # 发送数据

print(s.recv(1000).decode('utf-8'))  # 接收数据

s.close()
