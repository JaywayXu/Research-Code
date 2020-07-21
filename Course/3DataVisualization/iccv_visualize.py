from nltk.corpus import stopwords
from wordcloud import WordCloud
import matplotlib.pyplot as plt
from numpy import *
import re

plt.rcParams['font.sans-serif'] = ['FangSong']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


class ICCV_Visualize:
    '''ICCV数据可视化类'''

    def __init__(self):
        self.file_name = "iccv_title_author.txt"
        self.title_author_dict = {}  # 标题:作者dict
        self.read_file(self.file_name)
        self.word_dict = self.title_word_count()
        self.author_dict = self.author_count()

    def read_file(self, file_name):
        '''读取文件'''
        file = open(file_name, "r")
        lines = file.readlines()
        for i in range(0, len(lines), 2):
            title_str = lines[i].strip('\n')  # 读取标题，去除换行符

            author_str = lines[i+1].strip('\n')  # 读取作者，去除换行符
            author_list = author_str.split(",")[:-1]  # 按","进行分割，并去除最后一个空字符串
            author_list = [author.strip() for author in author_list]  # 去除前后空格

            self.title_author_dict[title_str] = author_list

    def title_word_count(self):
        '''标题词频统计，去除英文停用词'''
        # 词频统计
        new_text = " ".join(
            list(self.title_author_dict.keys()))  # 将所有标题合成一个字符串，按空格分隔
        new_text = new_text.lower()  # 所有大写字母变为小写字母
        str_list = re.split('\s+', new_text)
        word_dict = {}
        for str_word in str_list:
            if str_word in word_dict.keys():  # 如果key存在则value加1
                word_dict[str_word] = word_dict[str_word] + 1
            else:
                word_dict[str_word] = 1
        # 去掉英文停用词
        keys = list(word_dict.keys())
        stop_words = stopwords.words('english')
        stop_words.append('via')
        for key in keys:
            if key in stop_words:
                del word_dict[key]
        return word_dict

    def author_count(self):
        '''作者频率统计'''
        author_dict = {}
        author_list_list = self.title_author_dict.values()
        for author_list in author_list_list:
            for author in author_list:
                if author in author_dict.keys():
                    author_dict[author] = author_dict[author] + 1
                else:
                    author_dict[author] = 1
        return author_dict

    def draw_word_wordcloud(self):
        '''绘制热点词汇词云'''
        # 生成一个词云对象
        wordcloud = WordCloud(
            background_color="white",  # 设置背景为白色，默认为黑色
            width=1920,  # 设置图片的宽度
            height=1080,  # 设置图片的高度
            margin=20  # 设置图片的边缘
        ).generate_from_frequencies(self.word_dict)
        plt.imshow(wordcloud)  # 绘制图片
        plt.axis("off")  # 消除坐标轴
        # plt.show()  # 展示图片
        wordcloud.to_file('word_cloud.jpg')  # 保存图片
        plt.close()


    def draw_word_pie(self):
        '''绘制热点词汇饼图'''
        w_dict = self.word_dict
        # 排序
        w_list_all = sorted(
            w_dict.items(), key=lambda item: item[1], reverse=True)
        # 取频率最高的前12个
        w_list = w_list_all[:13]
        # 绘制饼图
        x = [value for key, value in w_list]
        labels = [key for key, value in w_list]
        plt.pie(x, labels=labels, wedgeprops=dict(
            edgecolor='w', width=1, linewidth=2))  # 画饼图
        plt.title("热点词汇饼图（只显示前12）")
        plt.savefig('word_pie.jpg')
        # plt.show()
        plt.close()

    def draw_word_plot(self):
        '''绘制热点词汇折线图'''
        w_dict = self.word_dict
        # 排序
        w_list_all = sorted(
            w_dict.items(), key=lambda item: item[1], reverse=True)
        # 取频率最高的前12个
        w_list = w_list_all[:13]
        # 绘制折线图
        plt.figure(figsize=(12, 6))  # 设置大小
        keys = [key for key, value in w_list]
        values = [value for key, value in w_list]
        plt.plot(keys, values, color='g')
        plt.xticks(rotation=15)  # 横轴内容旋转
        plt.grid()
        plt.title("热点词汇折线图（只显示前12）")
        plt.savefig('word_plot.jpg')
        # plt.show()
        plt.close()

    def draw_word_nums_bar(self):
        '''绘制每个热点词汇的出现次数和论文数量柱状图'''
        word_dict = self.word_dict
        # 取频率最高的前12个
        word_list = sorted(
            word_dict.items(), key=lambda item: item[1], reverse=True)[:12]
        # 求每个热点词汇的论文数量
        w_list = [word for word, value in word_list]
        w_dict = {}
        word_dict = {}
        for word in w_list:
            # 词频dict
            word_dict[word] = self.word_dict[word]
            # 文章数dict
            count = 0
            for title in self.title_author_dict.keys():
                if word in re.split('\s+', title.lower()):  # 转小写并分词
                    count = count+1
            w_dict[word] = count
        # 绘制柱状图
        plt.figure(figsize=(12, 6))  # 设置大小
        x = range(len(w_dict))
        bar1 = plt.bar([i-0.2 for i in x], word_dict.values(),
                       width=0.4, color='g', label="词频")  # 词频
        bar2 = plt.bar([i+0.2 for i in x], w_dict.values(),
                       width=0.4, color='orange', label="论文数")  # 论文数量
        plt.xticks(x, w_dict.keys(), rotation=15)  # 横轴内容旋转
        # 显示数值
        for rect in bar1:
            height = rect.get_height()  # 获得bar1的高度
            plt.text(rect.get_x() + rect.get_width() / 2, height +
                     3, str(height), ha="center", va="bottom")
        for rect in bar2:
            height = rect.get_height()
            plt.text(rect.get_x() + rect.get_width() / 2, height +
                     3, str(height), ha="center", va="bottom")
        plt.grid(axis="y")
        plt.title("热点词汇出现次数和论文数量柱状图（只显示前12）")
        plt.xlabel('热点词汇')
        plt.ylabel("数量")
        plt.legend()
        plt.savefig('word_nums_bar.jpg')
        # plt.show()
        plt.close()

    def draw_author_wordcloud(self):
        '''绘制热门作者词云'''
        # 生成一个词云对象
        wordcloud = WordCloud(
            background_color="white",  # 设置背景为白色，默认为黑色
            width=1920,  # 设置图片的宽度
            height=1080,  # 设置图片的高度
            margin=20  # 设置图片的边缘
        ).generate_from_frequencies(self.author_dict)
        plt.imshow(wordcloud)  # 绘制图片
        plt.axis("off")  # 消除坐标轴
        # plt.show()  # 展示图片
        wordcloud.to_file('author_cloud.jpg')  # 保存图片
        plt.close()

    def draw_author_pie(self):
        '''绘制热门作者饼图'''
        a_dict = self.author_dict
        # 取频率最高的前15个
        a_list = sorted(
            a_dict.items(), key=lambda item: item[1], reverse=True)[:15]
        # 绘制饼图
        x = [value for key, value in a_list]
        labels = [key for key, value in a_list]
        plt.pie(x, labels=labels, wedgeprops=dict(
            edgecolor='w', width=1, linewidth=2))  # 画饼图
        plt.title("热门作者饼图（只显示前15）")
        plt.savefig('author_pie.jpg')
        # plt.show()
        plt.close()

    def draw_author_bar(self):
        '''绘制热门作者论文数柱状图'''
        author_dict = self.author_dict
        # 取频率最高的前15个
        author_list = sorted(
            author_dict.items(), key=lambda item: item[1], reverse=True)[:15]
        author_dict = {}
        for author, value in author_list:
            author_dict[author] = value
        # 绘制柱状图
        plt.figure(figsize=(12, 8))  # 设置大小
        bar1 = plt.bar(author_dict.keys(), author_dict.values(),
                       width=0.5, color='g')  # 论文数量
        plt.xticks(rotation=20)  # 横轴内容旋转
        # 显示数值
        for rect in bar1:
            height = rect.get_height()  # 获得bar1的高度
            plt.text(rect.get_x() + rect.get_width() / 2, height +
                     0.2, str(height), ha="center", va="bottom")
        plt.title("热门作者论文数柱状图（只显示前15）")
        plt.xlabel('热门作者')
        plt.ylabel("论文数量")
        plt.savefig('author_bar.jpg')
        # plt.show()
        plt.close()

    def draw_author_num_bar(self):
        '''绘制作者数分布柱状图'''
        author_list_list = self.title_author_dict.values()
        # 统计作者数量的论文数
        author_num_dict = {}
        author_num_list = []
        for author_list in author_list_list:
            a_len = len(author_list)
            author_num_list.append(a_len)
            if a_len in author_num_dict.keys():
                author_num_dict[a_len] = author_num_dict[a_len] + 1
            else:
                author_num_dict[a_len] = 1
        # 统计最大最小作者数、平均作者数
        author_num_max = max(author_num_list)
        author_num_min = min(author_num_list)
        author_num_ave = mean(author_num_list)
        # 绘制柱状图
        plt.figure(figsize=(12, 6))  # 设置大小
        keys = author_num_dict.keys()
        values = author_num_dict.values()
        bar1 = plt.bar(keys, values, color='g')
        plt.xticks(range(max(keys)+1))
        for rect in bar1:
            height = rect.get_height()  # 获得bar1的高度
            plt.text(rect.get_x() + rect.get_width() / 2, height +
                     3, str(height), ha="center", va="bottom")
        plt.grid(axis="y")
        plt.title("作者数分布柱状图")
        plt.xlabel('作者数量')
        plt.ylabel("论文个数")
        plt.text(14, 235, '最大作者数：%d' % author_num_max)
        plt.text(14, 220, '最小作者数：%d' % author_num_min)
        plt.text(14, 205, '平均作者数：%d' % author_num_ave)
        plt.savefig('author_num_bar.jpg')
        # plt.show()
        plt.close()

    def draw_author_num_plot(self):
        '''绘制论文作者数分布折线图'''
        author_list_list = self.title_author_dict.values()
        # 统计作者数量的论文数
        author_num_dict = {}
        for author_list in author_list_list:
            a_len = len(author_list)
            if a_len in author_num_dict.keys():
                author_num_dict[a_len] = author_num_dict[a_len] + 1
            else:
                author_num_dict[a_len] = 1
        author_num_list = sorted(
            author_num_dict.items(), key=lambda item: item[0], reverse=False)
        # 绘制折线图
        plt.figure(figsize=(12, 6))  # 设置大小
        keys = [key for key, value in author_num_list]
        values = [value for key, value in author_num_list]
        plt.plot(keys, values, color='g')
        plt.xticks(range(max(keys)+1))
        plt.grid()
        plt.title("作者数分布折线图")
        plt.xlabel('作者数量')
        plt.ylabel("论文个数")
        plt.savefig('author_num_plot.jpg')
        # plt.show()
        plt.close()

    def draw_title_num_bar(self):
        '''绘制论文标题单词数分布柱状图'''
        title_list = self.title_author_dict.keys()
        # 统计单词数量的论文数
        title_num_dict = {}
        title_num_list = []
        for title in title_list:
            t_len = len(re.split('\s+', title))
            title_num_list.append(t_len)
            if t_len in title_num_dict.keys():
                title_num_dict[t_len] = title_num_dict[t_len] + 1
            else:
                title_num_dict[t_len] = 1
        # 统计最大最小单词数、平均单词数
        title_num_max = max(title_num_list)
        title_num_min = min(title_num_list)
        title_num_ave = mean(title_num_list)
        # 绘制柱状图
        plt.figure(figsize=(12, 6))  # 设置大小
        keys = title_num_dict.keys()
        values = title_num_dict.values()
        bar1 = plt.bar(keys, values, color='g')
        plt.xticks(range(max(keys)+1))
        for rect in bar1:
            height = rect.get_height()  # 获得bar1的高度
            plt.text(rect.get_x() + rect.get_width() / 2, height +
                     3, str(height), ha="center", va="bottom")
        plt.grid(axis="y")
        plt.title("标题单词数分布柱状图")
        plt.xlabel('标题单词数量')
        plt.ylabel("论文个数")
        plt.text(16, 177, '最大单词数：%d' % title_num_max)
        plt.text(16, 165, '最小单词数：%d' % title_num_min)
        plt.text(16, 153, '平均单词数：%d' % title_num_ave)
        plt.savefig('title_num_bar.jpg')
        # plt.show()
        plt.close()

    def draw_title_num_plot(self):
        '''绘制论文作者数分布折线图'''
        title_list = self.title_author_dict.keys()
        # 统计作者数量的论文数
        title_num_dict = {}
        for title in title_list:
            t_len = len(re.split('\s+', title))
            if t_len in title_num_dict.keys():
                title_num_dict[t_len] = title_num_dict[t_len] + 1
            else:
                title_num_dict[t_len] = 1
        title_num_list = sorted(
            title_num_dict.items(), key=lambda item: item[0], reverse=False)
        # 绘制折线图
        plt.figure(figsize=(12, 6))  # 设置大小
        keys = [key for key, value in title_num_list]
        values = [value for key, value in title_num_list]
        plt.plot(keys, values, color='g')
        plt.xticks(range(max(keys)+1))
        plt.grid()
        plt.title("标题单词数分布折线图")
        plt.xlabel('标题单词数量')
        plt.ylabel("论文个数")
        plt.savefig('title_num_plot.jpg')
        # plt.show()
        plt.close()


if __name__ == "__main__":
    iv = ICCV_Visualize()
    iv.draw_word_wordcloud()
    iv.draw_word_pie()
    iv.draw_word_plot()
    iv.draw_word_nums_bar()
    iv.draw_author_wordcloud()
    iv.draw_author_pie()
    iv.draw_author_bar()
    iv.draw_author_num_bar()
    iv.draw_author_num_plot()
    iv.draw_title_num_bar()
    iv.draw_title_num_plot()
