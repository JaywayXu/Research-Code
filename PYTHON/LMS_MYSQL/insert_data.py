import pymysql

# 连接数据库
db = pymysql.connect("localhost", "root", "lyc12030017", "Library", charset='utf8')
print("数据库已连接")
# 获取操作游标
cursor = db.cursor()

#插入Book
with open('data_Book.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        linestr = line.split(" ")
        bid = linestr[0]
        bname = linestr[1]
        author = linestr[2]
        phouse = linestr[3]
        line = f.readline().strip()

        sql = "INSERT INTO Book (BID, Bname, Author, PHouse) VALUES ('%s','%s','%s','%s')" % (bid,bname,author,phouse)
        try:
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
            print("成功")
        except:
            # 发生错误时回滚
            db.rollback()
            print("插入失败")

#插入User
with open('data_User.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        linestr = line.split(" ")
        uid = linestr[0]
        pswd = linestr[1]
        line = f.readline().strip()

        sql = "INSERT INTO User (UID, Password) VALUES ('%s','%s')" % (uid,pswd)
        try:
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
            print("成功")
        except:
            # 发生错误时回滚
            db.rollback()
            print("插入失败")

#插入Root
with open('data_Root.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        linestr = line.split(" ")
        rid = linestr[0]
        pswd = linestr[1]
        line = f.readline().strip()

        sql = "INSERT INTO Root (RID, Password) VALUES ('%s','%s')" % (rid,pswd)
        try:
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
            print("成功")
        except:
            # 发生错误时回滚
            db.rollback()
            print("插入失败")

#插入Stock
with open('data_Stock.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        linestr = line.split(" ")
        bid = linestr[0]
        num = linestr[1]
        line = f.readline().strip()

        sql = "INSERT INTO Stock (BID,Snum) VALUES ('%s','%s')" % (bid,num)
        try:
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
            print("成功")
        except:
            # 发生错误时回滚
            db.rollback()
            print("插入失败")

#插入Lend
with open('data_Lend.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        linestr = line.split(" ")
        uid = linestr[0]
        bid = linestr[1]
        date = linestr[2]
        line = f.readline().strip()

        sql = "INSERT INTO Lend (UID,BID,Ldate) VALUES ('%s','%s','%s')" % (uid,bid,date)
        print("('%s','%s','%s')" % (uid,bid,date))
        try:
            cursor.execute(sql)
            # 提交到数据库执行
            db.commit()
            print("成功")
        except:
            # 发生错误时回滚
            db.rollback()
            print("插入失败")

# 断开数据库
db.close()