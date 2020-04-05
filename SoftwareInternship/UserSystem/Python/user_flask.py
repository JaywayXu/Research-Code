# -*- coding:utf-8 -*-
from flask import Flask, request
import pymysql
import json

Loginfo = {'USER': 'root', 'PSWD': '0017',
           'HOST': '127.0.0.1', 'DBNAME': 'ParkingLot'}

app = Flask(__name__)


@app.route('/login', methods=['POST', 'GET'])
def login():
    '''登陆'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    upswd = request.args.get("Upswd")
    # 数据库
    sql = "SELECT UID FROM User WHERE UID='%s' AND Upswd='%s'" % (uid, upswd)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        # 如果查询到数据
        if data:
            j = '{"result": true}'
            # 返回信息
            cursor.close()
            db.close()
            return j
        else:
            j = '{"result": false}'
            # 返回信息
            cursor.close()
            db.close()
            return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/logout', methods=['POST', 'GET'])
def logout():
    '''注册'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    upswd = request.args.get("Upswd")
    # 数据库
    sql = "SELECT UID FROM User WHERE UID='%s'" % (uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        # 如果查询到数据
        if data:  # 已注册
            j = '{"result": false}'
            # 返回信息
            cursor.close()
            db.close()
            return j
        else:
            sql = "INSERT INTO User (UID, Upswd, Balance) VALUES ('%s', '%s', '%s')" % (
                uid, upswd, '0')
            try:
                cursor.execute(sql)
                db.commit()
                j = '{"result": true}'
                # 返回信息
                cursor.close()
                db.close()
                return j
            except:
                cursor.close()
                db.close()
                return "error"
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/getLot', methods=['POST', 'GET'])
def getLot():
    '''获取车位库存'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 数据库
    sql = "SELECT Num FROM Lot WHERE LID='MAIN'"
    try:
        cursor.execute(sql)  # 执行
        data = cursor.fetchall()  # 获取查询结果
        fields = cursor.description  # 获取字段名

        result = {}
        result[fields[0][0]] = data[0][0]

        j = json.dumps(result)  # 转为json
        # 返回信息
        cursor.close()
        db.close()
        return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/getLotCar', methods=['POST', 'GET'])
def getLotCar():
    '''获取当前用户停车信息'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    # 数据库
    sql = "SELECT CID,Intime FROM LotCar WHERE CID=(SELECT CID FROM UserCar WHERE UID='%s')" % (
        uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        fields = cursor.description  # 获取字段名

        result = {}
        result[fields[0][0]] = str(data[0][0])
        result[fields[1][0]] = str(data[0][1])

        j = json.dumps(result)  # 转为json
        # 返回信息
        cursor.close()
        db.close()
        return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/getRecord', methods=['POST', 'GET'])
def getRecord():
    '''获取交易记录'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    # 数据库
    sql = "SELECT CID,Intime,Outtime,Cost FROM Record WHERE UID='%s'" % (uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        fields = cursor.description  # 获取字段名
        name = []
        for i in fields:
            name.append(i[0])
        results = []
        print(data)
        for i in data:
            result = {}
            result[fields[0][0]] = str(i[0])
            result[fields[1][0]] = str(i[1])
            result[fields[2][0]] = str(i[2])
            result[fields[3][0]] = i[3]
            results.append(result)
        j = json.dumps(results)
        # 返回信息
        cursor.close()
        db.close()
        return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/getUserCar', methods=['POST', 'GET'])
def getUserCar():
    '''获取当前用户绑定车牌号'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    # 数据库
    sql = "SELECT CID FROM UserCar WHERE UID='%s'" % (uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        fields = cursor.description  # 获取字段名

        result = {}
        result[fields[0][0]] = str(data[0][0])

        j = json.dumps(result)  # 转为json
        # 返回信息
        cursor.close()
        db.close()
        return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/getUser', methods=['POST', 'GET'])
def getUser():
    '''获取当前用户信息'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    # 数据库
    sql = "SELECT Uname,Uphone,Balance FROM User WHERE UID='%s'" % (uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        fields = cursor.description  # 获取字段名

        result = {}
        result[fields[0][0]] = str(data[0][0])
        result[fields[1][0]] = str(data[0][1])
        result[fields[2][0]] = str(data[0][2])

        j = json.dumps(result)  # 转为json
        # 返回信息
        cursor.close()
        db.close()
        return j
    except:
        cursor.close()
        db.close()
        return "error"


@app.route('/changeCar', methods=['POST', 'GET'])
def changeCar():
    '''修改车牌号'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    cid = request.args.get("CID")
    if cid == "undefined":  # 如果没有则删除
        sql = "DELETE FROM UserCar WHERE (UID = '%s')" % (uid)
        try:
            cursor.execute(sql)
            db.commit()
            cursor.close()
            db.close()
        except:
            cursor.close()
            db.close()
            return "error"
    else:
        sql = "SELECT UID FROM UserCar WHERE UID='%s'" % (uid)
        try:
            cursor.execute(sql)
            data = cursor.fetchall()
            # 如果查询到数据
            if data:  # 已绑定，改变
                sql = "UPDATE UserCar SET CID = '%s' WHERE (UID = '%s')" % (
                    cid, uid)
                try:
                    cursor.execute(sql)
                    db.commit()
                    cursor.close()
                    db.close()
                except:
                    cursor.close()
                    db.close()
                    return "error"
            else:  # 未绑定，添加
                sql = "INSERT INTO UserCar (UID, CID) VALUES ('%s', '%s')" % (
                    uid, cid)
                try:
                    cursor.execute(sql)
                    db.commit()
                    cursor.close()
                    db.close()
                except:
                    cursor.close()
                    db.close()
                    return "error"
        except:
            cursor.close()
            db.close()
            return "error"


@app.route('/changeUser', methods=['POST', 'GET'])
def changeUser():
    '''修改用户信息'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    uname = request.args.get("Uname")
    uphone = request.args.get("Uphone")
    if uname == "undefined":
        uname = ""
    if uphone == "undefined":
        uphone = ""
    
    sql = "UPDATE User SET Uname = '%s', Uphone = '%s' WHERE (UID = '%s')" % (uname,uphone,uid)
    try:
        cursor.execute(sql)
        db.commit()
        cursor.close()
        db.close()
    except:
        cursor.close()
        db.close()
        return "error"

@app.route('/changeBalance', methods=['POST', 'GET'])
def changeBalance():
    '''修改余额（充值）'''
    db = pymysql.connect(
        Loginfo['HOST'], Loginfo['USER'], Loginfo['PSWD'], Loginfo['DBNAME'], charset='utf8')
    cursor = db.cursor()

    # 获取json数据
    uid = request.args.get("UID")
    balance = request.args.get("Balance")
    if balance == "undefined":
        balance = 0
    
    sql = "SELECT Balance FROM User WHERE (UID = '%s')" % (uid)
    try:
        cursor.execute(sql)
        data = cursor.fetchall()
        if data:
            print("a")
            balance = float(balance) + float(data[0][0])
            sql = "UPDATE User SET Balance = '%f' WHERE (UID = '%s')" % (balance, uid)
            try:
                cursor.execute(sql)
                db.commit()
                cursor.close()
                db.close()
            except:
                cursor.close()
                db.close()
                return "error"
    except:
        cursor.close()
        db.close()
        return "error"

if __name__ == '__main__':
    app.run(debug=True)
