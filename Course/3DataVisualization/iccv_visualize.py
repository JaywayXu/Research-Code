from nltk.corpus import stopwords
from wordcloud import WordCloud
import matplotlib.pyplot as plt
import re

plt.rcParams['font.sans-serif'] = ['FangSong']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号


class ICCV_Visualize:
    '''ICCV数据可视化类'''

    def __init__(self):
        self.file_name = "iccv_title_author.txt"
        self.title_author_dict = {}  # 标题:作者dict
        self.read_file(self.file_name)

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

    def draw_words_wordcloud(self):
        '''绘制热点词汇词云'''
        # 生成一个词云对象
        wordcloud = WordCloud(
            background_color="white",  # 设置背景为白色，默认为黑色
            width=1920,  # 设置图片的宽度
            height=1080,  # 设置图片的高度
            margin=20  # 设置图片的边缘
        ).generate_from_frequencies(self.title_word_count())
        plt.imshow(wordcloud)  # 绘制图片
        plt.axis("off")  # 消除坐标轴
        # plt.show()  # 展示图片
        wordcloud.to_file('word_cloud.jpg')  # 保存图片

    def draw_words_pie(self):
        '''绘制热点词汇饼图'''
        w_dict = self.title_word_count()
        # 取频率最高的前10个
        w_list = sorted(
            w_dict.items(), key=lambda item: item[1], reverse=True)[:11]
        # 绘制饼图
        x = [value for key, value in w_list]
        labels = [key for key, value in w_list]
        plt.title("每个热点词汇出现的次数（只显示前10）")
        plt.pie(x, labels=labels, wedgeprops=dict(
            edgecolor='w', width=1, linewidth=2))  # 画饼图
        plt.savefig('word_pie.jpg')
        # plt.show()

    def draw_words_nums_bar(self):
        '''绘制每个热点词汇的论文数量柱状图'''
        w_dict = self.title_word_count()
        # 取频率最高的前10个
        w_list = sorted(
            w_dict.items(), key=lambda item: item[1], reverse=True)[:11]
        # 求每个热点词汇的论文数量
        word_list = [word for word, value in w_list]
        word_dict = {}
        for word in word_list:
            count = 0
            for title in self.title_author_dict.keys():
                if word in title.lower():
                    count = count+1
            word_dict[word] = count
        # 绘制柱状图
        plt.figure(figsize=(10, 6))  # 设置大小
        plt.title("包含每种热点词汇的论文数量（只显示前10）")
        plt.bar(word_dict.keys(), word_dict.values(), width=0.5)
        plt.xticks(rotation=15)  # 横轴内容旋转
        # 显示数值
        for a, b in zip(word_dict.keys(), word_dict.values()):
            plt.text(a, b+0.05, '%d' %

            
                     b, ha='center', va='bottom', fontsize=10)
        plt.xlabel('热点词汇')
        plt.ylabel("论文数量")
        plt.savefig('word_nums_bar.jpg')
        # plt.show()


if __name__ == "__main__":
    iv = ICCV_Visualize()
    iv.draw_words_wordcloud()
    iv.draw_words_pie()
    iv.draw_words_nums_bar()
