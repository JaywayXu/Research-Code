package ly.hope;



import java.awt.Color;

import java.util.ArrayList;

import java.util.List;

import java.util.Random;



/**

* 生成淘宝评论

*

* @author CxyLy

*

*/

public class Comment {



/**

* 评论集合

*/

static List<String> commentList = new ArrayList<String>();

// 初始化评论

static {

commentList.add("小伙伴们赶紧下单吧");

commentList.add("刚好看到店铺有活动，而且价格也便宜。");

commentList.add("买的房心 用的书心");

commentList.add("小怪兽图案很好看，送的挂饰也很漂亮。很搭，设计非常好很有创意，");

commentList.add("推拉设计，有盖子的孩子会经常弄掉，推拉设计就不存在丢失了，总体满意");

commentList.add("产品符合预期 做工用料还是扎实 希望不要出什么故障多用几年");

commentList.add("很好的质量，比想象的厚实，水开了又报警声，四升三口人够用，方便，省电啊！快递给力 ");

commentList.add("日期都很新鲜，食材很新鲜，口感丰富口感正宗，麻辣鲜香，汤卤调制十分讲究，独立小包装，干净卫生，方便储存，独立小包装，干净卫生，");

commentList.add("方便储存，酸酸辣辣的很过瘾，泡出来真是色鲜味俱全，酸酸辣辣的很过痣，");

commentList.add("真是好吃到停不下来，汤料的味道也很浓郁，几乎与店里卖的正宗螺蛳粉没有区别。真的很好吃哦，推荐购买。");

commentList.add("到了，用了几天很不错，很结实有时候还用他锁电动车，有了它方便多了，价格又实惠");

commentList.add("发货很及时，价格便宜，质量比较好，比外面实体店便宜很多，标配2把钥匙，客服回消息很快，讲解产品很用心，对产品比较熟悉，收到以后跟客服讲解的一样满意好评");

commentList.add("食物是指能够满足机体正常生理和生化能量需求，并能延续正常寿命的物质。对人体而言，能够满足人的正常生活活动需求并利于寿命延长的物质称之为食物。");

commentList.add(

"食物通常是由碳水化合物、脂肪、蛋白质、水构成，能够藉进食或是饮用为人类或者生物提供营养或愉悦的物质。食物的来源可以是植物、动物或者其他界的生物，例如真菌，亦或发酵产品像是酒精。人类借由采集、耕种、畜牧、狩猎、渔猎等许多种不同的方式获得食物。");

commentList.add("食物和水是人们每天的必需品。");

commentList.add("《史记·范雎蔡泽列传》：“秦昭王……加赐相国 应侯 食物日益厚。”");

commentList.add("《后汉书·韦彪传》：“﹝帝﹞乃赐 彪 珍羞食物。”");

commentList.add("《二十年目睹之怪现状》第十二回：“有一个私贩，专门贩土（鸦片）……装在坛子里面，封了口，粘了茶食店的招纸，当做食物之类。”");

commentList.add("丁玲《杜晚香·欢乐的夏天》：“那些黑熊、野猪、狼、狐……还时常偷跑到庄稼地里找寻食物。”");

commentList.add("汉王充《论衡·商虫》：“变复之家，见其（食谷虫）希出，出又食物，则谓之灾。”");

commentList.add("《隋书·五行志下》：“ 梁大同初，大蝗，篱门松栢叶皆尽…… 京房 《易·飞候》曰：‘食禄无益圣化，天视以虫，虫无益於人而食万物也。’是时公卿皆以虚澹为美，不亲杂事，无益食物之应也。”");

commentList.add("农业的出现是人类文明的起源。在此之前，人们食物来源靠的是狩猎和采集，其生活要以野生植物和动物提供的多少为转移");

commentList.add("随着世界各地先祖们在采集经济的基础上和长期生活实践中，逐步观察和熟悉了某些植物的生长规律，慢慢懂得了如何培育作物。");

commentList.add("架子很好，安装师傅说也不错正好比他们规定带的还便宜普通的价钱买不锈钢的很好！！！");

commentList.add("看上去非常厚实的洗衣机，样式好看，物流也快，洗夏天7.8件衣服没有问题");

commentList.add("顺丰送货上来，服务很好。很好用不占地方，噪音也不大，一次能洗6件夏天衣服。好评。");

commentList.add("知菊隐风");

commentList.add("寒潭叶落而知秋");

commentList.add("讨还鼓山");

commentList.add("里有朋友");

commentList.add("白首之约");

commentList.add("保住知名");

commentList.add("没见人别拉拉扯扯");

commentList.add("年少请款单的痛");

commentList.add("自招吗 狗场口");

commentList.add("鄙视季节额");

commentList.add("新僧");

commentList.add("有很多");

commentList.add("程序员");

commentList.add("照例");

commentList.add("写作业");

commentList.add("分复寺都");

commentList.add("撷取人见状红");

commentList.add("唯有更鼓防寒服");

commentList.add("至死不渝的一场梦");

commentList.add("黑泽逢世");

commentList.add("千本樱");

commentList.add("sakura");

commentList.add("常营椅子");

commentList.add("花瓣修");

commentList.add("俺不走");

commentList.add("花自飘零水自流");

commentList.add("阿斯顿");

commentList.add("哇塞的");

commentList.add("天侠隐修");

commentList.add("江流是不赚");



}



/**

* 显示评论

*/

public static void showComment() {

StringBuffer end_comment = new StringBuffer(100);

StringBuffer end_se = new StringBuffer(100);

Random random = new Random();



while (end_comment.length() < 120 || end_se.length() < 120) {

end_comment.append(commentList.get(random.nextInt(commentList.size())));

end_se.append(commentList.get(random.nextInt(commentList.size())));

}

// System.out.println(end_se.length());

System.out.println(end_comment);

System.out.println();

System.out.println(end_se);

}



public static void main(String[] args) {



System.out.println("执行开始");

// 文字 评论

showComment();



// 图片

String path = "C:\\Users\\CxyLy\\Desktop\\";



Hope.markImageByText(Math.random() + "", path + "files\\1.jpg", path + "1.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\2.jpg", path + "2.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\3.jpg", path + "3.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\4.jpg", path + "4.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\5.jpg", path + "5.jpg", 0, new Color(0, 0, 0), "JPG");



System.out.println("执行完毕");

}



}



