import MySQLdb
import datetime
import time

class LMS():
    """图书管理系统类"""

    def __init__(self):
        """初始化图书管理系统"""

        # 连接数据库
        self.db = MySQLdb.connect("localhost", "root", "0017", "Library", charset='utf8')
        print("数据库已连接")
        # 获取操作游标
        self.cursor = self.db.cursor()
        # 登录运行
        self.login()
        # 断开数据库
        self.db.close()

    def login(self):
        """登录"""

        while True:
            user_type = str(input("1.用户登录 2.用户注册 3.管理员登录："))

            if user_type == '1':
                # 查询
                self.user_id = str(input("请输入用户名："))
                sql = "SELECT UID,Password FROM User WHERE UID='%s'" % (self.user_id)
                try:
                    self.cursor.execute(sql)
                    u_get = self.cursor.fetchall()
                    # 如果查询到数据
                    if u_get:
                        password = str(u_get[0][1])
                        user_password = str(input("请输入密码："))
                        if user_password == password:
                            self.run_user()
                            break
                        else:
                            print("密码错误")
                    else:
                        print("帐号不存在")
                except:
                    print("Error: unable to fecth data")

            elif user_type == '2':
                # 查询
                self.user_id = str(input("请输入用户名："))
                sql = "SELECT * FROM User WHERE UID='%s'" % (self.user_id)
                try:
                    self.cursor.execute(sql)
                    u_get = self.cursor.fetchall()
                    # 如果查询到数据
                    if u_get:
                        print("用户名已存在")
                    else:
                        # 插入
                        user_password = str(input("请输入密码："))
                        sql = "INSERT INTO User(UID, Password) VALUES ('%s', '%s')" % \
                              (self.user_id,user_password)
                        try:
                            self.cursor.execute(sql)
                            # 提交到数据库执行
                            self.db.commit()
                            print("注册成功")
                        except:
                            # 如果发生错误则回滚
                            self.db.rollback()
                            print("注册失败")
                except:
                    print("Error: unable to fecth data")

            elif user_type == '3':
                # 查询
                self.root_id = str(input("请输入管理员名："))
                sql = "SELECT RID,Password FROM Root WHERE RID='%s'" % (self.root_id)
                try:
                    self.cursor.execute(sql)
                    r_get = self.cursor.fetchall()
                    # 如果查询到数据
                    if r_get:
                        password = str(r_get[0][1])
                        root_password = str(input("请输入密码："))
                        if root_password == password:
                            self.run_root()
                            break
                        else:
                            print("密码错误")
                    else:
                        print("帐号不存在")
                except:
                    print("Error: unable to fecth data")

    def run_user(self):
        """用户模块"""

        while True:
            print("0.退出 1.借阅 2.归还 3.查询借阅记录")
            print("4.查询图书信息 5.查询库存信息 6.注销帐号")
            choice = str(input("输入要使用的功能号："))
            if choice == '1':
                self.user_lend()
            elif choice == '2':
                self.user_return()
            elif choice == '3':
                self.user_search()
            elif choice == '4':
                self.search_book()
            elif choice == '5':
                self.search_stock()
            elif choice == '6':
                if self.cancell_user(True) == True:
                    break
            elif choice == '0':
                break
            else:
                print("请输入正确选项")
            input("按Enter继续")

    def run_root(self):
        """管理员模块"""

        while True:
            print("0.退出 1.采书入库 2.清除库存 3.查询借阅记录")
            print("4.查询图书信息 5.查询库存信息 6.注销用户帐号")
            choice = str(input("输入要使用的功能号："))
            if choice == '1':
                self.root_getin()
            elif choice == '2':
                self.root_remove()
            elif choice == '3':
                self.root_search()
            elif choice == '4':
                self.search_book()
            elif choice == '5':
                self.search_stock()
            elif choice == '6':
                self.cancell_user(False)
            elif choice == '0':
                break
            else:
                print("请输入正确选项")
            input("按Enter继续")

    def user_lend(self):
        """借书"""

        book_name = str(input("输入要借的书名："))
        sql = """SELECT BID,Snum FROM Stock WHERE BID IN (
                    SELECT BID FROM Book WHERE Bname = '%s')""" % (book_name)
        try:
            self.cursor.execute(sql)
            s_get = self.cursor.fetchall()
            # 如果在Stock查找到记录
            if s_get:
                bid = s_get[0][0]
                num = s_get[0][1]
                # 如果还有库存
                if int(num) > 0:
                    print("库存%d本" % (num))
                    # 是否有借阅记录
                    sql = "SELECT Ldate FROM Lend WHERE UID = '%s' AND BID = '%s'" % (self.user_id,bid)
                    try:
                        self.cursor.execute(sql)
                        l_get = self.cursor.fetchall()
                        # 如果有借阅记录
                        if l_get:
                            date = l_get[0][0]
                            print("已借阅过该书，不可再借阅")
                            print("借阅时间%s" % (date))
                        else:
                            # 增加借阅记录
                            sql = "INSERT INTO Lend (UID, BID, Ldate) VALUES ('%s','%s','%s')" % \
                                  (self.user_id, bid, str(datetime.date.today()))
                            try:
                                self.cursor.execute(sql)
                                # 提交到数据库执行
                                self.db.commit()
                                print("借阅成功")
                            except:
                                # 发生错误时回滚
                                self.db.rollback()
                                print("插入借阅记录失败")
                    except:
                        print("Error: unable to fecth data")
                else:
                    print("该书已无库存")
            else:
                print("图书馆无此书")
        except:
            print("Error: unable to fecth data")

    def user_return(self):
        """还书"""

        book_name = str(input("请输入要还的书名："))
        sql = """SELECT BID,Ldate FROM Lend WHERE UID = '%s' AND BID IN (
                    SELECT BID FROM Book WHERE Bname = '%s')""" % (self.user_id,book_name)
        try:
            self.cursor.execute(sql)
            l_get = self.cursor.fetchall()
            # 如果有借阅记录
            if l_get:
                bid = l_get[0][0]
                date = l_get[0][1]
                # 删除借阅记录
                sql = "DELETE FROM Lend WHERE UID = '%s' AND BID = '%s'" % (self.user_id, bid)
                try:
                    self.cursor.execute(sql)
                    # 提交到数据库执行
                    self.db.commit()
                    print("归还成功")
                except:
                    # 发生错误时回滚
                    self.db.rollback()
                    print("删除借阅记录失败")
                # 业务（付款）
                date_lend = time.strptime(str(date), '%Y-%m-%d')
                date_lend = datetime.date(date_lend[0], date_lend[1], date_lend[2])
                date_now = datetime.date.today()
                print("已租%d天，租金7元/天" % ((date_now-date_lend).days))
            else:
                print("无此条借阅记录")
        except:
            print("Error: unable to fecth data")

    def user_search(self):
        """查找借阅记录（用户）"""

        sql = "SELECT Book.Bname,Lend.Ldate FROM Book,Lend WHERE Lend.UID = '%s' AND Book.BID = Lend.BID" % (self.user_id)
        try:
            self.cursor.execute(sql)
            l_get = self.cursor.fetchall()
            # 如果有借阅记录
            if l_get:
                for var in l_get:
                    book_name = var[0]
                    date = var[1]
                    print("图书名：%s 借阅时间：%s" % (book_name,date))
            else:
                print("无借阅记录")
        except:
            print("Error: unable to fecth data")

    def root_getin(self):
        """采书入库"""

        book_name = str(input("请输入要采购的书名："))
        sql = "SELECT BID FROM Book WHERE Bname='%s'" % (book_name)
        try:
            self.cursor.execute(sql)
            b_get = self.cursor.fetchall()
            # 如果在Book中查询到记录
            if b_get:
                bid = b_get[0][0]
                num = int(input("请输入数量："))
                sql = "SELECT BID FROM Stock WHERE BID='%s'" % (bid)
                try:
                    self.cursor.execute(sql)
                    s_get = self.cursor.fetchall()
                    # 如果在Stock中查询到记录
                    if s_get:
                        # 更新
                        sql = "UPDATE Stock SET Snum = Snum + %d WHERE BID='%s'" % (num,bid)
                        try:
                            self.cursor.execute(sql)
                            # 提交到数据库执行
                            self.db.commit()
                            print("入库成功")
                        except:
                            # 发生错误时回滚
                            self.db.rollback()
                            print("入库失败")
                    else:
                        # 插入
                        sql = "INSERT INTO Stock(BID, Snum) VALUES ('%s', %d)" % (bid,num)
                        try:
                            self.cursor.execute(sql)
                            # 提交到数据库执行
                            self.db.commit()
                            print("入库成功")
                        except:
                            # 如果发生错误则回滚
                            self.db.rollback()
                            print("入库失败")
                except:
                    print("Error: unable to fecth data")
            else:
                print("书名不在书库中")
        except:
            print("Error: unable to fecth data")

    def root_remove(self):
        """清仓库存"""

        bname = input("输入要清仓的书名：")
        sql = """SELECT BID FROM Stock WHERE BID IN(
                SELECT BID FROM Book WHERE Bname = '%s')""" % (bname)
        try:
            self.cursor.execute(sql)
            s_get = self.cursor.fetchall()
            # 如果库中有该书
            if s_get:
                bid = s_get[0][0]
                sql = "SELECT * FROM Lend WHERE BID = '%s'" % (bid)
                try:
                    self.cursor.execute(sql)
                    l_get = self.cursor.fetchall()
                    # 如果有借阅记录
                    if l_get:
                        print("该书还有借阅记录，无法清仓")
                    else:
                        sql = "DELETE FROM Stock WHERE BID = '%s'" % (bid)
                        try:
                            self.cursor.execute(sql)
                            # 提交到数据库执行
                            self.db.commit()
                            print("清仓成功")
                        except:
                            # 发生错误时回滚
                            self.db.rollback()
                            print("清仓失败")
                except:
                    print("Error: unable to fecth data")
            else:
                print("库中没有该书")
        except:
            print("Error: unable to fecth data")

    def root_search(self):
        """查找借阅记录（管理员）"""

        sql = "SELECT Book.Bname,Lend.UID,Lend.Ldate FROM Book,Lend WHERE Book.BID = Lend.BID ORDER BY Book.BID+0"
        try:
            self.cursor.execute(sql)
            l_get = self.cursor.fetchall()
            # 如果有借阅记录
            if l_get:
                for var in l_get:
                    book_name = var[0]
                    uid = var[1]
                    date = var[2]
                    print("图书名：%s 用户名：%s 借阅时间：%s" % (book_name,uid,date))
            else:
                print("无借阅记录")
        except:
            print("Error: unable to fecth data")

    def search_book(self):
        """查询图书信息"""

        print("1.图书名 2.作者 3.出版社 0.退出")
        choice = str(input("输入要使用的功能号："))
        if choice == '1':
            book_name = str(input("输入图书名："))
            # 查询图书记录
            sql = "SELECT BID,Author,PHouse FROM Book WHERE Bname = '%s' ORDER BY BID+0" % (book_name)
            try:
                self.cursor.execute(sql)
                b_get = self.cursor.fetchall()
                # 如果有图书记录
                if b_get:
                    bid = b_get[0][0]
                    author = b_get[0][1]
                    phouse = b_get[0][2]
                    print("图书名：%s 编号：%s 作者：%s 出版社：%s" % (book_name,bid,author,phouse))
                    # 查询库存记录
                    sql = "SELECT Snum FROM Stock WHERE BID = '%s'" % (bid)
                    try:
                        self.cursor.execute(sql)
                        s_get = self.cursor.fetchall()
                        # 如果有库存
                        if s_get:
                            snum = s_get[0][0]
                            print("库存：%s本" % (snum))
                        else:
                            print("该书无库存")
                    except:
                        print("Error: unable to fecth data")
                else:
                    print("无该书记录")
            except:
                print("Error: unable to fecth data")

        elif choice == '2':
            author = input("输入作者名：")
            sql = "SELECT BID,Bname,PHouse FROM Book WHERE Author = '%s' ORDER BY BID+0" % (author)
            try:
                self.cursor.execute(sql)
                b_get = self.cursor.fetchall()
                # 如果有图书记录
                if b_get:
                    for var in b_get:
                        bid = var[0]
                        bname = var[1]
                        phouse = var[2]
                        print("作者名：%s 图书编号：%s 图书名：%s 出版社：%s" % (author,bid,bname,phouse))
                else:
                    print("无该作者的图书记录")
            except:
                print("Error: unable to fecth data")
        elif choice == '3':
            phouse = input("输入出版社名：")
            sql = "SELECT BID,Bname,Author FROM Book WHERE PHouse = '%s' ORDER BY BID+0" % (phouse)
            try:
                self.cursor.execute(sql)
                b_get = self.cursor.fetchall()
                # 如果有图书记录
                if b_get:
                    for var in b_get:
                        bid = var[0]
                        bname = var[1]
                        author = var[2]
                        print("出版社：%s 图书编号：%s 图书名：%s 作者名：%s" % (phouse,bid,bname,author))
                else:
                    print("无该出版社的图书记录")
            except:
                print("Error: unable to fecth data")
        elif choice == '0':
            pass
        else:
            print("请输入正确选项")

    def search_stock(self):
        """查询库存记录"""

        sql = "SELECT Book.BID,Book.Bname,Stock.Snum FROM Book,Stock WHERE Book.BID = Stock.BID ORDER BY Book.BID+0"
        try:
            self.cursor.execute(sql)
            s_get = self.cursor.fetchall()
            # 写入文件
            with open('库存.txt', 'w+') as f:
                # 如果有库存
                if s_get:
                    for var in s_get:
                        bid = var[0]
                        bname = var[1]
                        snum = var[2]
                        print("编号：%s 图书名：%s 库存：%s本" % (bid,bname,snum))
                        f.write("编号：%s 图书名：%s 库存：%s本\n" % (bid,bname,snum))
                else:
                    print("无任何库存")
            f.close()
        except:
            print("Error: unable to fecth data")

    def cancell_user(self,is_user):
        if is_user == True:
            uid = self.user_id
        else:
            uid = input("输入要注销的用户名：")
        # 查询借阅记录
        sql = "SELECT UID FROM Lend WHERE UID = '%s'" % (uid)
        try:
            self.cursor.execute(sql)
            l_get = self.cursor.fetchall()
            # 如果查询到借阅记录
            if l_get:
                print("该用户还有未归还书，无法注销")
            else:
                # 查询用户记录
                sql = "SELECT UID,Password FROM User WHERE UID='%s'" % (uid)
                try:
                    self.cursor.execute(sql)
                    u_get = self.cursor.fetchall()
                    # 如果查询到用户数据
                    if u_get:
                        password = str(u_get[0][1])
                        user_password = str(input("输入密码："))
                        if user_password == password:
                            # 删除用户信息
                            sql = "DELETE FROM User WHERE UID = '%s'" % (uid)
                            try:
                                self.cursor.execute(sql)
                                # 提交到数据库执行
                                self.db.commit()
                                print("注销成功")
                                if is_user == True:
                                    return True
                            except:
                                # 发生错误时回滚
                                self.db.rollback()
                                print("注销失败")
                        else:
                            print("密码错误,注销失败")
                    else:
                        print("帐号不存在")
                except:
                    print("Error: unable to fecth data")
        except:
            print("Error: unable to fecth data")
        return False


lms = LMS()
