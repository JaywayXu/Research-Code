# -*- coding:utf-8 -*-
# flask运行

from app import app

if __name__ == '__main__':
    app.debug = True  # 设置调试模式，生产模式的时候要关掉debug
    app.run(threaded=False)  # 启动服务器，设置单线程，多线程调用keras预测会出错
