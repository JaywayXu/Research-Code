of = open('data_x.txt', 'w')
with open('D:/CODE/PYTHON/data.txt', 'r') as f:
    line = f.readline().strip()
    while line:
        # print(line)
        linestr = line.split("\t")
        line = f.readline().strip()
        if linestr[1].find("电脑评论") == -1:
            continue
        text = linestr[0]
        if text.find("京东") != -1:
            continue
        if text.find("差") != -1:
            continue
        if text.find("缺点") != -1:
            continue
        if text.find("不好") != -1:
            continue
        if text.find("不太好") != -1:
            continue
        if text.find("死") != -1:
            continue
        if text.find("坑") != -1:
            continue
        if text.find("售后") != -1:
            continue
        if text.find("..") != -1:
            continue
        if text.find("店") != -1:
            continue
        if text.find("一般") != -1:
            continue
        if text.find("&") != -1:
            continue
        if text.find("忍") != -1:
            continue
        if text.find("?") != -1:
            continue
        if text.find("慢") != -1:
            continue
        # if text.find("好") == -1:
        #     continue
        if len(text) < 20:
            continue
        text = text.strip()
        sttr = '\n{\n"name":"person",\n"desc":"'+text+'",\n"addr":"湖北武汉"\n},'
        # print(sttr)
        of.write(sttr)
of.close()