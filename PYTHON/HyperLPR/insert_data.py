import pymysql

# 连接数据库
db = pymysql.connect("localhost", "root", "lyc12030017",
                     "CarApp", charset='utf8')
print("数据库已连接")
# 获取操作游标
cursor = db.cursor()

# 插入Car
car_ids = ['京A88888', '皖CTJ876', '皖A92141']
usernames = ['张红', '黎明', '小二']
phones = ['14265786411', '15467898765', '10387653456']
addrs = ['新桂圆小区6号楼3单元702', '新桂圆小区10号楼1单元102', '新桂圆小区8号楼2单元1102']
ctimes = ['2015-7-18',
          '2019-6-30',
          '2020-1-12']

for i in range(3):
    sql = "INSERT INTO Car (car_id,username,phone,addr,ctime) VALUES ('%s','%s','%s','%s','%s')" % (
        car_ids[i], usernames[i], phones[i], addrs[i], ctimes[i])
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
